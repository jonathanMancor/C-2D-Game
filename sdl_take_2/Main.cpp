#include "Includes.h"


Game* game = nullptr;


int main(int argc, char *argv[])
{

	//	Frame rate
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;



	//	Initialized Game
	game = new Game();

	game->init(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH, SCREEN_HEIGHT, false);
	

	//	Game loop
	while ( game->running() )
	{
		frameStart = SDL_GetTicks();


		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;


		//	limit frame rate
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	
	return 0;
}

