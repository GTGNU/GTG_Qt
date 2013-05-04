QMAKE_CXXFLAGS += -std=c++11 -g -rdynamic
CONFIG += qt
LIBS += -lQt5Widgets

TEMPLATE = app
TARGET = editor

HEADERS +=	MainWindow.h MapDisplay.h TopPanel.h TileButton.h \
		TileChooser.h Tile.h config.h

SOURCES +=	MainWindow.cpp MapDisplay.cpp TopPanel.cpp TileButton.cpp \
		TileChooser.cpp Tile.cpp main.cpp

target.path = $$DESTDIR/.

assets.path = $$DESTDIR/assets
assets.files = $$PWD/assets/*

INSTALLS += target assets
