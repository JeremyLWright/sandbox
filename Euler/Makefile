SRCS=$(wildcard *.hs)
LIBS=$(wildcard Euler\*.hs)
PROGS=$(patsubst %.hs,%.exe,$(SRCS))
all: $(PROGS)

%.exe: %.hs $(LIBS)
	ghc -O2 --make $*.hs

clean: 
	rm $(PROGS) *.hi *.o
