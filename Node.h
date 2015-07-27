#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "Resistor.h"
#include "ResistorList.h"
using namespace std;

#define MAX_RESISTORS_PER_NODE 5

class NodeList;

class Node
{
private:

   int ID;//nodeID
   int numRes;
   double voltage;//voltage at node
   ResistorList RList;
   Node* nextN;
   bool set;
   bool voltChange;
   
float xleftN, ybottomN, xrightN, ytopN;


public:

	
	Node(int nodeID);
	~Node();
	friend class NodeList; //allows Node list to access node members

	// Updates resIDArray to show the resistor in position rIndex in
	// the resistor array is now connected to this node.
	// Returns true if successful
	void addResistor (string name,double resistance,int endpoints[2], int resID);//change
	bool deleteResistor(string name);
        
     Node* getNextN();
     float getxleft() { return xleftN; }
     
     void setVoltage(double v);
	void unsetVoltage();
	
	void getCoords(float& xleft, float& ybottom, float& xright, float& ytop);
	void setCoords(float xleft, float ybottom, float xright, float ytop);
	
	// prints the whole node
	// nodeIndex is the position of this node in the node array.
	friend ostream& operator<<(ostream& cout, Node& node);

};

#endif	/* NODE_H */

