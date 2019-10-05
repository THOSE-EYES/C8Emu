TITLE = CHIP-8.out

#ESSENTIAL FOLDERS
BUILDING_FOLDER = build
OUTPUT_FOLDER = $(BUILDING_FOLDER)/out

SOURCES_FOLDER = src
HEADERS_FOLDER = include
TESTS_FOLDER = tests

#WHERE TO LOOK FOR THE FILES
VPATH = $(BUILDING_FOLDER) $(SOURCES_FOLDER) $(HEADERS_FOLDER) $(TESTS_FOLDER)

#COMPILER'S SETTINGS
CXX = g++ -std=c++11
CPPFLAGS = -Wall -I$(HEADERS_FOLDER) -I$(TESTS_FOLDER) -O3

LDFLAGS = -lboost_serialization -lpthread -lopenal

#AUTOBUILD ALL THE SOURCE FILES
SOURCES = $(shell find -type f -name '*.cpp' -exec basename {} ';')
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

#TARGETS AND PREREQIUSITS
all : $(TITLE)

$(OBJECTS) : $(SOURCES) create_directories

$(TITLE) : $(OBJECTS)

# RULES
%.out : $(BUILDING_FOLDER)/*.o 
	@echo "HELLO!"
	$(CXX) $(LDFLAGS) $^ -o $(OUTPUT_FOLDER)/$@

$(BUILDING_FOLDER)/%.o : %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $(BUILDING_FOLDER)/$@

#PHONY TARGETS
.PHONY : clean install create_directories

clean :
	rm -rf $(BUILDING_FOLDER)

create_directories : 
	mkdir -p $(OUTPUT_FOLDER)

install :