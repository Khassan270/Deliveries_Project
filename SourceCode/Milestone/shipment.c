#define MAX_BOX_WEIGHT 2500

#include "shipment.h"

int validateWeight(const int weight)
{
	return weight > 0 && weight < MAX_BOX_WEIGHT;
}

int validateBox(const int size)
{
	return size == SM_BOX || size == MD_BOX || size == LG_BOX;
}

int validateDest(const struct Point* dest)
{
	if (dest->row >= 0 && dest->row < MAP_ROWS && dest->col >= 0 && dest->col < MAP_COLS)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int validateShipment(const struct Shipment* ship)
{
	if (!validateBox(ship->size))
	{
		puts("Invalid size!");
		return 0;
	}
	else if (!validateWeight(ship->weight))
	{
		printf("Invalid weight! (must be 1-%d Kg)\n", MAX_BOX_WEIGHT);
		return 0;
	}
	else if (!validateDest(&ship->dest))
	{
		puts("Invalid destination!");
		return 0;
	}
	return 1;
}