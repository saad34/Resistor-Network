#include "Node.h"


Node::Node(int nodeID) { 

	numRes = 0; 
	ID = nodeID;
	nextN = NULL;
	set = false;
	voltage = 0;
	voltChange = 1000000000;
}

Node::~Node() {}

void Node::addResistor (string name,double resistance,int endpoints[2], int resID) {

    RList.addResistor(name, resistance, endpoints, resID);
	numRes++;
}

void Node::setVoltage(double v) {

	voltage = v;
	set = true;
	return;
	
}

void Node::unsetVoltage() {

	voltage = 0;
	set = false;
	return;
}


bool Node::deleteResistor(string name) {

	if(RList.deleteResistor(name)){
            numRes--;
            return true;
     }
	return false;
}

Node* Node::getNextN() { return nextN; }

void Node::getCoords(float& xleft, float& ybottom, float& xright, float& ytop) {
	
	xleft = xleftN;
	ybottom = ybottomN;
	xright = xrightN;
	ytop = ytopN;
}

void Node::setCoords(float xleft, float ybottom, float xright, float ytop) {
	
	xleftN = xleft;
	ybottomN = ybottom;
	xrightN = xright;
	ytopN = ytop;
}
