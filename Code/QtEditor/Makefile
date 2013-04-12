CXX = c++
CXXFLAGS = -I/usr/include/qt/ -std=c++11 -fPIC -Wall -pedantic
LFLAGS =-lstdc++ -lgcc_s -lQt5Core -lQt5Widgets -lQt5Gui

all: main.o MainWindow.o TopPanel.o MapDisplay.o
	$(CXX) $(LFLAGS) $? -o editor

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $*.cpp -c -o $*.o

MainWindow.o: MainWindow.cpp
	$(CXX) $(CXXFLAGS) $*.cpp -c -o $*.o

TopPanel.o: TopPanel.cpp
	$(CXX) $(CXXFLAGS) $*.cpp -c -o $*.o

MapDisplay.o: MapDisplay.cpp
	$(CXX) $(CXXFLAGS) $*.cpp -c -o $*.o

clean:
	rm -f main.o MainWindow.o TopPanel.o MapDisplay.o

.PHONY: clean
