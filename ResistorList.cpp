#include "ResistorList.h"

#define NODE_SPACE 100.00
#define NODE_WIDTH 40.00
#define RES_SPACE 50.00
#define RES_HEIGHT 40.00
#define LABEL_SPACE 5.00

ResistorList::ResistorList() { RHead = NULL; }

ResistorList::~ResistorList() {

	Resistor* current;
	while(RHead != NULL) { //delete all resistors in resistor list
	
		current = RHead;
          RHead = RHead -> nextR;
		delete current; //delete resistor
	}
}

Resistor* ResistorList::getRHead() { return RHead; }

void ResistorList::addResistor(string name, double resistance, int endpoints[2], int resID) {

	Resistor* temp = new Resistor(name, resistance, endpoints, resID);
        
        if(RHead == NULL) RHead = temp;
        else {
            
            Resistor *current = RHead;
            
            while(current -> nextR != NULL) { // add resistor to end of resistor list
	
                    current = current -> nextR;
            }
            
            current -> nextR = temp; //point current last resistor to new last resistor
	}
        return;
}

bool ResistorList::modifyResistor(string name, double resistance, double& oldRes) {
    
        Resistor* resPtr = findResistor(name);
        if(resPtr != NULL) {
            oldRes = resPtr -> resistance;
            resPtr -> resistance = resistance;
            return true;
        }
        else return false;  
}


bool ResistorList::deleteResistor(string name) {

	Resistor *current = RHead, *previous = NULL;
	bool found = false;
	
	while(current != NULL && !found) {
	
		if(current -> name == name) found = true;
		else {
			previous = current;
			current = current -> nextR;
		}
	}
	
	if(found) {
		 if(previous == NULL) RHead = current -> nextR;
           else previous -> nextR = current -> nextR;
           delete current;
     }
	
	return found;
}

Resistor* ResistorList::findResistor(string name) {

	Resistor* current = RHead;
	bool found = false;
	
	while(current != NULL && !found) {
	
                if(current -> name == name) found = true;
		else current = current -> nextR;
	}
	
	return current;
}

void ResistorList::deleteList() {

	Resistor* current;
	while(RHead != NULL) { //delete all resistors in resistor list
	
		current = RHead;
		
          RHead = RHead -> nextR;
		delete current; //delete resistor
	}
}

double ResistorList::getTotal() {

	double denom = 0;
	
	Resistor* current = RHead;
	
	while(current != NULL) {

		denom += 1/(current -> resistance);
		current = current -> nextR;
	
	}
	
	return 1/denom;

}

Resistor* ResistorList::findResistor(int resNum) {

	Resistor* current = RHead;
	
	for(int i = 1; i < resNum; i++) current = current -> nextR;
	
	return current;
}







