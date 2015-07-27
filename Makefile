FLAGS = -g -Wall -DX11 

HDR = graphics.h easygl.h easygl_constants.h 

BACKUP_FILENAME=`date "+backup-%Y%m%d-%H%M.zip"`


rnet: Resistor.o ResistorList.o Node.o NodeList.o Rparser.o Main.o easygl.o graphics.o
	g++ $(FLAGS) Resistor.o ResistorList.o Node.o NodeList.o Rparser.o Main.o easygl.o graphics.o -lX11 -o rnet
	
Resistor.o: Resistor.cpp Resistor.h ResistorList.h
	g++ -c Resistor.cpp

ResistorList.o: ResistorList.cpp ResistorList.h
	g++ -c ResistorList.cpp

Node.o: Node.cpp Node.h Resistor.h ResistorList.h NodeList.h
	g++ -c Node.cpp
	
NodeList.o: NodeList.cpp NodeList.h easygl.h
	g++ -c $(FLAGS) NodeList.cpp
	
Rparser.o: Rparser.cpp Rparser.h NodeList.h easygl.h
	g++ -c $(FLAGS) Rparser.cpp

Main.o: Main.cpp Rparser.h
	g++ -c Main.cpp
	
easygl.o: easygl.cpp $(HDR)
	g++ -c $(FLAGS) easygl.cpp
	
graphics.o: graphics.cpp $(HDR)
	g++ -c $(FLAGS) graphics.cpp
	
backup:
	echo Backing up your files into ${BACKUP_FILENAME}
	zip ${BACKUP_FILENAME} *.cpp *.h makefile *.sln *.vcxproj 
