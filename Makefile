CXX = g++
CXXFLAGS = -std=c++17 -Wall

all:
	$(CXX) $(CXXFLAGS) *.cpp -o loadbalancer

clean:
	rm -f loadbalancer