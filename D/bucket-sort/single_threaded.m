load single_threaded.dat

mins = single_threaded(:,5);
maxs = single_threaded(:,4);
stdv = single_threaded(:,6);
time = single_threaded(:,3);
buckets = single_threaded(:,1);
best_time = min(time);
best_bucket = buckets(find(time == min(time)));

optimal_string = sprintf('Optimal Setting (%d, %d)', best_bucket, best_time);
%Plot Straight Plots
plot(best_bucket, best_time, "@31")
hold on;
plot(buckets, time);
title("Single Threaded Bucket Sort");
xlabel("# of Buckets");
ylabel("Time (ms)");
text(best_bucket-100, best_time - 100, optimal_string);
print -dpng "straight_single_threaded.png";
hold off;
% Plot the log plots
semilogx(best_bucket, best_time, "@31")
hold on;
semilogx(buckets, time);
title("Single Threaded Bucket Sort");
xlabel("# of Buckets");
ylabel("Time (ms)");
text(best_bucket-100, best_time - 100, optimal_string);
print -dpng "log_single_threaded.png";
