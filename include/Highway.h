#ifndef HIGHWAY_H
#define HIGHWAY_H
#include <string>

void StartHighway(int argc, char **argv);		// default constructor

class Highway {
    public:
		std::string name;	// name of this highway
        int lanes;		// number of lanes 
        int width;		// width of each lane in pixels
        int yaxis;		// Where does the next set of lines start on the y axis
		int Spawns[10];
		void SetSpawns();
		void draw();		// display the highway
		Highway();
};

#endif
