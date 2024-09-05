#pragma once
#ifndef SHIPMENT_H
#define SHIPMENT_H
#include "mapping.h"

#define SM_BOX 1
#define MD_BOX 3
#define LG_BOX 5

struct Shipment
{
	int weight;
	int size;
	struct Point dest;
};

/* *
* Vaidates that the weight is valid.
* @param size - the weight of the box to be validated
* @returns 1 if the weight is valid, 0 if invalid
*/
int validateWeight(const int weight);

/* *
* Vaidates that the box size is within parameters.
* @param size - the size of the box to be validated
* @returns 1 if the box size is valid, 0 if invalid
*/
int validateBox(const int size);

/* *
* Validates that the destination is within the map's bounds.
* @param dest - the destination to be validated
* @returns 1 if the destination is valid, 0 otherwise
*/
int validateDest(const struct Point* dest);

/* *
* Validates that the shipment is valid.
* @param ship - the shipment to be validated
* @returns 1 if the shipment is valid, 0 otherwise
*/
int validateShipment(const struct Shipment* ship);

#endif // !SHIPMENT_H
