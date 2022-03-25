QT += core gui

QT += widgets

CONFIG += c++11
TARGET = aisnak
TEMPLATE = app

#QMAKE_CXXFLAGS = -ggdb

SOURCES += ./main.cpp \
./gui/MainWindow.cpp ./gui/DrawField.cpp \
./tools/sup.cpp ./tools/matrix.cpp \
./game/GameHandler.cpp ./game/Snake.cpp

HEADERS  += ./include/MainWindow.h ./include/DrawField.h \
./include/sup.h ./include/matrix.h \
./include/GameHandler.h ./include/Snake.h
