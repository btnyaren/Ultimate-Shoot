#pragma once


#include "Entity.hpp"
#include <iostream>



class Player : public Entity
{
public:

	void Init()
	{
		LoadTexture("assets/MainShipA.png");
		src.x = 8;
		src.y = 10;

		x = 400;
		y = 500;
	};
	

private:


};