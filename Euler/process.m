[names, times] = textread('times.dat', '%s %f')
bar(times)
print -dpng euler.png
