#pragma once

#include <SDL.h>
#include <SDL_image.h>

class Entity
{
public:
	Entity();
	Entity(int x, int y);
	Entity(int x, int y, int w, int h);
	Entity(int x, int y, int w, int h, const char* texPath);

	int x;
	int y;

	int width;
	int height;

	SDL_Texture* texture;

	void LoadTexture(const char* texPath);
	void Draw();
	void Move(int x, int y);
	void Update();

	virtual void HandleEvent() {};

	SDL_Rect src, dest;
private:
	
};
