[names, times] = textread('times.dat', '%s %f');
bar(times);
colormap(summer (64))
ylabel("Time (seconds)")
xlabel("Problem Number")
title("Jeremy's Project Euler Progress")
print -dpng euler.png;
