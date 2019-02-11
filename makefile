CC=clang++
CFLAGS=-std=c++17 -Wall -c
LDFLAGS=

SOURCES= $(filter-out $(wildcard ./src/*_test.cpp),$(wildcard ./src/*.cpp))
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=program.exe

TESTSOURCES= $(filter-out ./src/main.cpp,$(wildcard ./src/*.cpp)) $(wildcard ./catch/*.cpp)
TESTOBJECTS=$(TESTSOURCES:.cpp=.o)
TESTEXECUTABLE=tests.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

debug: CFLAGS += -g
debug: $(SOURCES) $(EXECUTABLE)

tests: CFLAGS += -g
tests: $(TESTSOURCES) $(TESTEXECUTABLE)
	./$(TESTEXECUTABLE)

$(TESTEXECUTABLE): $(TESTOBJECTS)
	$(CC) $(LDFLAGS) $(TESTOBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS) $(TESTEXECUTABLE) $(TESTOBJECTS)