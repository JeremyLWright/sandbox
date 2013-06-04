SRCS=$(wildcard *.hs)
LIBS=$(wildcard Euler\*.hs)
PROGS=$(patsubst %.hs,%,$(SRCS))
all: $(PROGS)

%: %.hs $(LIBS)
	ghc -O2 --make $*.hs

test: all
	python EulerValues.py

clean: 
	rm $(PROGS) *.hi *.o
