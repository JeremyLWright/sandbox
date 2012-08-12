
function [x, y] = polyfit_and_resample(xdata, ydata, samples)
    p = polyfit(xdata, ydata', 2);
    x = linspace(min(xdata), max(xdata), samples);
    y = polyval(p,x);
endfunction

function [m, s, r] = compare(baseline, other, graphName, label1, label2)
    t = [0:size(baseline(:,2))(1)-1];

    mono = baseline(:,2)./baseline(:,2);
    funcs = other(:,2)./baseline(:,2);
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

[funcAvgO0, funcDevO0, funcRangeO0] = compare(switch_state_nop, functions_nop, "Functions O0", "Switch Sytle", "Calling Functions Style")
[funcAvgO2, funcDevO2, funcRangeO2] = compare(switch_state, functions, "Functions O2", "Switch Style", "Calling Functions Style")
[jumpavgO0, jumpDevO0, jumpRangeO0] = compare(switch_state_nop, jump_table_nop, "Jump Table O0", "Switch Style", "Function Pointers")
[jumpAvgO2, jumpDevO2, jumpRangeO2] = compare(switch_state, jump_table, "Jump Table O2", "Switch Style", "Function Pointers")

