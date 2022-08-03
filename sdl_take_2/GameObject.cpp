#include "Includes.h"

GameObject::GameObject(const char* spritesheet, const char* type, int x, int y)
{
	
	objTexture = TextureManager::LoadTexture(spritesheet);
	objType = type;

	if (x != NULL || y != NULL) 
	{
		xpos = x;
		ypos = y;
	}
	else 
	{
		xpos = 0;
		ypos = 0;
	}
	
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	
	

	if (objType == "player")
	{
		

		srcRect.w = TILE_SIZE;
		srcRect.h = TILE_SIZE;
		srcRect.x = 0;
		srcRect.y = 0;

		destRect.w = srcRect.w * 2;
		destRect.h = srcRect.h * 2;
		destRect.x = xpos;
		destRect.y = ypos;
	}
	

	
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
