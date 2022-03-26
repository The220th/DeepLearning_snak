QT += core gui

QT += widgets

CONFIG += c++11
TARGET = aisnak
TEMPLATE = app

#QMAKE_CXXFLAGS = -ggdb
#QMAKE_CXXFLAGS_RELEASE -= -O1
#QMAKE_CXXFLAGS_RELEASE -= -O2

SOURCES += ./main.cpp \
./gui/MainWindow.cpp ./gui/DrawField.cpp \
./tools/sup.cpp ./tools/matrix.cpp \
./game/GameHandler.cpp ./game/Snake.cpp \
./deeplearning/SnakeBrain.cpp

HEADERS  += ./include/MainWindow.h ./include/DrawField.h \
./include/sup.h ./include/matrix.h \
./include/GameHandler.h ./include/Snake.h \
./include/SnakeBrain.h
