CC = gcc
CFLAGS = -Wall

CXX = g++ -std=c++11
CXXFLAGS = -Wall -lboost_serialization

BUILDING_FOLDER = ../build
OUT_FOLDER = ../$(BUILDING_FOLDER)/out

VPATH = include src tests

#vpath %.h ../include
#vpath %.c ../src
#vpath %.o ../build



all : *


$(BUILDING_FOLDER)/settings.o : settings.cpp settings.h
	$(CXX) $(CXXFLAGS) $^

clean : 