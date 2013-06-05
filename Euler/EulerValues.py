import sys, time, subprocess
problems = (
        ("001", 233168),
        ("002", 4613732),
        ("003", 6857),
        ("004", 906609),
        ("005", 232792560),
        ("006", 25164150),
        ("007", 104743),
        ("008", 40824),
        ("009", 31875000),
        ("010", 142913828922),
        ("011", 70600674),
        ("012", 76576500),
        ("013", 5537376230),
        ("014", 837799),
        ("015", 137846528820),
        ("016", 1366),
        ("017", 21124),
        ("018", 1074),
        #"019,: 171,),
        ("020", 648),
        ("021", 31626),
#        "022":
#        "023":
#        "024":
#        "025":
#        "029":
#        "034":
#        "046":
)



ftime = open("times.dat", "w")
for p,a in problems:
    start_time = time.time()
    proc = subprocess.Popen("./"+p, stdout=subprocess.PIPE)
    end_time = time.time() - start_time
    if int(proc.stdout.read()) == a:
        print "[{0}] Passed {1} seconds".format(p, end_time)
        ftime.write("problem_"+p+"\t"+str(end_time)+"\n")
