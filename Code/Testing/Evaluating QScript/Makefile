QTLIBS = -lQt5Core -lQt5Qml -lQt5Script
SRC = main.cpp cpp/*.cpp
OFILE = out

all:
	make -C cpp
	g++ -std=c++11 -fPIC \
		-Icpp -I/usr/include/qt5 $(QTLIBS) \
		$(SRC) -o $(OFILE)
