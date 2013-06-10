SRCS=$(wildcard *.hs)
LIBS=$(wildcard Euler\*.hs)
PROGS=$(patsubst %.hs,%,$(SRCS))
all: $(PROGS)

%: %.hs $(LIBS)
	echo -n "$*.hs\t" >> compile.dat
	/usr/bin/time --format=%e ghc -O2 --make $*.hs 2>> compile.dat

test: euler.png

times.dat: $(PROGS)
	python EulerValues.py

euler.png: times.dat
	octave process.m

clean: 
	rm $(PROGS) *.hi *.o *.dat Euler/*.hi Euler/*.o
