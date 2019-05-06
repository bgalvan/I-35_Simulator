#include "Utilities.h"
#include "Highway.h"
#include "Vehicles.h"
#include "Lane.h"
#include "Node.h"
#include <fstream>
#include <iostream>
using namespace std;

const int NumberOfHighways = 4;
const int NumberOfLines = 4; // # of lines per highway -- 4 lines = 3 lanes for cars
const int NumberOfCars = 100;
const int NumberOfLanes = NumberOfLines - 1;

///////////////////////////////////////////////////////
int ActQueue[NumberOfHighways][NumberOfLines - 1]; // Queue for spawning in cars
int FC = 0;
bool SHW = true;
Highway Highways[NumberOfHighways];
Vehicle Vehicles[NumberOfCars];
Lane Lanes[NumberOfHighways][NumberOfLanes];


		
///////////////////////////////////////////////////////


void animate() {
	// Randomizer CONFIG //

	if(SHW) {
		for(int i = 0; i <= NumberOfHighways - 1; ++i) {
			// This will set the properties for each highway drawn on the console
			Highways[i].name = "Highway" + i;
			Highways[i].lanes = NumberOfLines; // Number of lanes for each highway -- If you change this you need to change the yaxis too bellow to more than 95
			Highways[i].yaxis = WINDOW_HEIGHT - (i * (Highways[i].lanes * 20) + (20 * (i + 1) ) ); // This is setup to user whatever is set for the config
			Highways[i].SetSpawns(); // Sets the spawn points for the Highways
			//outfile << Highways[i].yaxis << std::endl;
		}
		
		for(int i = 0; i <= NumberOfCars - 1; ++i) {
			// Randomize cars here!! Set the variables here for the first time for the objects. This will give cars different speeds
			Vehicles[i].lane = random(0, Highways[0].lanes - 2); // chooses what lane to spawn in
			Vehicles[i].xSpeed = random(2, 5); // Random Speed for each object
			//Vehicles[i].color = random(1, 20); // Random Color for each car -- does not work yet, look at vehicles.cpp inside the draw funtion is where the color is currently set.
			Vehicles[i].desiredSpeed = random(3, 10);
			Vehicles[i].setPosition( 0, Highways[Vehicles[i].highwayid].Spawns[Vehicles[i].lane] );
	
		}

		SHW = false;
	}
	//  END CONFIG //
	for(int i = 0; i <= NumberOfCars - 1; ++i) { 
		if( Vehicles[i].active != true && ActQueue[Vehicles[i].highwayid][Vehicles[i].lane] == 0 ) {
			
			Vehicles[i].active = true;
			ActQueue[Vehicles[i].highwayid][Vehicles[i].lane] = 1; // This lets us know if the entrance is busy or not. ( Stops multiple cars from spawning in the same lane at the same time.)
			Vehicles[i].setPosition( Vehicles[i].xPos + Vehicles[i].xSpeed, Highways[Vehicles[i].highwayid].Spawns[Vehicles[i].lane] );
			//add to linked list
			Lanes[Vehicles[i].highwayid][Vehicles[i].lane].addItem(i);
			//use link list to get index of car in front (needs testing)
			Vehicles[i].carAheadIndex = Lanes[Vehicles[i].highwayid][Vehicles[i].lane].getNextInLane(i);
			// cout << "this car is: " << i 
			// << "  color is: " << Vehicles[i].color
			// << "  Next car data is: " 
			// << Vehicles[i].carAheadIndex 
			// << "  color is: " << Vehicles[Vehicles[i].carAheadIndex].color
			// << endl;
		} else if( Vehicles[i].active == true && Vehicles[i].xPos <= WINDOW_WIDTH ) {
			Vehicles[i].setPosition( Vehicles[i].xPos + Vehicles[i].xSpeed, Highways[Vehicles[i].highwayid].Spawns[Vehicles[i].lane] );
			if (Vehicles[i].carAheadIndex != -1){
				int j = Vehicles[i].carAheadIndex;
				if (Vehicles[j].xPos - Vehicles[i].xPos < 25) {
					Vehicles[i].xSpeed = Vehicles[j].xSpeed - 1;
					if (Vehicles[i].xSpeed <= 0)
						Vehicles[i].xSpeed = 0;
					Vehicles[i].tolerance += 1;
					if (Vehicles[i].desiredSpeed > Vehicles[j].xSpeed && Vehicles[i].tolerance == 30){
						Vehicles[i].tolerance = 0;
						//decide which lane to move into
						int desiredLane = -1;
						int flip = random(0,1);
						// cout << "flip" << flip << endl;
						if (Vehicles[i].lane == NumberOfLanes-1)
							desiredLane = Vehicles[i].lane - 1;
						else if (0 < Vehicles[i].lane && Vehicles[i].lane < NumberOfLanes-1)
							if (flip == 1){
								desiredLane = Vehicles[i].lane - 1;
							}
							else {
								desiredLane = Vehicles[i].lane + 1;
							}
						else{
							desiredLane = Vehicles[i].lane + 1;
						}

						// cout << "desired lane: " << desiredLane << endl;

						//get carBehind of current lane
						int carBehind = Lanes[Vehicles[i].highwayid][Vehicles[i].lane].getCarBehind(i);
						// cout << "This : " << i;
						// if (carBehind != -1){
							// cout << " car behind : " << carBehind
							// << " carAhead of carbehind: " << Vehicles[carBehind].carAheadIndex;
							// cout << "This car xPos: " << Vehicles[i].xPos;
						
							// cout << " Car behind index: " << carBehind << " Car Behind xPos: " << Vehicles[carBehind].xPos;
						// }
						//check desired lane to get indexes of nearest cars
						Node * ptr2;
						ptr2 = Lanes[Vehicles[i].highwayid][desiredLane].getList();
						int carOverAhead;
						int carOverBehind;
						//list is empty, set values to -1
						if (ptr2 == NULL){
							carOverAhead = -1;
							carOverBehind = -1;
						}
						//list is not empty
						else{
							//check if head of lane over is ahead of this car, so no cars will be behind it.
							if (Vehicles[ptr2->getData()].xPos >= Vehicles[i].xPos){
								carOverAhead = ptr2->getData();
								carOverBehind = -1;
								// cout << "Only car ahead and over: " << carOverAhead;
							}
							else{
								while(ptr2 != NULL){
									int index = ptr2->getData();
									if (Vehicles[index].xPos < Vehicles[i].xPos)
										carOverBehind = index;
									else
										break;
									ptr2 = ptr2->getNext();
								}
								carOverAhead = Lanes[Vehicles[i].highwayid][desiredLane].getNextInLane(carOverBehind);
								// cout << "Car ahead over: " << carOverAhead
								// << " Car behind over: " << carOverBehind;
							}
						}
						// cout << "car over behind: " << carOverBehind << endl;
						// cout << "car over ahead: " << carOverAhead << endl;
						// if (carOverAhead != -1){
							// cout << "This car xPos: " << Vehicles[i].xPos << endl;
							// cout << " Car over ahead: " << Vehicles[carOverAhead].xPos << endl;
						// }
						// if (carOverBehind != -1){
							// cout << "This car xPos: " << Vehicles[i].xPos << endl;
							// cout << " Car over behind: " << Vehicles[carOverBehind].xPos << endl;
						// }

						//check distances
					

						//PASSING
						//If lane over is empty
						if (carOverAhead == -1 && carOverBehind == -1){
							//remove from current lane linked list
							Lanes[Vehicles[i].highwayid][Vehicles[i].lane].removeFromFront(i);
							//add to new lane linked list
							Lanes[Vehicles[i].highwayid][desiredLane].addItem(i);
							//set position to new lane
							Vehicles[i].lane = desiredLane;
							//reset carAheadIndex of original carBehind
							Vehicles[carBehind].carAheadIndex = Vehicles[i].carAheadIndex;
							//reset carAheadIndex of this car
							Vehicles[i].carAheadIndex = -1;
							// cout << "car" << i << "changed lanes";
						} 

						 //If there is only a car behind and over
						 if (carOverBehind != -1){
							if ( carOverAhead == -1 && Vehicles[i].xPos - Vehicles[carOverBehind].xPos > 30){
								//remove from current lane linked list
								Lanes[Vehicles[i].highwayid][Vehicles[i].lane].removeFromFront(i);
								//add to new lane linked list at end (front)
								Lanes[Vehicles[i].highwayid][desiredLane].insertAfter(carOverBehind, i);
								//set position to new lane
								Vehicles[i].lane = desiredLane;
								//reset carAheadIndex of original carBehind
								Vehicles[carBehind].carAheadIndex = Vehicles[i].carAheadIndex;
								//set carAheadIndex of new carBehind to this car
								Vehicles[carOverBehind].carAheadIndex = i;
								//reset carAheadIndex of this car
								Vehicles[i].carAheadIndex = -1;
							} 
						 } 
						//if there is only a car ahead and over
						if (carOverAhead != -1){
							if ( carOverBehind == -1 && Vehicles[carOverAhead].xPos - Vehicles[i].xPos > 30){
								//remove from current lane linked list
								Lanes[Vehicles[i].highwayid][Vehicles[i].lane].removeFromFront(i);
								//add to new lane linked list, make head
								Lanes[Vehicles[i].highwayid][desiredLane].addItem(i);
								//set position to new lane
								Vehicles[i].lane = desiredLane;
								// reset carAheadIndex of original carBehind
								Vehicles[carBehind].carAheadIndex = Vehicles[i].carAheadIndex;
								//reset carAheadIndex of this car
								Vehicles[i].carAheadIndex = carOverAhead;
							}
						}
						 //if there is both a car behind&over and ahead&over
						if (carOverAhead != -1){
							if (carOverAhead != -1){
								if (Vehicles[carOverAhead].xPos - Vehicles[i].xPos > 15 && Vehicles[i].xPos - Vehicles[carOverBehind].xPos > 15){
									//remove from current lane linked list
									// cout << "first lane change: " << endl;
									// Lanes[Vehicles[i].highwayid][Vehicles[i].lane].print();
									Lanes[Vehicles[i].highwayid][Vehicles[i].lane].removeFromFront(i);
									// Lanes[Vehicles[i].highwayid][Vehicles[i].lane].print();
									//add to new lane linked list
									// cout << "second lane change: " << endl;
									// Lanes[Vehicles[i].highwayid][desiredLane].print();
									Lanes[Vehicles[i].highwayid][desiredLane].insertAfter(carOverBehind, i);
									// Lanes[Vehicles[i].highwayid][desiredLane].print();
									//set position to new lane
									Vehicles[i].lane = desiredLane;
									//reset carAheadIndex of original carBehind
									Vehicles[carBehind].carAheadIndex = Lanes[Vehicles[i].highwayid][Vehicles[carBehind].lane].getNextInLane(carBehind);
									//reset carAheadIndex of this car
									Vehicles[i].carAheadIndex = carOverAhead;
								} 
							}
						}
					}

				}
			}

			if (Vehicles[i].xSpeed < Vehicles[i].desiredSpeed){
				if (Vehicles[i].carAheadIndex == -1)
					Vehicles[i].xSpeed++;
				else{
					if (Vehicles[Vehicles[i].carAheadIndex].xPos - Vehicles[i].xPos > 20)
						Vehicles[i].xSpeed++;
				}

			}

		} else if(Vehicles[i].xPos >= WINDOW_WIDTH) {
			Vehicles[i].active = false;
			//reset carhead index of carbehind
			int lastCar = Lanes[Vehicles[i].highwayid][Vehicles[i].lane].getCarBehind(i);
			if (lastCar != -1)
				Vehicles[lastCar].carAheadIndex = -1;
			//remove from linked list
			Lanes[Vehicles[i].highwayid][Vehicles[i].lane].removeFromFront(i);
			Vehicles[i].highwayid = Vehicles[i].highwayid + 1;
			Vehicles[i].setPosition( 0, Highways[Vehicles[i].highwayid].Spawns[Vehicles[i].lane] );
			if(Vehicles[i].highwayid > (NumberOfHighways - 1)) {
				Vehicles[i].highwayid = 0;
				Vehicles[i].setPosition( 0, Highways[Vehicles[i].highwayid].Spawns[Vehicles[i].lane] );
			}
		}



		
		// If funtion whipes spawn queue but leaves enough space to have the cars spawn in.
		if(i == NumberOfCars - 1) {
			if(FC == 2) {
				FC = 0;
				for(int t = 0; t <= NumberOfLines - 2; ++t) {
					ActQueue[Vehicles[i].highwayid][Vehicles[t].lane] = 0;
				}
			} else {
				FC++;
			} 
		} 
	}

	// lanes[Vehicles[i].lane].numberofcars = 0;
	glutPostRedisplay(); // This runs DisplayInit again
	pause_ms(16); // A small delay is needed.
}

// keyboard handler to terminate the program when "q" key is pressed
void handleKey(unsigned char key, int x, int y) {
    switch(key) {
        case 'q':
            exit(0);
            break;
    }
}

// THIS FUNTION DISPLAYS EVERYTHING
void DisplayInit() {
	clearWindow();
	for (int i = 0; i <= NumberOfHighways - 1; ++i) {
		Highways[i].draw();
	}
	
	for(int i = 0; i <= NumberOfCars - 1; ++i) {
		if(Vehicles[i].active) {
			Vehicles[i].move();
		}
	}
	glutSwapBuffers();
}

int main(int argc, char **argv) {
	seed();
	StartHighway(argc, argv); // This sets up GLUT in the highway file
    glutDisplayFunc(DisplayInit); // Sets default funtion to run to draw the screen.
    glutIdleFunc(animate);          // Runs listed funtion constantly in a loop so any variables 
    glutKeyboardFunc(handleKey);    // set up the "q" key to quit
    glutMainLoop();                 // GLUT will control the action
    //glutSwapBuffers();              // double buffering control
}
