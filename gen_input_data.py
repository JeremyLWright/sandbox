from random import uniform
from sys import maxint

inputfile = open("random_list.dat", "w")
data = []
for i in range(10000000):
    data.append(uniform(1,1000000))
for datum in data:
    inputfile.write("%d\n"%datum)
