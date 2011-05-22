DMD=dmd
DOCDIR=doc

#DFLAGS=-O -release -inline -nofloat -w -d -Isrc -Iimport
DFLAGS=-unittest -g -d
#DFLAGS=-unittest -cov -g -d

SRCS=main.d

all: bucket_sort

.d.obj:
	$(DMD) -c $(DFLAGS) $*

.PHONY: all


bucket_sort: $(SRCS)
	$(DMD) $(DFLAGS) $(SRCS)
