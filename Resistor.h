#ifndef RESISTOR_H
#define RESISTOR_H

#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class ResistorList;
class NodeList;

class Resistor
{
private:
	double resistance; // resistance (in Ohms)
	string name; // C++ string holding the label
	int endpointNodeIDs[2]; // IDs of nodes it attaches to
	Resistor* nextR;
	
	int resID;
	float xleftR, ybottomR, xrightR, ytopR;

public:

	Resistor(string name_,double resistance_,int endpoints_[2], int resID_);
	// endpoints_ holds the node indices to which this resistor connects

	~Resistor();
	
	friend class ResistorList;
	friend class NodeList;
     
     double getResistance();
     int getOtherEnd(int node);
     Resistor* getNextR();
     
     void getCoords(float& xleft, float& ybottom, float& xright, float& ytop);
	void setCoords(float xleft, float ybottom, float xright, float ytop);

	// you *may* create either of the below to print your resistor
	//void print ();
	friend ostream& operator<<(ostream&,const Resistor&);
	
};

#endif	/* RESISTOR_H */

