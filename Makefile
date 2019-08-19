TITLE = CHIP-8_$(shell date +'%d%m%Y')

CXX = g++ -std=c++11
CPPFLAGS = -Wall 

LDFLAGS = -lboost_serialization

BUILDING_FOLDER = ../build
OUTPUT_FOLDER = ../$(BUILDING_FOLDER)/out

VPATH = include src tests build

.PHONY : all clean install $(OUTPUT_FOLDER)

all : $(OUTPUT_FOLDER) $(OUTPUT_FOLDER)/$(TITLE)

# Creating needed folders in order to build the app
$(OUTPUT_FOLDER) :
	@echo "Creating the folder : " $@
	mkdir -p $(OUTPUT_FOLDER)

# Building tha app from all the object files
$(OUTPUT_FOLDER)/$(TITLE) : $(wildcard $(BUILDING_FOLDER)/*.o)
	@echo "Compiling the app. It will be awailable in " $(OUTPUT_FOLDER)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $^ -o $@

# Compiling the object files
$(BUILDING_FOLDER)/%.o : %.cpp %.h
	@echo "Compiling the file : " $@
	$(CXX) $(CPPFLAGS) -c $^ -o $@

# Cleaning already built files
clean : 
	rm $(BUILDING_FOLDER)/*.o
	rm $(OUTPUT_FOLDER)/$(TITLE)

install :