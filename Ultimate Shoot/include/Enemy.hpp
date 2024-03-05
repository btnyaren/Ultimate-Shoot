#pragma once


#include "Entity.hpp"





class Enemy : public Entity
{
public:

	int speed = 1;

	void Init()
	{
		LoadTexture("assets/EnemyAA.png");



		src.x = 6;
		src.y = 8;


	};

	void UpdateEnemy()
	{
		y += 1 * speed;

		
	}

private:

};

