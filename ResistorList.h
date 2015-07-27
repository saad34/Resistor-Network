#ifndef RESISTOR_LIST
#define RESISTOR_LIST

#include <string>
#include "Resistor.h"
using namespace std;

class Node;

class ResistorList
{
private:

	Resistor* RHead;//point to resistor list
	
public:

	ResistorList();
	~ResistorList();
	friend class Node;
	
	Resistor* getRHead();
	void addResistor(string name,double resistance,int endpoints[2], int resID);
	bool deleteResistor(string name);
     bool modifyResistor(string name, double resistance, double& oldRes);
	Resistor* findResistor(string name);
	void deleteList();
	double getTotal();
	Resistor* findResistor(int resNum);
};

#endif /*RESISTOR_LIST*/
