SRCS=$(wildcard *.hs)
LIBS=$(wildcard Euler\*.hs)
PROGS=$(patsubst %.hs,%,$(SRCS))
all: $(PROGS)

%: %.hs $(LIBS)
	ghc -O2 --make $*.hs

test: euler.png

times.dat: $(PROGS)
	python EulerValues.py

euler.png: times.dat
	octave process.m

clean: 
	rm $(PROGS) *.hi *.o
