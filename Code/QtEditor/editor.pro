QMAKE_CXXFLAGS += -std=c++11
CONFIG += qt
LIBS += -lQt5Widgets
HEADERS += MainWindow.h MapDisplay.h TopPanel.h TileButton.h TileChooser.h

SOURCES +=	MainWindow.cpp MapDisplay.cpp TopPanel.cpp TileButton.cpp \
		TileChooser.cpp

SOURCES += main.cpp
