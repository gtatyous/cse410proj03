EXE = proj3
SOURCES = main.cpp
OBJECTS := $(SOURCES:%.cpp=%.o)
CXXFLAGS = -Wall -std=c++11
CXX = clang++
$(EXE) : $(OBJECTS) 
	$(CXX) $^ -o $@
clean:
	rm -rf *o $(EXE)
