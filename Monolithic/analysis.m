
function [x, y] = polyfit_and_resample(xdata, ydata, samples)
    p = polyfit(xdata, ydata', 2);
    x = linspace(min(xdata), max(xdata), samples);
    y = polyval(p,x);
endfunction

function [m, s, r] = compare(baseline, other, graphName, label1, label2)
    t = [0:size(baseline(:,2))(1)-1];

    mono = baseline(:,2)./baseline(:,2);
    funcs = baseline(:,2)./other(:,2);
    plot(t, mono, t, funcs);
    m = mean(funcs);
    s = std(funcs);
    line(xlim, [m m]);
    #line(xlim, [m+s m+s]);
    #line(xlim, [m-s m-s]);
    legend(label1, label2, cstrcat("Mean ", label2));
    title(graphName);
    print(strcat(graphName, ".png"), "-dpng");
    r = range(funcs);
endfunction

load("switch_state.out");
load("functions.out");
load("switch_state_nop.out");
load("functions_nop.out");
load("jump_table.out");
load("jump_table_nop.out");
load("msm.out");
load("msm_nop.out");
load("cpp_obj.out");

[funcAvgO0, funcDevO0, funcRangeO0] = compare(switch_state_nop  , functions_nop , "Functions O0"    , "Switch Sytle", "Calling Functions Style")
[funcAvgO2, funcDevO2, funcRangeO2] = compare(switch_state      , functions     , "Functions O2"    , "Switch Style", "Calling Functions Style")
[jumpavgO0, jumpDevO0, jumpRangeO0] = compare(switch_state_nop  , jump_table_nop, "Jump Table O0"   , "Switch Style", "Function Pointers")
[jumpAvgO2, jumpDevO2, jumpRangeO2] = compare(switch_state      , jump_table    , "Jump Table O2"   , "Switch Style", "Function Pointers")
[msmAvgO0, msmDevO0, msmRangeO0]    = compare(switch_state_nop  , msm_nop       , "MSM O0"          , "Switch Style", "Meta State")
[msmAvgO2, msmDevO2, msmRangeO2]    = compare(switch_state      , msm           , "MSM O2"          , "Switch Style", "Meta State")
[cpp_objAvgO2, cpp_objDevO2, cpp_objRangeO2]    = compare(switch_state      , cpp_obj           , "C++ O2"          , "Switch Style", "C++ Object")

mean_times = [mean(functions(:,2)), mean(jump_table(:,2)), mean(switch_state(:,2)), mean(cpp_obj(:,2)), mean(msm(:,2))];
mean_labels = ["Functions"; "Object Style"; "Switch"; "C++ Objs"; "C++ MSM"];
bar(mean_times)
set(gca, 'xticklabelmode', 'manual');
set(gca, 'xtick', [1 2 3 4 5]);
set(gca, 'yscale', 'log');
set(gca, 'xticklabel', mean_labels);
title("Average Optimized Times");
print -dpng "AverageO2Times.png"

mean_speedups = [funcAvgO2, jumpAvgO2, 1, cpp_objAvgO2, msmAvgO2];
bar(mean_speedups);
set(gca, 'xticklabelmode', 'manual');
set(gca, 'xtick', [1 2 3 4 5]);
%set(gca, 'yscale', 'log');
set(gca, 'xticklabel', mean_labels);
title("Optimized Speedups");
print -dpng "O2Speedups.png"
