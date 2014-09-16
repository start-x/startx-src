# Libname
LIBNAME=device.a

# Archiver
AR=ar
ARARGS=cvq

# Compiler
CC=g++
CFLAGS=

# Include dir
INCDIR=-I.
INCDIRTESTS=-I. -I..

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
	$(CC) -c -o $@ $< $(MOCK_FLAG) $(CFLAGS) $(INCDIR)

.PHONY: tests

tests: $(LIBNAME)
	$(CC) -o $@/$@.out $(SRCTESTS) $(LIBNAME) $(INCDIRTESTS)

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(LIBNAME)
	