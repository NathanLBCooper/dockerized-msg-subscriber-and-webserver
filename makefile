include conanbuildinfo.mak
# https://docs.conan.io/en/latest/integrations/make.html#make

CC=clang++
CFLAGS=-std=c++17 -Wall -c
CPPFLAGS=
CXXFLAGS=
LDFLAGS=
LDLIBS=

SOURCES= $(filter-out $(wildcard ./src/*_test.cpp),$(wildcard ./src/*.cpp))
OBJECTS= $(SOURCES:.cpp=.o)
EXECUTABLE=program.exe

TESTSOURCES= $(filter-out ./src/main.cpp,$(wildcard ./src/*.cpp)) $(wildcard ./catch/*.cpp)
TESTOBJECTS=$(TESTSOURCES:.cpp=.o)
TESTEXECUTABLE=tests.exe

CFLAGS += $(CONAN_CFLAGS)
CPPFLAGS += $(addprefix -I, $(CONAN_INCLUDE_DIRS))
CPPFLAGS += $(addprefix -D, $(CONAN_DEFINES))
CXXFLAGS += $(CONAN_CXXFLAGS)
LDFLAGS += $(addprefix -L, $(CONAN_LIB_DIRS))
LDLIBS += $(addprefix -l, $(CONAN_LIBS))

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJECTS) -o $@

debug: CFLAGS += -g
debug: $(SOURCES) $(EXECUTABLE)

tests: CFLAGS += -g
tests: $(TESTSOURCES) $(TESTEXECUTABLE)
	./$(TESTEXECUTABLE)

$(TESTEXECUTABLE): $(TESTOBJECTS)
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $(TESTOBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS) $(TESTEXECUTABLE) $(TESTOBJECTS)