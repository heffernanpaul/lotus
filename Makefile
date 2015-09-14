
V=0
CXX=/usr/bin/g++


LIBRARIES := -L/System/Library/Frameworks/OpenGL.framework/Libraries -g -O2
LIBRARIES += -framework Cocoa -framework OpenGL -framework GLUT -framework IOKit -framework SFML
LIBRARIES +=  -framework CoreVideo /usr/local/lib/libglfw3.a /usr/local/lib/libSOIL.a /usr/lib/libglew.a -framework AGL
LIBRARIES +=  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio //usr/local/lib/libassimp.dylib
#INCLUDES := -I/usr/local/include/assimp -I/usr/include -I/usr/local/include
INCLUDES += -I/usr/include -I/usr/local/include $(addprefix -I, $(wildcard raytracer/*))
INCLUDES +=  $(addprefix -I, $(wildcard src/*))

LDLIBS := $(LIBRARIES)
WXINCLUDES := -I/usr/local/lib/wx/include/osx_cocoa-unicode-static-3.0 -I/usr/local/include/wx-3.0 -D_FILE_OFFSET_BITS=64 -DwxDEBUG_LEVEL=0 -D__WXMAC__ -D__WXOSX__ -D__WXOSX_COCOA__
CXXFLAGS := -std=c++0x -DDEBUG -g $(WXINCLUDES) $(INCLUDES) -MMD -Wwritable-strings

all: main

SRCS := $(wildcard src/*.c*)
SRCS += $(wildcard src/common/*.c*)
SRCS += $(wildcard src/model/*.c*)
OBJS=$(subst .cpp,.o,$(SRCS))

DEPS = $(SRCS:.cpp=.d)

#-include $(DEPS)




main: $(OBJS)
	g++ $(CXXFLAGS) $(LIBRARIES) -o main $(OBJS)

clean:
	$(RM) $(OBJS) $(DEP)

dist-clean: clean
	$(RM) main
