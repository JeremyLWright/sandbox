DMD=dmd
DOCDIR=doc

#DFLAGS=-O -release -inline -nofloat -w -d -Isrc -Iimport
DFLAGS=-unittest -g -d
#DFLAGS=-unittest -cov -g -d

SRCS=main.d RedBlackNode.d

all: red_black_tree

.d.obj:
	$(DMD) -c $(DFLAGS) $*

.PHONY: all


red_black_tree: $(SRCS)
	$(DMD) $(DFLAGS) $(SRCS)
