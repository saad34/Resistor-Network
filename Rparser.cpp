#include "Rparser.h"

/************** Global variables ************************************/
// Create a window with name = “Resistor display” and a white background.
// Making it global so we can draw to it from anywhere.
easygl window("Resistor display", WHITE);


// Make a global scope pointer to the nodelist so your drawing routine can access it.
// Make sure you set this pointer to a valid value early in your program!
NodeList* NListPtr;


void readInput() {

	NodeList NList;
	
	cout << "> ";
	cout.flush();

	string line, command;

     getline (cin, line); // Get a line from standard input

	while (!cin.eof()) {

		// Put the line in a stringstream for parsing
		// Making a new stringstream for each line so flags etc. are in a known state
		stringstream lineStream (line);
		lineStream >> command;

          //call function depending on command
		if(command == "insertR") insertR(lineStream, NList);
		else if (command == "setV") setV(lineStream, NList);
		else if (command == "unsetV") unsetV(lineStream, NList);
		else if (command == "solve") solve(lineStream, NList);
		else if (command == "modifyR") modifyR(lineStream, NList);
		else if (command == "printR") printR(lineStream, NList);
		else if (command == "printNode") printNode(lineStream, NList);
		else if (command == "deleteR") deleteR(lineStream, NList);
		else if (command == "draw") draw(NList);
		else cout << "Error: invalid command" << endl;

		command = " ";
		cout << "> ";
		cout.flush();
		getline (cin, line);

	} // End input loop until EOF.

	return;

}

void setV(stringstream& lineStream, NodeList& NList) {

	int nodeID;
	double voltage;
	
	if(!anyArgs(lineStream)) return;
	
	lineStream >> nodeID;

		if(!validNode(nodeID, lineStream)) return;
		
	lineStream >> voltage;
	
		if(lineStream.fail()) {
			cout << "Error: " << endl;
			return;
		}
	
	if(!endOfArgs(lineStream)) return;
	
	if(NList.findNode(nodeID) == NULL) NList.insertNode(nodeID);
		
	NList.findNode(nodeID) -> setVoltage(voltage);
		
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout << "Set: node " << nodeID << " to " << setprecision(2) << voltage << setprecision(6) << " Volts" << endl;
	cout.unsetf(ios::fixed);
	cout.unsetf(ios::showpoint);
	
}

void unsetV(stringstream& lineStream, NodeList& NList) {

	int nodeID;
	
	if(!anyArgs(lineStream)) return;
	
	lineStream >> nodeID;

		if(!validNode(nodeID, lineStream)) return;
	
	if(!endOfArgs(lineStream)) return;
	
	if(NList.findNode(nodeID) == NULL) cout << "Error: node " << nodeID << " doesn't exist" << endl;
	else {
	
		NList.findNode(nodeID) -> unsetVoltage();
		
		cout << "Unset: the solver will determine the voltage of node " << nodeID << endl;
	} 
	
}

void solve(stringstream& lineStream, NodeList& NList) {

	if(NList.solve() == false) cout << "Error: no nodes have their voltage set" << endl;

}

void insertR(stringstream& lineStream, NodeList& NList) {

	string name;
	double resistance;
	int nodeID1, nodeID2;

	//Read in each argument one at a time and check for errors
	lineStream >> name;

		if(!anyArgs(lineStream)) return;

		if(name == "all") {
			cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
			return;
		}

	lineStream >> resistance;

		if(!validResistance(resistance, lineStream)) return;

	lineStream >> nodeID1;

		if(!validNode(nodeID1, lineStream)) return;

	lineStream >> nodeID2;

		if(!validNode(nodeID2, lineStream)) return;


	if(nodeID1 == nodeID2) {
		cout << "Error: both terminals of resistor connect to node " << nodeID1 << endl;
		return;
	}

	//check if there are more arguments
	if(!endOfArgs(lineStream)) return;
	
	//VALID ARGUMENTS
	
	//check if nodes exist, if not create
	if(NList.findNode(nodeID1) == NULL) NList.insertNode(nodeID1);
	if(NList.findNode(nodeID2) == NULL) NList.insertNode(nodeID2);
	
	//check if resistor name already exists
	if(NList.findResistor(name) != NULL) {
	
		cout << "Error: resistor " << name << " already exists" << endl;
		return;
	}
        
	//if resistor doesnt exist
	int nodes[2] = {nodeID1, nodeID2};
	NList.addResistor(name, resistance, nodes);
        
    	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout << "Inserted: resistor " << name << " " << setprecision(2) << resistance << " Ohms " << setprecision(6);
	cout.unsetf(ios::fixed);
	cout.unsetf(ios::showpoint);
	cout << nodeID1 << " -> " << nodeID2 << endl;

	return;
}

void modifyR(stringstream& lineStream, NodeList& NList) {

	string name;
	double resistance;

	lineStream >> name;

		if(!anyArgs(lineStream)) return;

		if(name == "all") {
			cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
			return;
		}

	lineStream >> resistance;

		if(!validResistance(resistance, lineStream)) return;

	//check for extra arguments
	if(!endOfArgs(lineStream)) return;
	
	//VALID ARGS
	
	if(NList.modifyR(name, resistance) == false) cout << "Error: resistor " << name << " not found" << endl;  	

	return;
}

void printR(stringstream& lineStream, NodeList& NList) {

	string name;

	lineStream >> name;

		if(!anyArgs(lineStream)) return;

	if(!endOfArgs(lineStream)) return;
	
	//VALID ARGS

	if(name == "all") { //if "all" go through resistor array and print all resistors

		cout << "Print:" << endl;

    	}

    	else {

    		Resistor* res = NList.findResistor(name);
    		
    		if(res == NULL) {
    		
    			cout << "Error: resistor " << name << " not found" << endl;
    			return;
    		}
		else {
			cout << "Print:" << endl;
			cout << *res << endl;
		}
    	}

	return;

}

void printNode(stringstream& lineStream, NodeList& NList) {

	string Nodes, junk;
	int nodeID;

	lineStream >> nodeID;

		if(lineStream.fail()) {

			lineStream.clear();
			lineStream >> Nodes;
			if(lineStream.fail()) {
				cout << "Error: too few arguments" << endl;
				return;
			}

			if(Nodes != "all") {
				cout << "Error: invalid argument" << endl;
				return;
			}
                        
                        if(!endOfArgs(lineStream)) return;

			//if argument is "all", print all nodes
			cout << "Print: " << endl;
                        Node* current = NList.getNHead();
                        while(current != NULL) {
                            cout << *current;
                            current = current -> getNextN();
                        }

			return;

		}

	if(!isspace(lineStream.peek()) && lineStream.peek() != -1) {

		cout << "Error: invalid argument" << endl;
		return;

	}

	if(!endOfArgs(lineStream)) return;

	//for specific node print no. of connection then all resistors at node
        if(NList.findNode(nodeID) != NULL) {
                cout << "Print: " << endl;
                cout << *NList.findNode(nodeID);
        }
	

	return;

}

void deleteR(stringstream& lineStream, NodeList& NList) {

	string name, junk;

	lineStream >> name;

		if(!anyArgs(lineStream)) return;

	if(!endOfArgs(lineStream)) return;

	if(name == "all") {

            NList.deleteAllR();
            cout << "Deleted: all resistors" << endl;
        }
        else {

            if(NList.deleteR(name) == false)
                cout << "Error: resistor " << name << " not found" << endl;
            else cout << "Deleted: resistor " << name << endl;
          
        }

     return;

}

ostream& operator<<(ostream& cout, const Resistor& res) { //operator overload to print Resistor objects using "<<"

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout << setw(20) << left << res.name << " " << setw(8) << setprecision(2) << right << res.resistance << " Ohms " << setprecision(6);
	cout.unsetf(ios::fixed);
	cout.unsetf(ios::showpoint);
	cout << res.endpointNodeIDs[0] << " -> " << res.endpointNodeIDs[1] << left;
	
	return cout;
}

ostream& operator<<(ostream& cout, Node& node) { //operator overload to print Node objects using "<<"

	if(node.numRes == 0) return cout;
        cout << "Connections at node " << node.ID << ": " << node.numRes << " resistor(s)" << endl;
        Resistor *current = node.RList.getRHead();
        while(current != NULL) {
            cout << "  " << *current << endl;
            current = current -> getNextR();
        }
	return cout;
}


void draw(NodeList& NList) {

	float xleft, ybottom, xright, ytop;
	
	NList.setDrawCoords(xleft, ybottom, xright, ytop);

	// Tell the graphics package what coordinate system we will draw in.
	window.set_world_coordinates (xleft, ybottom, xright, ytop);
	
	NListPtr = &NList; //setup global pointer
	
	NList.draw(window); // Draw the network
	cout << "Draw: control passed to graphics window";
	cout.flush();
	// This function will not return until the “Proceed” button is pushed.
	window.gl_event_loop ();
	cout << "Draw: complete; responding to commands again" << endl;
	
	return;
}

/** Redrawing the screen when the graphics package calls you (drawscreen callback) **/
void easygl::drawscreen () {

	NListPtr->draw (window); // Call your routine that does all the work of drawing.
	// Note how we needed the global pointer to nodeList.
}




////////////////**********ERROR CHECKING********//////////////////////

bool anyArgs(stringstream& lineStream) {

	if(lineStream.fail()) {
			cout << "Error: too few arguments" << endl;
			return false;
	}

	return true;

}

bool validResistance(double resistance, stringstream& lineStream) {

		string junk;

		if(lineStream.fail()) {

			lineStream.clear();
			lineStream >> junk;
			if(!lineStream.fail()) {
				cout << "Error: invalid argument" << endl;
				return false;
			}
			else {

				cout << "Error: too few arguments" << endl;
				return false;

			}
		}

		if(!isspace(lineStream.peek()) && lineStream.peek() != -1) { //check for letters after number

			cout << "Error: invalid argument" << endl;
			return false;

		}

		if(resistance < 0.0){
			cout << "Error: negative resistance" << endl;
			return false;
		}

		return true;

}

bool validNode(int node, stringstream& lineStream) {

	string junk;

	if(lineStream.fail()) {

			lineStream.clear();
			lineStream >> junk;
			if(!lineStream.fail()) {
				cout << "Error: invalid argument" << endl;//NodeID isn't a number
				return false;
			}
			else {

				cout << "Error: too few arguments" << endl;//nothing entered for nodeID
				return false;

			}
		}

		if(!isspace(lineStream.peek()) && lineStream.peek() != -1) {

			cout << "Error: invalid argument" << endl;//trailing characters
			return false;

		}

		return true;
}


bool endOfArgs(stringstream& lineStream) {

	string junk;

	lineStream >> junk;
	if(!lineStream.fail()) {
		cout << "Error: too many arguments" << endl;
		return false;
	}

	return true;
}
