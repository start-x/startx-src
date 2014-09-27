# Libname
LIBNAME=bikex.a

# Archiver
AR=ar
ARARGS=cvq

# Compiler
CC=g++
CFLAGS=

# Include dir
INCDIR=-I. -I../ovr/sdk/src

MODULES = device.a ovr.a unity.a
MODULES_INC = $(patsubst %.a, -I../%, $(MODULES))

# Obj dir
OBJDIR=obj

# Sources
SRC=$(wildcard *.cpp)

# Objects
OBJ=$(patsubst %.cpp,$(OBJDIR)/%.o,$(SRC))

# Dependencies
DEP=$(wildcard *.h)

$(LIBNAME): wrap $(OBJDIR) $(OBJ)
	rm -f $(LIBNAME)
	$(AR) $(ARARGS) $(LIBNAME) $(OBJ)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.cpp $(DEP)
	rm -f $@
	$(CC) -c -o $@ $< $(CFLAGS) $(INCDIR) $(MODULES_INC)

wrap: Wrap.h
	swig -python -module startx Wrap.h
	$(CC) -c -fpic Wrap_wrap.c -I/usr/include/python2.7 -I.
	$(CC) -shared Wrap_wrap.o -o ../device/scripts/_startx.so
	mv -v startx.py Wrap_wrap.c Wrap_wrap.o ../device/scripts/

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(LIBNAME)
	