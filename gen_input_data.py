from random import uniform
from sys import maxint

inputfile = open("random_list.dat", "w")
for i in range(10000000):
    inputfile.write("%d\n"%(uniform(1,maxint)))
