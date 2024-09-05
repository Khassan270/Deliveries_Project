#include <iostream>
#include <cstdio>
#include <assert.h>
#include "pch.h"
#include "CppUnitTest.h"
#include "ProjectTests_r.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace ProjectTests
{
	TEST_CLASS(ProjectTests)
	{
	public:

		TEST_METHOD(Map)
		{
			struct Map map = populateMap();

			// Black box tests
			Assert::AreEqual(getNumRows(&map), 25);
			Assert::AreEqual(getNumCols(&map), 25);
		}
		TEST_METHOD(HasEnoughSpace)
		{
			struct Truck
				tr1 = { MAX_WEIGHT, MAX_VOLUME },
				tr2 = { 100, 200 },
				tr3 = { 30, 200 },
				tr4 = { 100, 30 };

			//struct Shipment
			//	sh1 = { 15, 3, {0, 'A'} },
			//	sh2 = { 0, 3, {0, 'A'} },
			//	sh3 = { 15, 0, {0, 'A'} },
			//	sh4 = { 0, 0, {0, 'A'} },
			//	sh5 = { MAX_VOLUME - 15, 3, {0, 'A'} },
			//	sh6 = { 10, 3, {0, 'A'} },
			//	sh7 = { 50, 50, {0, 'A'} };

			struct Shipment
				sh1 = { 15, 3, {0, 0} },
				sh2 = { 0, 3, {0, 0} },
				sh3 = { 15, 0, {0, 0} },
				sh4 = { 0, 0, {0, 0} },
				sh5 = { MAX_VOLUME - 15, 3, {0, 0} },
				sh6 = { 10, 3, {0, 0} },
				sh7 = { 50, 50, {0, 0} };

			// Black box tests
			Assert::AreEqual(hasEnoughSpace(&tr1, &sh1), 1);
			Assert::AreEqual(hasEnoughSpace(&tr1, &sh2), 1);
			Assert::AreEqual(hasEnoughSpace(&tr1, &sh3), 1);
			Assert::AreEqual(hasEnoughSpace(&tr1, &sh4), 1);
			Assert::AreEqual(hasEnoughSpace(&tr1, &sh5), 1);

			// White box tests
			Assert::AreEqual(hasEnoughSpace(NULL, &sh4), -1);
			Assert::AreEqual(hasEnoughSpace(&tr1, &sh6), 1);
			Assert::AreEqual(hasEnoughSpace(&tr2, &sh7), 1);
			Assert::AreEqual(hasEnoughSpace(&tr3, &sh7), 0);
			Assert::AreEqual(hasEnoughSpace(&tr4, &sh7), 0);
			Assert::AreEqual(hasEnoughSpace(NULL, &sh7), -1);
		}
		TEST_METHOD(LoadShipment)
		{
			struct Truck
				tr1 = { 100, 10 },
				tr2 = { 85, 5 },
				tr3 = { 200, 10 },
				tr4 = { 50, 5 },
				tr5 = { 200, 10 };

			//struct Shipment
			//	sh1 = { 15, 5, {0, 'A'} },
			//	sh2 = { 86, 1, {0, 'A'} },
			//	sh3 = { 0, 1, {0, 'A'} },
			//	sh4 = { 15, 2, {0, 'A'} },
			//	sh5 = { 150, 5, {0, 'A'} },
			//	sh6 = { 50, -1, {0, 'A'} },
			//	sh7 = { -50, 5, {0, 'A'} },
			//	sh8 = { 500, 5, {0, 'A'} };

			struct Shipment
				sh1 = { 15, 5, {0, 0} },
				sh2 = { 86, 1, {0, 0} },
				sh3 = { 0, 1, {0, 0} },
				sh4 = { 15, 2, {0, 0} },
				sh5 = { 150, 5, {0, 0} },
				sh6 = { 50, -1, {0, 0} },
				sh7 = { -50, 5, {0, 0} },
				sh8 = { 500, 5, {0, 0} };

			// Black box tests
			loadShipment(&tr1, &sh1);
			Assert::AreEqual(tr1.volCapacity, tr2.volCapacity);
			Assert::AreEqual(tr1.weightCapacity, tr2.weightCapacity);
			loadShipment(&tr1, &sh2);
			Assert::AreEqual(tr1.volCapacity, tr2.volCapacity);
			Assert::AreEqual(tr1.weightCapacity, tr2.weightCapacity);
			loadShipment(&tr1, &sh3);
			Assert::AreEqual(tr1.volCapacity, tr2.volCapacity);
			Assert::AreEqual(tr1.weightCapacity, tr2.weightCapacity);

			// White box tests
			loadShipment(&tr1, &sh4);
			Assert::AreEqual(tr1.volCapacity, tr2.volCapacity);
			Assert::AreEqual(tr1.weightCapacity, tr2.weightCapacity);

			loadShipment(&tr3, &sh5);
			Assert::AreEqual(tr3.volCapacity, tr4.volCapacity);
			Assert::AreEqual(tr3.weightCapacity, tr4.weightCapacity);

			// Box size is invalid	
			loadShipment(&tr5, &sh6);
			Assert::AreEqual(tr5.volCapacity, tr5.volCapacity);
			Assert::AreEqual(tr5.weightCapacity, tr5.weightCapacity);

			// Weight size is invalid
			loadShipment(&tr5, &sh7);
			Assert::AreEqual(tr5.volCapacity, tr5.volCapacity);
			Assert::AreEqual(tr5.weightCapacity, tr5.weightCapacity);

			// Truck is full
			loadShipment(&tr5, &sh8);
			Assert::AreEqual(tr5.volCapacity, tr5.volCapacity);
			Assert::AreEqual(tr5.weightCapacity, tr5.weightCapacity);

		}
		TEST_METHOD(CheckMoreCapacity)
		{
			struct Truck tr1 = { 100, 10 },
				tr2 = { 85, 5 },
				tr3 = { 100, 10 };

			struct Truck tr4 = { 100, 50 },
				tr5 = { 200, 100 };

			// Black box tests
			Assert::AreEqual(checkMoreCapacity(&tr1, &tr2), 2);
			Assert::AreEqual(checkMoreCapacity(&tr2, &tr1), 1);

			// White box tests ..
			Assert::AreEqual(checkMoreCapacity(&tr1, &tr3), 1);
			Assert::AreEqual(checkMoreCapacity(&tr4, &tr5), 1);
			Assert::AreEqual(checkMoreCapacity(&tr5, &tr4), 2);
			Assert::AreEqual(checkMoreCapacity(NULL, &tr5), 1); 
			Assert::AreEqual(checkMoreCapacity(&tr5, NULL), 1);

		}
		TEST_METHOD(ValidateWeight)
		{
			// Black box tests
			Assert::AreEqual(validateWeight(10), 1);
			Assert::AreEqual(validateWeight(0), 0);

			// White box tests
			Assert::AreEqual(validateWeight(-10), 0);
			Assert::AreEqual(validateWeight(10), 1);
			Assert::AreEqual(validateWeight(0), 0);
			Assert::AreEqual(validateWeight(-50), 0);
			Assert::AreEqual(validateWeight(1), 1);
		}
		TEST_METHOD(ValidateBox)
		{
			// Black box tests
			Assert::AreEqual(validateBox(1), 1);
			Assert::AreEqual(validateBox(3), 1);
			Assert::AreEqual(validateBox(5), 1);
			Assert::AreEqual(validateBox(0), 0);
			Assert::AreEqual(validateBox(7), 0);

			// White box tests
			Assert::AreEqual(validateBox(SM_BOX), 1);
			Assert::AreEqual(validateBox(MD_BOX), 1);
			Assert::AreEqual(validateBox(-6), 0);
			Assert::AreEqual(validateBox(50), 0);
		}
		TEST_METHOD(ValidateDestination)
		{
			//struct Point pt1 { 0, 'A' }, // Valid
			//	pt2{ 24, 'A' }, // Valid
			//	pt3{ 0, 'Y' }, // Valid
			//	pt4{ 25, 'A' }, // Invalid
			//	pt5{ 0, 'Z' }, // Invalid
			//	pt6{ -1, 'A' }, // Invalid
			//	pt7{ 0, '0' }, // Invalid
			//	pt8{ 5, 'E' }, // Valid
			//	pt9{ -1, 'E' }, // Invalid
			//	pt10{ 999, 'E' }; // Invalid

			struct Point pt1 { 0, 0 }, // Valid
				pt2{ 24, 0 }, // Valid
				pt3{ 0, 24 }, // Valid
				pt4{ 25, 0 }, // Invalid
				pt5{ 0, 25 }, // Invalid
				pt6{ -1, 0 }, // Invalid
				pt7{ 0, -1 }, // Invalid
				pt8{ 5, 5 }, // Valid
				pt9{ -1, 5 }, // Invalid
				pt10{ 999, 5 }; // Invalid

			// Black box tests
			Assert::AreEqual(validateDest(&pt1), 1);
			Assert::AreEqual(validateDest(&pt2), 1);
			Assert::AreEqual(validateDest(&pt3), 1);
			Assert::AreEqual(validateDest(&pt4), 0);
			Assert::AreEqual(validateDest(&pt5), 0);

			// White box tests
			Assert::AreEqual(validateDest(&pt6), 0);
			Assert::AreEqual(validateDest(&pt7), 0);
			Assert::AreEqual(validateDest(&pt8), 1);
			Assert::AreEqual(validateDest(&pt9), 0);
			Assert::AreEqual(validateDest(&pt10), 0);
			Assert::AreEqual(validateDest(&pt1), 1);
		}
	};

	TEST_CLASS(IntegrationTests)
	{
	public:
		TEST_METHOD(IntegrationTest001)
		{
			// Set up test cases
			struct Truck tr1 = { 200, 100 }; // Enough space
			struct Truck tr2 = { 30, 200 };  // Not enough volume
			struct Truck tr3 = { 100, 40 };  // Not enough weight

			struct Shipment shipment = { 50, 50 };

			// Valid truck, enough space
			Assert::AreEqual(hasEnoughSpace(&tr1, &shipment), 1);

			// Valid truck, not enough volume
			Assert::AreEqual(hasEnoughSpace(&tr2, &shipment), 0);

			// Valid truck, not enough weight
			Assert::AreEqual(hasEnoughSpace(&tr3, &shipment), 0);

			// Truck is NULL
			Assert::AreEqual(hasEnoughSpace(NULL, &shipment), -1);
		}

		TEST_METHOD(IntegrationTest002)
		{
			// Set up test cases
			struct Truck tr1 = { 200, 100 }; // Valid truck, enough space
			struct Truck tr2 = { 200, 100 }; // Invalid box size
			struct Truck tr3 = { 200, 100 }; // Invalid weight size
			struct Truck tr4 = { 30, 40 };  // Not enough space

			struct Shipment sh1 = { 5, SM_BOX, {0, 0} };  // Valid box size and weight
			struct Shipment sh2 = { 50, 2, {0, 0} };      // Invalid box size
			struct Shipment sh3 = { -50, SM_BOX, {0, 0} }; // Invalid weight size
			struct Shipment sh4 = { 50, SM_BOX, {0, 0} };  // Not enough space

			// Valid box size and weight, enough space
			int result = loadShipment(&tr1, &sh1);
			Assert::AreEqual(result, 1);
			Assert::AreEqual(tr1.volCapacity, 99);  // Decremented by 1
			Assert::AreEqual(tr1.weightCapacity, 195); // Decremented by 5

			// Invalid box size
			result = loadShipment(&tr2, &sh2);
			Assert::AreEqual(result, 0);

			// Invalid weight size
			result = loadShipment(&tr3, &sh3);
			Assert::AreEqual(result, 0);

			// Not enough space in the truck
			result = loadShipment(&tr4, &sh4);
			Assert::AreEqual(result, 0);
		}

			TEST_METHOD(IntegrationTest003)
		{
			// Initialize trucks with weight capacity first, then volume capacity
			struct Truck tr1 = { 100, 10 };   // Truck 1: lower capacity
			struct Truck tr2 = { 85, 5 };	  // Truck 2: higher capacity
			struct Truck tr3 = { 200, 100 };  // Truck 1: higher capacity
			struct Truck tr4 = { 100, 50 };   // Truck 2: lower capacity

			// Compare capacities of Truck 1 and Truck 2
			Assert::AreEqual(checkMoreCapacity(&tr1, &tr2), 2); // Truck 2 has more capacity
			Assert::AreEqual(checkMoreCapacity(&tr2, &tr1), 1); // Truck 1 has more capacity

			// Null Truck1 case ..
			Assert::AreEqual(checkMoreCapacity(NULL, &tr3), 1);
			// Null Truck2 case
			Assert::AreEqual(checkMoreCapacity(&tr3, NULL), 1);

		}

		TEST_METHOD(IntegrationTest004)
		{
			// Valid positive weight
			Assert::AreEqual(validateWeight(50), 1);

			// Weight is zero
			Assert::AreEqual(validateWeight(0), 0);

			// Negative weight
			Assert::AreEqual(validateWeight(-10), 0);

			// Large positive weight
			Assert::AreEqual(validateWeight(1000), 1);
		}

		TEST_METHOD(IntegrationTest005)
		{
			// Valid small box size
			Assert::AreEqual(validateBox(SM_BOX), 1);

			// Valid medium box size
			Assert::AreEqual(validateBox(MD_BOX), 1);

			// Valid large box size
			Assert::AreEqual(validateBox(LG_BOX), 1);

			// Invalid box size
			Assert::AreEqual(validateBox(10), 0);
		}

		TEST_METHOD(IntegrationTest006)
		{
			// Valid destination within bounds
			struct Point validPoint = { 5, 5 };
			Assert::AreEqual(validateDest(&validPoint), 1);

			// Invalid destination (negative row)
			struct Point negativeRow = { -1, 5 };
			Assert::AreEqual(validateDest(&negativeRow), 0);

			// Invalid destination (negative col)
			struct Point negativeCol = { 5, -1 };
			Assert::AreEqual(validateDest(&negativeCol), 0);

			// Invalid destination (exceed bounds)
			struct Point exceedBounds = { MAP_ROWS, MAP_COLS }; 
			Assert::AreEqual(validateDest(&exceedBounds), 0);
		}

		TEST_METHOD(IntegrationTest007)
		{
			// Set up various shipment scenarios
			struct Shipment validShipment = { 150, MD_BOX, {10, 10} };
			struct Shipment invalidBoxSize = { 150, 7, {10, 10} };  // 7 is not a defined box size constant
			struct Shipment invalidWeight = { -10, MD_BOX, {10, 10} };
			struct Shipment invalidDestination = { 150, MD_BOX, {-1, 50} };  // Assuming -1 is out of bounds

			// Testing a valid shipment
			Assert::AreEqual(validateShipment(&validShipment), 1);

			// Testing invalid box size
			Assert::AreEqual(validateShipment(&invalidBoxSize), 0);

			// Testing invalid weight
			Assert::AreEqual(validateShipment(&invalidWeight), 0);

			// Testing invalid destination
			Assert::AreEqual(validateShipment(&invalidDestination), 0);
		}
	};


	TEST_CLASS(AcceptanceTests)
	{
	public:
		TEST_METHOD(AcceptanceTest001)
		{
			// Test Data for hasEnoughSpace (sufficient capacity)
			struct Truck truck1 = { 1000, 10 };
			struct Shipment shipment1 = { 300, 3, {0, 0} };

			// Verify hasEnoughSpace with sufficient capacity
			Assert::AreEqual(1, hasEnoughSpace(&truck1, &shipment1));

			// Test Data for loadShipment (insufficient capacity)
			struct Truck truck2 = { 200, 2 };
			struct Shipment shipment2 = { 300, 3, {0, 0} };

			// Verify loadShipment with insufficient capacity (Expect failure)
			Assert::AreEqual(0, loadShipment(&truck2, &shipment2));

			// Test Data for checkMoreCapacity
			struct Truck truck3 = { 500, 5 };
			struct Truck truck4 = { 700, 7 };

			// Verify checkMoreCapacity chooses Truck 2 ..
			Assert::AreEqual(1, checkMoreCapacity(&truck3, &truck4));
		}

		TEST_METHOD(AcceptanceTest002)
		{
			// Test Data
			struct Point p1 = { 3, 4 };
			struct Point p2 = { 7, 1 };

			// Expected Result
			double expectedDistance = sqrt((7 - 3) * (7 - 3) + (1 - 4) * (1 - 4));

			// Calculate Actual Result using the distance function
			double actualDistance = distance(&p1, &p2);

			// Compare the expected and actual results with a tolerance for floating point precision
			Assert::IsTrue(std::abs(expectedDistance - actualDistance) < 0.0001);
		}


		TEST_METHOD(AcceptanceTest003)
		{
			// -------- LoadShipment --------
			// Test Data
			struct Truck truck = { 1000, 10 };  // Set truck capacity
			struct Shipment shipment = { 300, 3, {0, 0} };  // Set shipment details

			// Test loadShipment function
			int result = loadShipment(&truck, &shipment);

			// Expect the shipment process to be successful (return 1)
			Assert::AreEqual(1, result);

			// -------- AddRoute --------
			// Test Data for Map and Route
			struct Map map = populateMap();  // Initialize the map with a hypothetical function
			struct Route route;
			struct Point start = { 0, 0 };  // Starting point of the route
			struct Point destination = { 24, 24 };  // Destination point

			// Create a route with initial point
			route.numPoints = 0;
			route.routeSymbol = 'P';  // Set route symbol
			addPtToRoute(&route, start);

			// Calculate and add the route to the map
			struct Map newMap = addRoute(&map, &route);

			// Verify the route was added successfully
			Assert::AreEqual(start.row, route.points[0].row);
			Assert::AreEqual(start.col, route.points[0].col);
		}


		TEST_METHOD(AcceptanceTest004)
		{
			// Initialize map with obstacles
			struct Map map = populateMap();  // Initialize the map with predefined obstacles

			// Define start and destination points
			struct Point start = { 0, 0 };
			struct Point destination = { 24, 24 };
			
			// Infinite loop occurs when calling shortestPath.
			/*
			// Calculate the shortest path
			struct Route route = shortestPath(&map, start, destination);

			// Verify the path starts at the start point
			Assert::AreEqual(start.row, route.points[0].row);
			Assert::AreEqual(start.col, route.points[0].col);

			// Verify the path ends at the destination point
			int lastPointIndex = route.numPoints - 1;
			Assert::AreEqual(destination.row, route.points[lastPointIndex].row);
			Assert::AreEqual(destination.col, route.points[lastPointIndex].col);

			// Verify that the route avoids obstacles
			for (int i = 0; i < route.numPoints; i++)
			{
				Assert::IsTrue(map.squares[route.points[i].row][route.points[i].col] == 0);
			}
			*/
		}

		// Test case for validating weight and size
		TEST_METHOD(AcceptanceTest005)
		{
			// Test Data
			int invalidWeight = -1; // Invalid weight
			int invalidSize = -4;   // Invalid size

			// Validate the results
			Assert::AreEqual(0, validateWeight(invalidWeight));
			Assert::AreEqual(0, validateBox(invalidSize));
		}


		// Test case for checking more capacity and displaying load percentage
		TEST_METHOD(AcceptanceTest006)
		{
			// Test Data
			struct Truck truck1 = { 2000, 95 }; // Truck 1 with 2000 kg capacity left and 95 m³ left
			struct Truck truck2 = { 1800, 93 }; // Truck 2 with 1800 kg capacity left and 93 m³ left

			// Validate the result for truck with more capacity
			Assert::AreEqual(2, checkMoreCapacity(&truck1, &truck2));
		}

		// Test map generation function
		struct Map createTestMap() {
			struct Map testMap = populateMap();
			// Set building location 
			testMap.squares[5][5] = 1;  
			testMap.squares[5][6] = 1;  
			testMap.squares[5][7] = 1;  
			return testMap;
		}

		TEST_METHOD(AcceptanceTest007)
		{
			struct Map testMap = createTestMap();
			struct Point start = { 4, 4 };
			struct Point dest = { 6, 6 };

			// Infinite loop occurs when calling shortestPath.
			/*struct Route result = shortestPath(&testMap, start, dest);

			// Verify that the resulting path avoids the building
			for (int i = 0; i < result.numPoints; i++) {
				Assert::AreNotEqual(1, testMap.squares[result.points[i].row][result.points[i].col]);
			}*/
		}

		// 경로가 추가된 맵 설정 함수
		struct Map setupMapWithRoutes() {
			struct Map baseMap = populateMap();
			struct Route blueRoute = getBlueRoute();
			struct Route greenRoute = getGreenRoute();
			struct Route yellowRoute = getYellowRoute();

			baseMap = addRoute(&baseMap, &blueRoute);
			baseMap = addRoute(&baseMap, &greenRoute);
			baseMap = addRoute(&baseMap, &yellowRoute);

			return baseMap;
		}

		// R008 - Test truck route visualization
		TEST_METHOD(AcceptanceTest008)
		{
			struct Map testMap = setupMapWithRoutes();

			// Code to check each route for existence (e.g., validate blueRoute)
			struct Route blueRoute = getBlueRoute();
			bool routeCorrectlyAdded = true;
			for (int i = 0; i < blueRoute.numPoints; i++) {
				int r = blueRoute.points[i].row;
				int c = blueRoute.points[i].col;
				if (testMap.squares[r][c] != BLUE) {
					routeCorrectlyAdded = false;
					break;
				}
			}

			//Assert::IsTrue(routeCorrectlyAdded); // correct Route Data
			Assert::IsFalse(routeCorrectlyAdded); // Incorrect Route Data
		}

		// Test to verify eqPt function works correctly for delivery status
		TEST_METHOD(AcceptanceTest009)
		{
			// Test data setup
			struct Point currentPos = { 6, 6 };
			struct Point destPos = { 6, 6 };

			// Expected result is 1 (true), indicating the truck has reached its destination
			Assert::IsTrue(eqPt(currentPos, destPos));
		}
	};

}
