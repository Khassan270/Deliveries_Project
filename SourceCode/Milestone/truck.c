#define DEBUG 0

#include <stdio.h>
#include "shipment.h"
#include "truck.h"

int hasEnoughSpace(const struct Truck* tr, const struct Shipment* ship)
{
	if (!tr)
	{
		puts("Invalid Truck argument supplied!");
		return -1;
	}

	return tr->volCapacity >= ship->size && tr->weightCapacity >= ship->weight;
}

int loadShipment(struct Truck* tr, const struct Shipment* ship)
{
	int loaded = 0;

	if (hasEnoughSpace(tr, ship) && validateShipment(ship))
	{
		tr->volCapacity -= ship->size;
		tr->weightCapacity -= ship->weight;
		loaded = 1;
	}
	else
	{
#if DEBUG
		puts("Truck is full!");
#endif
	}
	return loaded;
}

int checkMoreCapacity(const struct Truck* tr1, const struct Truck* tr2)
{
	double tr1Full = 0, tr2Full = 0;

	if (tr1 == NULL) return 2; // tr2 has more capacity
	if (tr2 == NULL) return 1; // tr1 has more capacity

	// Determine limiting factor and calculate the percentage filled
	if (tr1->volCapacity / MAX_VOLUME > tr1->weightCapacity / MAX_WEIGHT)
	{
		tr1Full = (double)tr1->volCapacity / MAX_VOLUME;
	}
	else
	{
		tr1Full = (double)tr1->weightCapacity / MAX_WEIGHT;
	}

	if (tr2->volCapacity / MAX_VOLUME > tr2->weightCapacity / MAX_WEIGHT)
	{
		tr2Full = (double)tr2->volCapacity / MAX_VOLUME;
	}
	else
	{
		tr2Full = (double)tr2->weightCapacity / MAX_WEIGHT;
	}

	return tr2Full >= tr1Full ? 1 : 2;
}