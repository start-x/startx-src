# Libname
LIBNAME=ovr.a

# OVR library
OVRLIB=sdk/lib/linux/Release/x86_64/libovr.a

# Archiver
AR=ar
ARARGS=cvq

# Compiler
CC=g++
CFLAGS=-lGL -ludev -lXrandr -lX11 -lpthread

# Include dir
INCDIR=-I. -Isdk/src
INCDIRTESTS=-I. -I.. -Isdk/src

# Obj dir
OBJDIR=obj

# Sources
SRC=$(wildcard *.cpp)
SRCTESTS=tests/tests.cpp

# Objects
OBJ=$(patsubst %.cpp,$(OBJDIR)/%.o,$(SRC))

# Dependencies
DEP=$(wildcard *.h)

$(LIBNAME): $(OBJDIR) $(OBJ)
	rm -f $(LIBNAME)
	$(AR) $(ARARGS) $(LIBNAME) $(OBJ)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.cpp $(DEP)
	rm -f $@
	$(CC) -c -o $@ $< $(CFLAGS) $(INCDIR)

.PHONY: tests

tests: $(LIBNAME)
	$(CC) -o tests/$@.out $(SRCTESTS) $(LIBNAME) $(OVRLIB) $(INCDIRTESTS) $(CFLAGS)

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(LIBNAME)
	
