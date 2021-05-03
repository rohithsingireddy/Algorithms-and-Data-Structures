CXX=g++
CXXFLAGS=-Wall -g -D NANANA -O2
TARGET=exam

all: containerHelper.h
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp $(objects)

clean:
	rm $(TARGET)
