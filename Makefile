# appname := simulator

# CXX := g++
# CXXFLAGS := -Wall -g

# srcfiles := $(shell find . -maxdepth 3 -name "*.cpp")
# objects  := $(patsubst %.cpp, %.o, $(srcfiles))

# all: $(appname)

# $(appname): $(objects)
# 	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(appname) $(objects) $(LDLIBS)

# depend: .depend

# .depend: $(srcfiles)
# 	rm -f ./.depend
# 	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

# clean:
# 	rm -f $(objects)

# dist-clean: clean
# 	rm -f *~ .depend

# include .depend

# Makefile for building Graphics demo on command line
FILES 	= $(wildcard src/*.cpp) $(wildcard lib/*.cpp)
OBJS	= $(FILES:.cpp=.o)
TARGET 	= demo

ifeq ($(OS), Windows_NT)
	EXT = .exe
	RUN = $(TARGET)
	RM	= del
	CFLAGS = -IC:\tools\freeglut\include -Iinclude
	LFLAGS = -LC:\tools\freeglut\lib\x64
	LFLAGS += -lfreeglut -lglu32 -lopengl32 -Wl,--subsystem,windows
	CXX = g++
	DOBJS = $(subst /,\,$(OBJS))
else
	EXT =
	RM 	= rm -f
	RUN = ./$(TARGET)
	CXX = g++
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
	    CFLAGS = -I/usr/include
		LFLAGS = -lGL -lGLU -lglut
	endif
	ifeq ($(UNAME_S), Darwin)
		CFLAGS = -I/usr/local/include -Iinclude
		CFLAGS += -Wno-deprecated-declarations
		LFLAGS = -framework OpenGL -framework GLUT
	endif
	DOBJS = $(OBJS)
endif

.PHONY: all
all:	$(TARGET)$(EXT)

$(TARGET)$(EXT):	$(OBJS)
	g++ -o $(TARGET)$(EXT) $(OBJS) $(LFLAGS)

%.o:	%.cpp
	g++ -c $< -o $@ $(CFLAGS)

.PHONY: run
run:	$(TARGET)$(EXT)
		$(RUN)

.PHONY: clean
clean:
	$(RM) $(TARGET)$(EXT) $(DOBJS)

