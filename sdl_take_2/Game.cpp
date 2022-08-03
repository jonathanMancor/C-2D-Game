#include "Includes.h"



Tile_map* map;
Manager manager;


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };


std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

auto& player(manager.AddEntity());
auto& wall(manager.AddEntity());

const char* mapFile = "assets/test_tm.png";

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};


auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));


Game::Game()
{
}

Game::~Game()
{
}





void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{

	int flags = 0;
	if (fullscreen = true) SDL_WINDOW_FULLSCREEN;


	//	INITIALIZING SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{

		//	Initialize Window
		std::cout << "subsystems initialized \n";
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) 
		{
			std::cout << "window created \n";
		}


		//	Initialize Renderer						
		renderer = SDL_CreateRenderer(window, -1, 0); //window, index, flags
		if (renderer) 
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "renderer created \n";
		}



		isRunning = true;
	}

	
	map = new Tile_map();

	Tile_map::LoadMap("assets/test_map_30x30.csv", 30, 30);

	player.AddComponent<TransformComponent>(2);
	player.AddComponent<SpriteComponent>("assets/32_bit_char_ss.png", true);
	player.AddComponent<KeyboardController>();
	player.AddComponent<ColliderComponent>("player");

	player.addGroup(groupPlayers);



	


	
	//else isRunning = false;
}






void Game::handleEvents()
{
	
	SDL_PollEvent(&event);
	switch (event.type) 
	{
	case
	SDL_QUIT: 
		isRunning = false;
		break;
	}
}






void Game::update()
{
	//	 all update functions for diferent game elements (player, enemy, ...) will be called here


	manager.Refresh();
	manager.Update();

	camera.x = player.GetComponent<TransformComponent>().position.x - (SCREEN_WIDTH / 2);
	camera.y = player.GetComponent<TransformComponent>().position.y - (SCREEN_HEIGHT / 2);

	if (camera.x < 0) {
		camera.x = 0;
	}
	if (camera.y < 0) {
		camera.y = 0;
	}

	if (camera.x > camera.w) {
		camera.x = camera.w;
	}
	if (camera.y > camera.h) {
		camera.y = camera.h;
	}
	




	//colliders
	/*for (auto cc : colliders)
	{
		Collision::AABB(player.GetComponent<ColliderComponent>(), *cc);
	}*/
}






void Game::render()
{
	SDL_RenderClear(renderer);


	//	this is where items will be added to the renderer

	//	*	*	*	*	*
	


	for (auto& t : tiles)
	{
		t->Draw();
	}
	for (auto& p : players)
	{
		p->Draw();
	}
	for (auto& e : enemies)
	{
		e->Draw();
	}
	
	

	//	*	*	*	*	*
	SDL_RenderPresent(renderer);
}







void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "game cleaned \n";

}

void Game::AddTile(int srcX, int srcY, int xpos, int ypos)
{
	auto& tile(manager.AddEntity());
	tile.AddComponent<TileComponent>(srcX, srcY, xpos, ypos, mapFile);
	tile.addGroup(groupMap);
}


