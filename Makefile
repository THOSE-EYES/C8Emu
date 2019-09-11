TITLE = CHIP-8_$(shell date +'%d%m%Y')

CXX = g++ -std=c++11
CPPFLAGS = -Wall -Iinclude

LDFLAGS = -lboost_serialization -lpthread

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

all : create_directories $(OBJECTS)

clean :
	rm -rf $(BUILDING_FOLDER)

create_directories : 
	mkdir -p $(OUTPUT_FOLDER)

#TARGETS AND PREREQIUSITS
$(TITLE) : $(OBJECTS)

$(OBJECTS) : $(SOURCES)

# RULES
% : $(BUILDING_FOLDER)/%.o 
	$(CXX) $(LDFLAGS) $^ -o $(OUT_DIR)/$@

$(BUILDING_FOLDER)/%.o : $(SOURCES_FOLDER)/%.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@
