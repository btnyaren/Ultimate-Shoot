#pragma once


#include <iostream>



class Collision
{
public:
	template<typename T>
	static bool AABB(T rect1, T rect2)
	{
		if (rect1.x < rect2.x + rect2.w &&
			rect1.x + rect1.w > rect2.x &&
			rect1.y < rect2.y + rect2.h &&
			rect1.h + rect1.y > rect2.y)

		{
			return true;
		}

		else
		{
			return false;
		}
	}
};