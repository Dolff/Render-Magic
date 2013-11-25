CXX    = g++
CFLAGS = -Wall -g

ifeq ($(shell uname), Darwin)
    LIBS = -framework GLUT -framework OpenGL -framework Cocoa
else
    LIBS = -lglut -lGL -lGLU -lGLEW -lglui
endif

GLUI = /afs/nd.edu/coursefa.12/cse/cse40166.01
ifneq "$(wildcard $(GLUI))" ""
    INCPATH += -I$(GLUI)/include
    LIBPATH += -L$(GLUI)/lib
endif

FREEGLUT = /afs/nd.edu/user37/ccl/software/external/freeglut
ifneq "$(wildcard $(FREEGLUT))" ""
    INCPATH += -I$(FREEGLUT)/include
    LIBPATH += -L$(FREEGLUT)/lib
endif

GLEW = /afs/nd.edu/user37/ccl/software/external/glew
ifneq "$(wildcard $(GLEW))" ""
    INCPATH += -I$(GLEW)/include
    LIBPATH += -L$(GLEW)/lib -Wl,--rpath -Wl,$(GLEW)/lib
endif

all: renderMagic

clean:
	rm -f *.o renderMagic

depend:
	rm -f Makefile.bak
	mv Makefile Makefile.bak
	sed '/^# DEPENDENCIES/,$$d' Makefile.bak > Makefile
	echo '# DEPENDENCIES' >> Makefile
	$(CXX) -MM *.cpp >> Makefile

.c.o: 	
	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

.cc.o: 	
	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

.cpp.o: 	
	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

renderMagic: main.o
	$(CXX) $(CFLAGS) $(INCPATH) -o $@ $^ $(LIBPATH) $(LIBS)


# DEPENDENCIES
main.o: main.cpp
