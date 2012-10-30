#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "melinkjlStarbucks.h"
#include <iostream>
#include <fstream>

using namespace ci;
using namespace ci::app;
using namespace std;

class MelinkJLHW04App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	int numberOfEntries;
	Entry* readIntoArray();
};

void MelinkJLHW04App::setup()
{
	numberOfEntries = 0;
	Entry* entryArray = readIntoArray();
	melinkjlStarbucks* tree = new melinkjlStarbucks;
	(*tree).build(entryArray, numberOfEntries);
	delete [] entryArray;
	Entry* testPoint = (*tree).getNearest(.743269, .610535);
}

Entry* MelinkJLHW04App::readIntoArray()
{
	string name;
	double xPos, yPos;
	ifstream input("../../../resources/Starbucks_2006.csv");
	if (input.is_open())
	{
		// Determines the size of the array to be instantiated.
		while (input.good())
		{
			getline(input, name, '\r');
			input >> xPos;
			input.get();
			input >> yPos;
			input.get();
			numberOfEntries++;
		}
		input.clear();
		input.seekg(0);

		Entry* storeEntries = new Entry[numberOfEntries];
		numberOfEntries = 0;

		// Fills the array with the data.
		while (input.good())
		{
			getline(input, name, '\r');
			input >> xPos;
			input.get();
			input >> yPos;
			input.get();
			(*(storeEntries + numberOfEntries)).identifier = name;
			(*(storeEntries + numberOfEntries)).x = xPos;
			(*(storeEntries + numberOfEntries)).y = yPos;
			numberOfEntries++;
		}
		input.close();
		return storeEntries;
	}
	else
	{
		return NULL;
	}
}

void MelinkJLHW04App::mouseDown( MouseEvent event )
{
}

void MelinkJLHW04App::update()
{
}

void MelinkJLHW04App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( MelinkJLHW04App, RendererGl )
