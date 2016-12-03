QT += core
QT -= gui

CONFIG += c++11

TARGET = GUI
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    gui.cpp

HEADERS += \
    gui.h
