#pragma once
class GameObject
{
public:
	GameObject(const char* spritesheet, const char* type, int x, int y);
	~GameObject();

	void Update();
	void Render();

private:
	int xpos;
	int ypos;
	const char* objType;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};

