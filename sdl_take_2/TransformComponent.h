#pragma once
#include "Includes.h"
class TransformComponent : public Component
{

public:

	Vector2D position;
	Vector2D velocity;
	
	int width = TILE_SIZE;
	int height = TILE_SIZE;
	int scale = 1;


	int speed = 3;

	TransformComponent()
	{
		position.Zero();
		
	}

	TransformComponent(int sc)
	{
		position.x = (SCREEN_WIDTH / 2) ;
		position.y = (SCREEN_HEIGHT / 2) ;
		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int w, int h, int sc)
	{
		position.x = x;
		position.y = y;
		width = w;
		height = h;
		scale = sc;
	}



	void Init() override
	{
		velocity.Zero();
	}

	void Update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}


	
};