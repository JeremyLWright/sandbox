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
%Plot all data. 
plot(buckets, time, m_buckets, m_time, best_bucket, best_time, '@', m_best_bucket, m_best_time, 'o');
legend('Single-Threaded', 'Multi-Threaded', 'ST Optimal', 'MT Optimal');

title('Bucket Sort');
xlabel('# of Buckets');
ylabel('Time (ms)');
print -dpng 'straight_threaded.png';

%Plot Single Data
subplot(2, 1, 1);
plot(best_bucket, best_time, '@', buckets, time)
text(best_bucket-100, best_time - 100, optimal_string);
title('Single-Threaded Bucket Sort');
xlabel('# of Buckets');
ylabel('Time (ms)');
%Std-Dev plot
subplot(2,1, 2);
plot(buckets, time, buckets, maxs, buckets, mins);
legend('Standard Deviation', 'Max Runtimes', 'Min Runtimes');
hold on;
errorbar(buckets, time, stdv/2);
title('Single-Threaded Standard Deviation');
xlabel('# of Buckets');
ylabel('Time (ms)');
hold off

print -dpng 'straight_single_threaded.png';

%Plot Multi Data
subplot(2,2, [1 2]);
plot(m_best_bucket, m_best_time, '@', m_buckets, m_time)
text(m_best_bucket+10, m_best_time + 10, m_optimal_string);
title('Multi-Threaded Bucket Sort');
xlabel('# of Buckets');
ylabel('Time (ms)');

%% Std-dev plot
subplot(2,2, [3 4]);
plot(m_buckets, m_time, m_buckets, m_maxs, m_buckets, m_mins);
legend('Standard Deviation', 'Max Runtimes', 'Min Runtimes');
hold on;
errorbar(m_buckets, m_time, m_stdv/2);
title('Multi-Threaded Standard Deviation');
xlabel('# of Buckets');
ylabel('Time (ms)');
%% Range Plot
print -dpng 'straight_multi_threaded.png';
hold off
