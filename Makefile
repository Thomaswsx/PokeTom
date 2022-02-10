appname := pokeTom

CXX=g++
CXXFLAGS := -std=c++11

srcfiles := $(shell find . -maxdepth 1 -name "*.cpp")
objects  := $(patsubst %.cpp, %.o, $(srcfiles))

all: $(appname)

$(appname): $(objects)
	$(CXX) $(CXXFLAGS) $(objects) -o $(appname)

clean:
	rm -f $(objects)

