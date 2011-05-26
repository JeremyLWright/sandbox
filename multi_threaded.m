load single_threaded.dat

mins = single_threaded(:,5);
maxs = single_threaded(:,4);
stdv = single_threaded(:,6);
time = single_threaded(:,3);
buckets = single_threaded(:,1);
best_time = min(time);
best_bucket = buckets(find(time == min(time)));


load multi_threaded.dat

m_mins = multi_threaded(:,5);
m_maxs = multi_threaded(:,4);
m_stdv = multi_threaded(:,6);
m_time = multi_threaded(:,3);
m_buckets = multi_threaded(:,1);
m_best_time = min(m_time);
m_best_bucket = buckets(find(m_time == min(m_time)));

m_optimal_string = sprintf('MT Optimal Setting (%d, %d)', m_best_bucket, m_best_time);


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

%Plot Straight Plots
plot(m_best_bucket, m_best_time, "@31")
plot(m_buckets, m_time);
title("Bucket Sort");
xlabel("# of Buckets");
ylabel("Time (ms)");
text(m_best_bucket-100, m_best_time - 100, m_optimal_string);
print -dpng "straight_multi_threaded.png";


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


% Plot the log plots
semilogx(m_best_bucket, m_best_time, "@31")
hold on;
semilogx(m_buckets, m_time);
title("Threaded Bucket Sort");
xlabel("# of Buckets");
ylabel("Time (ms)");
text(m_best_bucket-100, m_best_time - 100, m_optimal_string);
print -dpng "log_multi_threaded.png";
