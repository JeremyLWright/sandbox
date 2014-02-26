CXX=$(HOME)/hemi_platform_tools/compilers/4.8.3/x86_64-unknown-linux-gnu/bin/x86_64-unknown-linux-gnu-g++
CXX_FLAGS=-std=gnu++11 -Wall -O3 -I$(PWD)/dist/public/nss -I$(PWD)/dist/Linux3.2_x86_64_glibc_PTH_64_OPT.OBJ/include
LD_FLAGS=-L$(PWD)/dist/Linux3.2_x86_64_glibc_PTH_64_OPT.OBJ/lib -lnss3 -lnssutil3 -lplc4 -lplds4 -lnspr4


rainbow: main.cpp dist
	$(CXX) $(CXX_FLAGS) main.cpp -o rainbow $(LD_FLAGS)

dist: nss nspr
	cd nss && BUILD_OPT=1 USE_64=1 $(MAKE) nss_build_all 

nspr:
	hg clone https://hg.mozilla.org/projects/nspr
	cd nspr
	hg update NSPR_4_10_2_RTM

nss:
	hg clone https://hg.mozilla.org/projects/nss
	cd nss
	hg update NSS_3_15_5_RTM

clean:
	cd nss && $(MAKE) clean -j8 && cd ..
	rm -rf dist rainbow sample3

sample3: dist
	$(CXX) $(CXX_FLAGS) sample3.cpp -o sample3 $(LD_FLAGS)

