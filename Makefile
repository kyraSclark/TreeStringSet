CXX = clang++
CXXFLAGS = -g -Wall -Wextra -pedantic -std=c++1z

all: treestringset-test

treestringset-test: treestringset-test.o treestringset.o
	$(CXX) -o -lranduint32 treestringset-test treestringset-test.o treestringset.o -ltestinglogger

treestringset-test.o: treestringset-test.cpp treestringset.cpp treestringset.hpp
	$(CXX) $(CXXFLAGS) -c treestringset-test.cpp treestringset.cpp

treestringset.o: treestringset.cpp treestringset.hpp
	$(CXX) $(CXXFLAGS) -c treestringset.cpp

clean:
	rm -rf treestringset-test *.o