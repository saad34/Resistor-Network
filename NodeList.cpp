#include "NodeList.h"

#define NODE_SPACE 100.00
#define NODE_WIDTH 40.00
#define RES_SPACE 40.00
#define RES_HEIGHT 40.00
#define LABEL_SPACE 10.00
#define RES_WIDTH 50.00

NodeList::NodeList() { NHead = NULL; numNodes = 0; numResistors = 0;}

NodeList::~NodeList() {

	Node* current = NHead;
	while(NHead != NULL) {
	
		NHead = NHead -> nextN;
		delete current; //delete that node
		current = NHead;
	}
}

Node* NodeList::getNHead() { return NHead; }

Node* NodeList::findNode(int ID) {

     Node* current = NHead;
	bool found = false;
	while(current != NULL && !found) {
		
                if(current -> ID == ID) found = true;
		else current = current -> nextN;
	}
        
	return current;
}

Node* NodeList::insertNode(int ID) {
	
	Node *current = NHead, *previous = NULL;
	Node* temp = new Node(ID);
	
	while(current != NULL && current -> ID < ID) { //move through node list until spot for new node is found
	
		previous = current; // keep track of previous node
		current = current -> nextN; //move to next node
	}
	
	temp -> nextN = current;
	if(previous == NULL) NHead = temp;
	else previous -> nextN = temp;
	
	numNodes++;
	
	return temp;
}

Resistor* NodeList::findResistor(string name) {

	Node* current = NHead;
	Resistor* resPtr = NULL;
	bool found = false;
	
	while(current != NULL && !found) {
	
                resPtr = current -> RList.findResistor(name);
		if(resPtr != NULL) found = true;
                
		if(!found) current = current -> nextN;	
	}
	
	return resPtr;
}

void NodeList::addResistor(string name, double resistance, int nodes[2]) {

	numResistors++;
	findNode(nodes[0]) -> addResistor(name, resistance, nodes, numResistors);
	findNode(nodes[1]) -> addResistor(name, resistance, nodes, numResistors);
	
}

bool NodeList::modifyR(string name, double resistance) {
	
	Node* current = NHead;
	bool found = false;
	double oldRes;
	
	while(current != NULL) {
	
                if(!found) found = current -> RList.modifyResistor(name, resistance, oldRes);
                else current -> RList.modifyResistor(name, resistance, oldRes);
                current = current -> nextN;	
	}
	
	if(found) {
	
	 	//print modified resistance
		cout.setf(ios::fixed);
		cout.setf(ios::showpoint);		
		cout << "Modified: resistor " << name << " from " << setprecision(2) << oldRes << " Ohms  to " << resistance << " Ohms" << setprecision(6) << endl;
		cout.unsetf(ios::fixed);
		cout.unsetf(ios::showpoint);
	 	return true;
	}
	else return false;
}

bool NodeList::deleteR(string name) {

	Node* current = NHead;
	bool found = false;
	
	int resID = findResistor(name) -> resID;
	
	while(current != NULL) {
	
     	if(!found) found = current -> deleteResistor(name);
          else current -> deleteResistor(name);
          current = current -> nextN;
	}
	
	if(found) {
		
		Node* current = NHead;
		while(current != NULL){
			
			Resistor* currentR = current -> RList.getRHead();
			while(currentR != NULL){
			
				if(currentR -> resID > resID) currentR -> resID = currentR -> resID - 1;
				
				currentR = currentR -> nextR;
			}
		
			current = current -> nextN;
		}
				
		numResistors --;
		return true;
	}
     else return false;
}

void NodeList::deleteAllR() {

	Node* current = NHead;
	while(current != NULL) {
            
		current -> RList.deleteList(); //delete resistor list at every node
		current -> numRes = 0;
          current = current -> nextN;
          numResistors = 0;
	}
}

bool NodeList::solve() {

	bool setFound = false;
	Node* current = NHead;
	while(current != NULL && !setFound) {
		if(current -> set) setFound = true;
		else current = current -> nextN;
	}
	
	if(!setFound) return false;
	
	while(current != NULL) {
		
		if(current -> set == false) current -> voltage = 0;
		
		current = current -> nextN;
	}
	

	current = NHead;
	double change = 0;
	double oldVolt, newChange;
	int numConverge = 0;
	
	while(numConverge != numNodes) {
	
		if(current -> set == true) numConverge++;
		
		else if(current -> set == false) {

			oldVolt = current -> voltage;
			double totalRes = current -> RList.getTotal();
			double totalCur = 0;
			
			for(int i = 1; i <= current -> numRes; i++) {
				
				Resistor* res = current -> RList.findResistor(i); 
				int otherNodeID = res -> getOtherEnd(current -> ID); 
				
				Node* otherNode = NHead;
				while(otherNode -> ID != otherNodeID) otherNode = otherNode -> nextN;
						
				totalCur += (otherNode -> voltage)/(res -> getResistance());
				
			}
			
			
			current -> voltage = totalRes * totalCur;
			
			newChange	= oldVolt - current -> voltage;
			if(newChange >= 0) change = newChange; 
			else if(newChange < 0) change = -newChange;

			if(change <= MAX_ITERATION_CHANGE) numConverge++;
			else numConverge = 0;
		
		}
		

		if(current -> nextN == NULL) current = NHead;
		else current = current -> nextN;

	}
	
	current = NHead;
	
	cout << "Solve:" << endl;
	while(current != NULL) {
		
		if(current -> numRes != 0){
			
			cout << "  Node " << current -> ID << ": ";
			cout.setf(ios::fixed);
			cout.setf(ios::showpoint);
			cout << setprecision(2) << current -> voltage << setprecision(6) << " V" << endl;
			cout.unsetf(ios::fixed);
			cout.unsetf(ios::showpoint);
		
		}
		
		current = current -> nextN;
	}
	
	return true;

}

void NodeList::setDrawCoords(float& xleft, float& ybottom, float& xright, float& ytop) { 

	xleft = 0;
	ybottom = 0;
	xright = xleft + (NODE_SPACE + NODE_WIDTH)* numNodes + NODE_SPACE;
	ytop = ybottom + (RES_SPACE + RES_HEIGHT)* numResistors + RES_SPACE + 2* LABEL_SPACE;
	
	
	Node* current = NHead;
	for(int i = 0; i < numNodes; i++) {
		
		current -> setCoords((NODE_SPACE + NODE_WIDTH)* i + NODE_SPACE	,	RES_SPACE/2 + 2*LABEL_SPACE	,	(NODE_SPACE + NODE_WIDTH)* i + NODE_SPACE + NODE_WIDTH	    ,	ytop - RES_SPACE/2);
			
		current = current -> nextN;
	}
	
	int node1, node2;
	
	current = NHead;
	while(current!=NULL){
	Resistor* currentR = current -> RList.getRHead();
		for(int i = 0; i < current -> numRes; i++) {

			if(currentR -> endpointNodeIDs[0] < currentR -> endpointNodeIDs[1]) { node1 = currentR -> endpointNodeIDs[0]; node2 = currentR -> endpointNodeIDs[1]; }
			else { node1 = currentR -> endpointNodeIDs[1]; node2 = currentR -> endpointNodeIDs[0]; }
			Node* node1p = findNode(node1);
			Node* node2p = findNode(node2);
		
			currentR -> setCoords(node1p -> xleftN + NODE_WIDTH/2	,	(RES_SPACE + RES_HEIGHT)* (currentR ->resID - 1) + RES_SPACE + 2*LABEL_SPACE	,	node2p -> xleftN + NODE_WIDTH/2	,	(RES_SPACE + RES_HEIGHT)* (currentR->resID - 1) + RES_SPACE + RES_HEIGHT + 2*LABEL_SPACE);
		
			currentR = currentR -> nextR;
		}
	current = current -> nextN;
	}
	return;
}

void NodeList::draw(easygl& window) {
	
	// Clear the area in the red box in Figure 1 (the graphics area).
	// Need to do this to have a blank area before redrawing.
	window.gl_clearscreen ();
	// Iterate over Nodes, calling appropriate draw functions (probably in
	// class Node). See easygl.h for a list of drawing functions, like
	// window.gl_drawline (x1, y1, x2, y2).
	// Iterate over resistors, calling appropriate draw functions (probably in
	// class Resistor).
	// These functions will use new member variables that store drawing coordinates
	// for each Node and resistor.
	
	Node* current = NHead;
	stringstream converter;

	while(current != NULL) {
	
		//draw nodes	
		window.gl_setcolor(DARKGREY);
		window.gl_fillrect(current -> xleftN, current -> ybottomN, current -> xrightN, current -> ytopN);
		
		//border nodes
		window.gl_setlinestyle(SOLID);
		window.gl_setlinewidth(3);
		window.gl_setcolor(BLACK);
		window.gl_drawrect(current -> xleftN, current -> ybottomN, current -> xrightN, current -> ytopN);
		
		//label nodes
		window.gl_setcolor(BLACK);
		window.gl_setfontsize(13);
		
		string nodelabel;
		converter << "Node " << current -> ID;
		nodelabel = converter.str();
		converter.str("");
		window.gl_drawtext(NODE_WIDTH/2 + current -> xleftN, 2*LABEL_SPACE , nodelabel, NODE_WIDTH);
		
		if(current -> set == false) window.gl_setcolor(RED);
		else {
			window.gl_setcolor(BLACK);
		}
		window.gl_setfontsize(15);
		

		converter << setprecision(2) << current -> voltage << " V";
		string voltStr;
		voltStr = converter.str();
		converter.str("");
		window.gl_drawtext(NODE_WIDTH/2 + current -> xleftN, LABEL_SPACE , voltStr, NODE_WIDTH);
				
		window.gl_setcolor(BLACK);//reset font to black if changed to red
		
		current = current -> nextN;
	
	}
	
	
	current = NHead;
	stringstream convert;
	while(current != NULL) {

		Resistor* currentR = current -> RList.getRHead();
		
		while(currentR != NULL){
			
			if(currentR -> getOtherEnd(current -> ID) > current -> ID) {
			
			//draw node circle
			window.gl_fillarc(currentR -> xleftR, currentR -> ybottomR + RES_HEIGHT/2, 3*NODE_WIDTH/8, 0, 360);
			window.gl_fillarc(currentR -> xrightR, currentR -> ybottomR + RES_HEIGHT/2, 3*NODE_WIDTH/8, 0, 360);
			
			//draw resistors
			window.gl_setcolor(RED);
			
			double reslength = currentR->xrightR - currentR->xleftR;
			double straightlength = (reslength - RES_WIDTH)/2;
			double zigzagstart = currentR->xleftR + straightlength;
			
			//draw first straight line
			window.gl_drawline(currentR -> xleftR, currentR -> ybottomR + RES_HEIGHT/2, currentR -> xleftR + straightlength, currentR->ybottomR + RES_HEIGHT/2);
			
			//draw zigzag			
			window.gl_drawline(zigzagstart, currentR-> ybottomR+RES_HEIGHT/2, zigzagstart + RES_WIDTH/7, currentR-> ybottomR);//
			window.gl_drawline(zigzagstart + RES_WIDTH/7, currentR-> ybottomR, zigzagstart + 2*RES_WIDTH/7, currentR-> ytopR);//
			window.gl_drawline(zigzagstart + 2*RES_WIDTH/7, currentR-> ytopR, zigzagstart + 3*RES_WIDTH/7, currentR-> ybottomR);//
			window.gl_drawline(zigzagstart + 3*RES_WIDTH/7, currentR-> ybottomR, zigzagstart + 4*RES_WIDTH/7, currentR-> ytopR);//
			window.gl_drawline(zigzagstart + 4*RES_WIDTH/7, currentR-> ytopR, zigzagstart + 5*RES_WIDTH/7, currentR-> ybottomR);//
			window.gl_drawline(zigzagstart + 5*RES_WIDTH/7, currentR-> ybottomR, zigzagstart + 6*RES_WIDTH/7, currentR-> ytopR);//
			window.gl_drawline(zigzagstart + 6*RES_WIDTH/7, currentR-> ytopR, zigzagstart + RES_WIDTH, currentR-> ybottomR + RES_HEIGHT/2);
			
			//draw second line
			window.gl_drawline(currentR -> xrightR - straightlength, currentR -> ybottomR + RES_HEIGHT/2, currentR -> xrightR, currentR->ybottomR + RES_HEIGHT/2);
			
			//label resistors
			window.gl_setcolor(BLACK);
			window.gl_setfontsize(15);
			
			string reslabel;
			convert.setf(ios::fixed);
			convert << currentR -> name << " (" << setprecision(2) << currentR -> resistance << " ohms)";
			convert.setf(ios::fixed);
			reslabel = convert.str();
			convert.str("");
			
			window.gl_drawtext(zigzagstart + RES_WIDTH/2, currentR -> ybottomR - 1*RES_SPACE/3, reslabel);	
			
			}
			
			currentR = currentR -> nextR;	
		}
			
		current = current -> nextN;
	}
	
	return;
}





