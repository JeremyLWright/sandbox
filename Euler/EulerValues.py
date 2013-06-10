import sys, time, subprocess
problems = (
        ("001", "233168"),
        ("002", "4613732"),
        ("003", "6857"),
        ("004", "906609"),
        ("005", "232792560"),
        ("006", "25164150"),
        ("007", "104743"),
        ("008", "40824"),
        ("009", "31875000"),
        ("010", "142913828922"),
        ("011", "70600674"),
        ("012", "76576500"),
        ("013", "5537376230"),
        ("014", "(525,837799)"),
        ("015", "137846528820"),
        ("016", "1366"),
        ("017", "21124"),
        ("018", "1074"),
        ("019", "171"),
        ("020", "648"),
        ("021", "31626"),
        ("022", "871198282"),
        ("023", "4179871"),
        ("024", "\"2783915460\""),
        ("025", "4782"),
        ("026", "983"),
        ("027", "-59231"),
        ("029", "9183"),
        ("034", "40730"),
        ("046", "\"working...\""),
)



ftime = open("times.dat", "w")
for p,a in problems:
    start_time = time.time()
    proc = subprocess.Popen("./"+p, stdout=subprocess.PIPE)
    end_time = time.time() - start_time
    result = proc.stdout.read().strip()
    if result == a:
        print "[{0}] Passed {1} seconds".format(p, end_time)
    else:
        print "[{0}] Failed Expected: {1} Got: {2}".format(p, result, a)
    ftime.write("problem_"+p+"\t"+str(end_time)+"\n")
