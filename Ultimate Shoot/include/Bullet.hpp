#pragma once

#include "Entity.hpp"





class Bullet : public Entity
{
public:

	int speed = 1;

	void Init()
	{
		LoadTexture("assets/BulletA.png");



		src.x = 4;
		src.y = 12;

		width = 6;
		height = 16;


	};

	void UpdateBullet()
	{
		y -= 4 * speed;


	}

private:
	
};