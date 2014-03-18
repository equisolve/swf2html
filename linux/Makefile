
# Currently supported platforms are LINUX
PLATFORM       := LINUX

# DEBUG can be set to YES to include debugging info, or NO otherwise
DEBUG          := NO

#****************************************************************************
# Linux configuration seciton
#****************************************************************************

ifeq (LINUX, ${PLATFORM})

CC     := gcc
CXX    := gcc
GCC    := gcc
AR     := ar rc
RANLIB := ranlib

DEFS := -DLINUX
INCS :=
LIBS := -lm -lstdc++ -L. -lswf2html -lz

endif

#****************************************************************************
# Include paths
#****************************************************************************

INCS := -I../ \
		-I./ \
        ${INCS}

#****************************************************************************
# Makefile code common to all platforms
#****************************************************************************

CFLAGS   := ${DEFS}
CXXFLAGS := ${DEFS}

ifeq (YES, ${DEBUG})
  CFLAGS := ${CFLAGS} -g
  CXXFLAGS := ${CXXFLAGS} -g
endif

ifeq (NO, ${DEBUG})
  CFLAGS := ${CFLAGS} -O3
  CXXFLAGS := ${CXXFLAGS} -O3
endif

#****************************************************************************
# Targets of the build
#****************************************************************************

OUTPUT := swf2html

LIBOUTPUT := libswf2html.a

all: ${OUTPUT}

#****************************************************************************
# swf2html source files
#****************************************************************************

SRCS := ../swf2html_main.cpp

LIBSRCS := ../swf2html.cpp ../swf2html_stdio.cpp
		
OBJS := $(addsuffix .o,$(basename ${SRCS}))

LIBOBJS := $(addsuffix .o,$(basename ${LIBSRCS}))

#****************************************************************************
# Output
#****************************************************************************

${OUTPUT}: ${OBJS} ${LIBOUTPUT}
	${GCC} -o $@ ${OBJS} ${LIBS}

${LIBOUTPUT}: ${LIBOBJS}
	${AR} $@ ${LIBOBJS}
	${RANLIB} $@

#****************************************************************************
# Rules
#****************************************************************************

# Rules for compiling source files to object files
%.o : %.cpp
	${CXX} -c ${CXXFLAGS} ${INCS} $< -o $@

clean:
	-rm -f ${OBJS} ${OUTPUT} ${LIBOBJS} ${LIBOUTPUT}

depend:
	makedepend -p${OBJPATH}/ ${INCS} ${SRCS} ${LIBSRCS}


