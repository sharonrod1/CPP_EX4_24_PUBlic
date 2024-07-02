CXX = g++
CXXFLAGS = -std=c++17 -Wall -fPIC `pkg-config --cflags Qt5Core Qt5Widgets` -I.  # Include the current directory
LDFLAGS = `pkg-config --libs Qt5Core Qt5Widgets`

DEMO_SOURCES = Demo.cpp
MAIN_SOURCES = main.cpp complex.cpp
TEST_SOURCES = test.cpp

HEADERS = node.hpp tree.hpp complex.hpp utils.hpp doctest.h

DEMO_OBJECTS = $(DEMO_SOURCES:.cpp=.o)
MAIN_OBJECTS = $(MAIN_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

DEMO_EXEC = demo
MAIN_EXEC = main
TEST_EXEC = test

.PHONY: all clean

all: $(DEMO_EXEC) $(MAIN_EXEC) $(TEST_EXEC)

$(DEMO_EXEC): $(DEMO_OBJECTS) complex.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(MAIN_EXEC): $(MAIN_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_EXEC): $(TEST_OBJECTS) complex.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(DEMO_OBJECTS) $(MAIN_OBJECTS) $(TEST_OBJECTS) $(DEMO_EXEC) $(MAIN_EXEC) $(TEST_EXEC)
