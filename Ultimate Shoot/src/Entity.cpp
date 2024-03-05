#include "../include/Entity.hpp"
#include "../include/Game.hpp"

Entity::Entity()
{
	this->x = 0;
	this->y = 0;

	this->width = 32;
	this->height = 32;
	
	this->texture = NULL;
}

Entity::Entity(int x, int y)
{
	this->x = x;
	this->y = y;

	this->width = 32;
	this->height = 32;

	this->texture = NULL;
}

Entity::Entity(int x, int y, int w, int h)
{
	this->x = x;
	this->y = y;

	this->width = w;
	this->height = h;

	this->texture = NULL;
}

Entity::Entity(int x, int y, int w, int h, const char* texPath)
{
	this->x = x;
	this->y = y;

	this->width = w;
	this->height = h;

	LoadTexture(texPath);
}


void Entity::Move(int x, int y)
{
	this->x = x;
	this->y = y;
}



void Entity::LoadTexture(const char* texPath)
{
	SDL_Surface* tempSurface = IMG_Load(texPath);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	this->texture = tex;
}


void Entity::Draw()
{
	SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}


void Entity::Update()
{
	src.w = width;
	src.h = height;
	//src.x = 0;
	//src.y = 0;

	dest.x = x;
	dest.y = y;
	dest.w = src.w * 2;
	dest.h = src.h * 2;

	Draw();
	HandleEvent();
}
