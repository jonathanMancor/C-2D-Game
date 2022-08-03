#pragma once
#include "Includes.h"
#include "Animation.h"

class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture *texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	//speed : dlay in milliseconds
	int speed = 100;

public:
	
	int animIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	


	SpriteComponent() = default;
	SpriteComponent(const char* path)
	{
		SetTex(path);
	}

	SpriteComponent(const char* path, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 6, 100);
		Animation walk = Animation(1, 6, 100);

		animations.emplace("idle", idle);
		animations.emplace("walk", walk);

		Play("idle");
		SetTex(path);
	}


	~SpriteComponent()
	{
		SDL_DestroyTexture(texture);
	}



	void SetTex(const char* path) 
	{
		texture = TextureManager::LoadTexture(path);
	}



	void Init() override
	{
		transform = &entity->GetComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
		
	}

	void Update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}
	


	void Play(const char* animName) 
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};


