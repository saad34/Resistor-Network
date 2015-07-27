#ifndef NODE_LIST
#define NODE_LIST

#define MAX_ITERATION_CHANGE 0.0001

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "Node.h"
#include "easygl.h"
using namespace std;

class NodeList
{
private: 

	Node* NHead;//points to node list
	int numNodes;
	int numResistors;
	
public:

	NodeList();
	~NodeList();
	
	Node* getNHead();
	Node* findNode(int ID);
	Node* insertNode(int ID);
	Resistor* findResistor(string name);
	void addResistor(string name, double resistance, int nodes[2]);
	bool modifyR(string name, double resistance);
	bool deleteR(string name);
	void deleteAllR();
	bool solve();
	
	void setDrawCoords(float& xleft, float& ybottom, float& xright, float& ytop);
	void draw(easygl &window);
	
};	

#endif /*NODE_LIST*/
