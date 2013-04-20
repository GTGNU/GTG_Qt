QTLIBS = -lQt5Core -lQt5Gui -lQt5Quick -lQt5Qml
SRC = cpp/*.cpp main.cpp
OFILE = out

all:
	make moc -C cpp
	g++ -std=c++11 -fPIC \
		-Icpp -I/usr/include/qt5 $(QTLIBS) \
		$(SRC) -o $(OFILE)

clean:
	make clean -C cpp
	rm $(OFILE)
