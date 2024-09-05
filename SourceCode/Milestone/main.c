#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "mapping.h"
#include "truck.h"
#include "shipment.h"

void clearInputBuffer();

int getUserInput(struct Shipment* ship);

int main(void)
{

	struct Route blueRoute = getBlueRoute();
	struct Route greenRoute = getGreenRoute();
	struct Route yellowRoute = getYellowRoute();

	/*struct Map routeMap = addRoute(&baseMap, &blueRoute);
	routeMap = addRoute(&routeMap, &greenRoute);
	routeMap = addRoute(&routeMap, &yellowRoute);*/

	struct Truck
		blueTruck = { MAX_WEIGHT, MAX_VOLUME },
		greenTruck = { MAX_WEIGHT, MAX_VOLUME },
		yellowTruck = { MAX_WEIGHT, MAX_VOLUME };

	struct Route* selectedRoute = NULL;
	struct Truck* selectedTruck = NULL;
	struct Shipment ship = { 0 };

	int moreShips = 1, blueClosest, greenClosest, yellowClosest, selectedClosest;
	double blueDist, greenDist, yellowDist, minDist;

	//printMap(&routeMap, 1, 1);

	puts("=================");
	puts("Seneca Polytechnic Deliveries");
	puts("=================");


	do {
		moreShips = getUserInput(&ship);

		selectedTruck = NULL;
		struct Route divertRoute = { 0 };

		// Find the closest point on each route for the Shipment's destination
		blueClosest = getClosestPoint(&blueRoute, ship.dest);
		greenClosest = getClosestPoint(&greenRoute, ship.dest);
		yellowClosest = getClosestPoint(&yellowRoute, ship.dest);

		// Calculate the distances on each route
		blueDist = distance(&blueRoute.points[blueClosest], &ship.dest);
		greenDist = distance(&greenRoute.points[greenClosest], &ship.dest);
		yellowDist = distance(&greenRoute.points[greenClosest], &ship.dest);

		// Find the nearest route
		minDist = blueDist;
		selectedTruck = &blueTruck;
		selectedRoute = &blueRoute;
		selectedClosest = blueClosest;

		if (greenDist < minDist ||
			(greenDist == minDist && checkMoreCapacity(selectedTruck, &greenTruck) == 2))
		{
			minDist = greenDist;
			selectedTruck = &greenTruck;
			selectedRoute = &greenRoute;
			selectedClosest = greenClosest;
		}

		if (yellowDist < minDist ||
			(yellowDist == minDist && checkMoreCapacity(selectedTruck, &yellowTruck) == 2))
		{
			minDist = yellowDist;
			selectedTruck = &yellowTruck;
			selectedRoute = &yellowRoute;
			selectedClosest = yellowClosest;
		}
				/*divertRoute = shortestPath(&selectedRoute, selectedRoute->points[selectedClosest], ship.dest);
				printf("%d%c ", divertRoute.points[0].row, 'A' + divertRoute.points[0].col);*/


		// Try to load the shipment to the selected truck
		if (loadShipment(selectedTruck, &ship))
		{
			// Check if the Truck needs to divert from its route
			if (minDist > 1)
			{
				struct Map baseMap = populateMap();
				//addRoute(&baseMap, &selectedRoute);
				divertRoute = shortestPath(&selectedRoute, selectedRoute->points[selectedClosest], ship.dest);

				printf("Ship on %s LINE, divert: ",
					selectedTruck == &blueTruck ? "BLUE" :
					selectedTruck == &greenTruck ? "GREEN" :
					"YELLOW");

				for (int i = 0; i < divertRoute.numPoints; i++)
					printf("%d%c ", divertRoute.points[i].row, 'A' + divertRoute.points[i].col);
				putchar('\n');
			}
			else
			{
				printf("Ship on %s LINE, no diversion\n", 
					selectedTruck == &blueTruck ? "BLUE" : 
					selectedTruck == &greenTruck ? "GREEN" : 
					"YELLOW");
			}
		}
		else
		{
			puts("Ships Tomorrow");
		}
	} while (moreShips);

	return 0;
}

void clearInputBuffer()
{
	while (getchar() != '\n');
}

int getUserInput(struct Shipment* ship)
{
	int weight, size, row, valid, moreShips = 1;
	char col;

	do {
		valid = 0;
		printf("Enter shipment weight, box size and destination (0 0 x to stop): ");

		scanf("%d %d ", &weight, &size);

		if (!weight && !size)
		{
			scanf("%c", &col);

			if (col == 'x')
				moreShips = 0;
			else
				puts("Invalid input!");
		}
		else
		{
			scanf("%d%c", &row, &col);

			ship->weight = weight;
			ship->size = size;
			ship->dest.row = row;
			ship->dest.col = col - 'A';

			if (validateShipment(ship))
				valid = 1;
		}
		clearInputBuffer();
	} while (!valid && moreShips);

	return moreShips;
}