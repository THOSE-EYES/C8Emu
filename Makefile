TITLE = CHIP-8.out

CXX = g++ -std=c++11
CPPFLAGS = -Wall -Iinclude 

LDFLAGS = -lboost_serialization -lpthread -lopenal

#ESSENTIAL FOLDERS
BUILDING_FOLDER = build
OUTPUT_FOLDER = $(BUILDING_FOLDER)/out

SOURCES_FOLDER = src
HEADERS_FOLDER = include
TESTS_FOLDER = tests

#AUTOBUILD ALL THE SOURCE FILES
SOURCES = $(wildcard $(SOURCES_FOLDER)/*.cpp)
OBJECTS = $(patsubst $(SOURCES_FOLDER)/%.cpp, $(BUILDING_FOLDER)/%.o, $(SOURCES))

VPATH = include src test build

#PHONY TARGETS
.PHONY : clean install all create_directories

all :  $(TITLE)

clean :
	rm -rf $(BUILDING_FOLDER)

create_directories : 
	mkdir -p $(OUTPUT_FOLDER)

#TARGETS AND PREREQIUSITS
$(TITLE) : $(OBJECTS)

$(OBJECTS) : $(SOURCES) create_directories

# RULES
%.out : $(BUILDING_FOLDER)/*.o 
	$(CXX) $(LDFLAGS) $^ -o $(OUTPUT_FOLDER)/$@

$(BUILDING_FOLDER)/%.o : $(SOURCES_FOLDER)/%.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@
