#include "Resistor.h"

Resistor::Resistor(string name_,double resistance_,int endpoints_[2], int resID_) {

	name = name_;
	resistance = resistance_;
	endpointNodeIDs[0] = endpoints_[0];
	endpointNodeIDs[1] = endpoints_[1];
	nextR = NULL;
	resID = resID_;

}

double Resistor::getResistance() { return resistance; }

int Resistor::getOtherEnd(int node) {
	
	if(endpointNodeIDs[0] == node) return endpointNodeIDs[1];
	else return endpointNodeIDs[0];

}
 
Resistor* Resistor::getNextR() { return nextR; }

void Resistor::getCoords(float& xleft, float& ybottom, float& xright, float& ytop) {
	
	xleft = xleftR;
	ybottom = ybottomR;
	xright = xrightR;
	ytop = ytopR;
}

void Resistor::setCoords(float xleft, float ybottom, float xright, float ytop) {
	
	xleftR = xleft;
	ybottomR = ybottom;
	xrightR = xright;
	ytopR = ytop;
}



Resistor::~Resistor() {}
