[compile_names, compile_times] = textread('compile.dat', '%s %f');
[run_names, run_times] = textread('times.dat', '%s %f');
subplot(2,1,1)
bar(run_times);
colormap(summer (64))
ylabel("Run Time (seconds)")
title("Jeremy's Project Euler Progress")

subplot(2,1,2)
bar(compile_times)
colormap(summer (64))
ylabel("Compile Time (seconds)")
xlabel("Problem Number")
print -dpng euler.png;

