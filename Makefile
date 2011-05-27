DMD=dmd
DOCDIR=doc

DFLAGS=-O -release -inline -nofloat -w -d -Isrc -Iimport
#DFLAGS=-unittest -g -d
#DFLAGS=-unittest -cov -g -d

SRCS=main.d

all: mbucket_sort sbucket_sort 

.d.obj:
	$(DMD) -c $(DFLAGS) $*

.PHONY: all


sbucket_sort: $(SRCS)
	$(DMD) $(DFLAGS) $(SRCS) -ofsbucket_sort

mbucket_sort: $(SRCS)
	$(DMD) $(DFLAGS) -version=MultiThreaded $(SRCS) -ofmbucket_sort

