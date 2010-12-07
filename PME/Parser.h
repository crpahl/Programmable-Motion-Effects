/*
    Authors: Adel Lari, Clinton Pahl, Date: 07/2010

    A simple parser that reads a user supplied text file to
    create objects and position additional samples at the
    supplied times.
*/

#ifndef Parser_H
#define Parser_H

#include <string>
#include <vector>
using namespace std;

#define MAX_POINTS 10
#define MAX_PLANES 100

struct Color{
	float r, g, b, a;
};

// Contains all points in plane
struct MyPoint{
    float	x, y, z;
	Color	color;
};

// Contains all planes in object
struct MyPlane{
	MyPoint			points[MAX_POINTS];	// points in plane
	unsigned int	nPoints;			// number of points in plane
};

// Contains all samples generated from input file
struct Sample{
	MyPlane			planes[MAX_PLANES];	// planes in sample
	unsigned int	nPlanes;			// number of planes in sample
	float			time;				// stores the samples time
};

// Container for all of the objects samples
struct Object{
	string			name;
	bool			globalColor;		// yes if the global color should be used
	Color			color;				// stores the general object color
	vector<Sample>	samples;			// contains all of the objects samples
};

class Parser
{
public:
	//functions
	int parse(void);
	vector<Object> getObjects(void);
	int findSample(Sample &samp,vector<Sample> &samples, string name);
	void printObjects(void);
	Sample translateSample(Sample samp, MyPoint point);
	Parser(char *file);
	~Parser(void);
private:
	//functions
	Object createObject(ifstream &in);		// Creates an object
	void storePoints(MyPlane &plane, ifstream &in);					// Stores a series of points in a plane
	Color createColor(string r, string g, string b, string a);		// Creates a color struct from strings
	MyPoint createPoint(string x, string y, string z);				// Creates a point struct from strings
	vector<string> parseLine(string line);							// Stores a string of words into a vector
	void strip(string &s);											// Removes potentially bad characters

	//variable(s)
	vector<Object> objects;
	char *inputFile;
};

#endif
