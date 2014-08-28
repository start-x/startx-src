# Libname
LIBNAME=bikex.a

# Archiver
AR=ar
ARARGS=cvq

# Compiler
CC=g++
CFLAGS=

# Include dir
INCDIR=.

MODULES = breaks.a ovr.a sensors.a unity.a
MODULES_INC = $(patsubst %.a, -I../%, $(MODULES))

# Obj dir
OBJDIR=obj

# Sources
SRC=$(wildcard *.cpp)

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
	$(CC) -c -o $@ $< $(CFLAGS) -I$(INCDIR) $(MODULES_INC)

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(LIBNAME)
	