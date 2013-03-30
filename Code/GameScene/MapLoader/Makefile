QTLIBS = -lQt5Core -lQt5Gui -lQt5Quick -lQt5Qml
INCLUDES = -I/usr/include/qt5 -I/usr/include/qt5/QtCore -I/usr/include/qt5/QtGui

CXX = clang++
MOC = moc

SRC = *.cpp
HEADERS = $(wildcard *.h)

OFILE = tileloader

all: moc build

moc:
	$(foreach header, $(HEADERS), $(MOC) $(header) -o $(header:%.h=moc_%.cpp);)

build:
	$(CXX) -g -std=c++11 -fPIC \
		$(INCLUDES) $(QTLIBS) \
		$(SRC) -o $(OFILE)

clean:
	rm moc_*.cpp
