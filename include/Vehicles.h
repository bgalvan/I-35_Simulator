#ifndef VEHICLES_H
#define VEHICLES_H

class Vehicle {
    public:
        int size;       // how big should this vehicle be
        int xPos;       // screen position in pixels
        int yPos;       
        int xSpeed;     // current speed
        int ySpeed;
        int desiredSpeed;

        // Vehicle * nextCar;
        // Vehicle * prevCar;

        int highwayid;
        int lane;
        // int lanepost = 0;
        int preferred_lane;
        bool active;
        int color;
        int carAheadIndex;
        int carBehindIndex;
        int tolerance;

        //constructors
        Vehicle();
        void setPosition( int x, int y );
        void setSpeed( int xv, int yv );

        // //accessors
        // Vehicle * getnextCar ( void );
        // Vehicle * getprevCar ( void );


        // //mutators
        // void setnextCar(Vehicle * ptr);
        // void setprevCar(Vehicle * ptr);

        void move( void );
        void scan( void );   //called every moment
        void slow( void );
        void pass( void );
        std::string getColor( void );
};
#endif
