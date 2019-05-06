#include "Utilities.h"
#include "Vehicles.h"
#include "Highway.h"
#include <string>
#include <sstream>
using namespace std;

Vehicle::Vehicle() {
	size = 4;       // how big should this vehicle be
	xPos = 0;       // screen position in pixels
	yPos = 470;       
	xSpeed = 5;
	ySpeed = 10;
	desiredSpeed = 10;

	// this->nextCar = NULL;
	// this->prevCar = NULL;

	highwayid = 0;
	lane = 0;
	preferred_lane = 1;
	active = false; // this lets us know if the car is on the highway.
	color = random(1, 13);
	carAheadIndex = -1;
	// carBehindIndex = -1;
	tolerance = 0;
	
}
void Vehicle::setPosition( int x, int y ) {
	xPos = x;
	yPos = y;
}

void Vehicle::setSpeed( int xv, int yv ) {
	xSpeed = xv;
	ySpeed = yv;
}

void Vehicle::move( void ) {
	setColor(color);
	drawFilledCircle(xPos,yPos,size);
}

// string Vehicle::getColor( void ){
// 	stringstream ss;
// 	if (color = 1){
// 		ss << "black";
// 	};
// 	if (color = 2){
// 		ss << "black";
// 	};
// 	if (color = 3){
// 		ss << "black";
// 	};
// 	if (color = 4){
// 		ss << "red";
// 	};
// 	if (color = 5){
// 		ss << "orange";
// 	};
// 	if (color = 6){
// 		ss << "yellow";
// 	};
// 	if (color = 7){
// 		ss <<"light green";
// 	};
// 	if (color = 8){
// 		ss << "dark green";
// 	};
// 	if (color = 9){
// 		ss << "black";
// 	};
// 	if (color = 10){
// 		ss << "brown";
// 	};
// 	if (color = 11){
// 		ss << "blue";
// 	};
// 	if (color = 12){
// 		ss << "brown";
// 	};
// 	return ss.str();
// }

// //accessors
// Vehicle * Vehicle::getnextCar ( void ){
// 	//return pointer to carAhead
// 	return this->nextCar;
// };

// Vehicle * Vehicle::getprevCar ( void ) {
// 	//return pointer to carBehind
// 	return this->prevCar;
// };

// //mutators
// void Vehicle::setnextCar(Vehicle * ptr){
// 	//update pointer to new carAhead;
// 	this->nextCar = ptr;
// };

// void Vehicle::setprevCar(Vehicle * ptr){
// 	//update pointer to new carBehind;
// 	this->prevCar = ptr;
// };

//methods    
//**need help here: **
//**We need to be able to iterate through vehicles on highway (lane? spots?), and connect that vehicle to this one. **
//**does spots array contain vehicle objects?  **
// void Vehicle::scan( void ){
// 	if (this->carAhead = NULL) {
// 		//iterate through all spots in lane
// 		for(int i = 1, i < 33, i++){
// 			//sort, if Vehicle in spot[i] has a lower xPos than others in array, 
// 			//but still higher than this Vehicle(meaning its in front of it), store it as temp.
// 			int temp = NULL;
// 			if (this.lane.spots[i].xPos > this.xPos && this.lane.spots[i].xPos < temp.xPos) {
// 				temp = lane[this.lane].spots[i];
// 			};
// 		//set pointer to closest car in front of our car
// 		this->carAhead = temp;
// 		delete temp;
// 		}
// 	}
// };

// void Vehicle::scan( void ) {
// 	if CarAhead != NULL
// 		if this.xPos-CarAhead.xPos < this.xSpeed * .1
// 			this.slow();
// 		if this.desiredSpeed > CarAhead.xSpeed
// 			this.pass();
// 	else:
// 		for(int i = 1, i < 30, i++)
// 			if lane[this.lane].spots[this.lanepost + i] == true;
// 				spot.vehicleid = this.CarAhead;
// }

// void Vehicle::slow( void ) {
// 	while (this.xSpeed > CarAhead.xSpeed)
// 		this.xSpeed = this.xSpeed - 2
// };

// void Vehicle::pass() {

// }


	//drawFilledCircle(xPos,480,5);
    //drawFilledCircle(xPosTwo,450,5);
    //drawFilledCircle(xPos,420,5);