#ifndef RPARSER_H
#define RPARSER_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cctype>
#include "NodeList.h"
#include "easygl.h"
using namespace std;



//choose which command to execute
void readInput();

// run following commands 
void setV(stringstream&, NodeList&);
void unsetV(stringstream&, NodeList&);
void solve(stringstream&, NodeList&);
void insertR(stringstream&, NodeList&);
void modifyR(stringstream&, NodeList&);
void printR(stringstream&, NodeList&);
void printNode(stringstream&, NodeList&);
void deleteR(stringstream&, NodeList&);
void draw(NodeList& NList);

//check errors
bool anyArgs(stringstream&);
bool validResistance(double, stringstream&);
bool validNode(int, stringstream&);
bool endOfArgs(stringstream&);

#endif    /* RPARSER_H */
