#include "../include/Randomer.hpp"


int Randomer::RandomRangei(int left, int right)
{
	srand((unsigned) time(NULL));

	int output = left + (rand() % right);

	return output;
}


