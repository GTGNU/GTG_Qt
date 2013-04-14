QMAKE_CXXFLAGS += -std=c++11 -g -rdynamic
CONFIG += qt
LIBS += -lQt5Widgets

HEADERS +=	MainWindow.h MapDisplay.h TopPanel.h TileButton.h TileChooser.h \
		Tile.h

SOURCES +=	MainWindow.cpp MapDisplay.cpp TopPanel.cpp TileButton.cpp \
		TileChooser.cpp Tile.cpp

SOURCES += main.cpp
