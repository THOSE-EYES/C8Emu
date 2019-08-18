TITLE = CHIP-8

CXX = g++ -std=c++11
CPPFLAGS = -Wall 

LDFLAGS = -lboost_serialization

BUILDING_FOLDER = ../build
OUTPUT_FOLDER = ../$(BUILDING_FOLDER)/out

VPATH = include src tests build

.PHONY : all clean install $(OUTPUT_FOLDER)

all : $(OUTPUT_FOLDER) $(OUTPUT_FOLDER)/$(TITLE)

$(OUTPUT_FOLDER) :
	mkdir -p $(OUTPUT_FOLDER)

$(OUTPUT_FOLDER)/$(TITLE) : $(wildcard $(BUILDING_FOLDER)/*.o)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $^ -o $@

$(BUILDING_FOLDER)/%.o : %.cpp %.h
	$(CXX) $(CPPFLAGS) -c $^ -o $@

clean : 
	rm $(BUILDING_FOLDER)/*.o
	rm $(OUTPUT_FOLDER)/$(TITLE)

install :