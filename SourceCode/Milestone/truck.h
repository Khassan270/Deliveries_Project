#pragma once
#ifndef TRUCK_H
#define TRUCK_H
#include "shipment.h"

#define MAX_WEIGHT 2500
#define MAX_VOLUME 100

struct Truck 
{
	int weightCapacity;
	int volCapacity;
};
/**
* Checks if the Truck has enough space to hold the cargo.
* @param tr - the truck being checked
* @param ship - the Shipment to be loaded
* @returns 1 if the Truck has enough space, 0 if not, -1 if it is invalid.
*/
int hasEnoughSpace(const struct Truck* tr, const struct Shipment* ship);

/**
* Loads the cargo on the truck by subtracting the weight and volume capacity of the Truck.
* @param tr - the Truck being loaded
* @param ship - the Shipment to be loaded
* @returns 1 if loaded successfully, 0 otherwise
*/
int loadShipment(struct Truck* tr, const struct Shipment* ship);

/**
* Checks which of the trucks has more capacity
* @param tr1 - the first truck
* @param tr2 - the second truck
* @returns the truck number (1 or 2) that has more capacity, if they are equal returns 1.
*/
int checkMoreCapacity(const struct Truck* tr1, const struct Truck* tr2);

#endif // !TRUCK_H
