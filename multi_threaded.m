load single_threaded.dat

time = single_threaded(:,2:end);
stime_stats = statistics(time')';
s_avg_time = stime_stats(:,6);
s_buckets = single_threaded(:,1);
s_mins = stime_stats(:,1);
s_maxs = stime_stats(:,5);
s_q1 = stime_stats(:,2);
s_med = stime_stats(:,3);
s_q3 = stime_stats(:,4);
s_best_time = min(s_avg_time);
s_best_bucket = s_buckets(find(s_avg_time == min(s_avg_time)));

load multi_threaded.dat

m_time = multi_threaded(:,2:end);
time_stats = statistics(m_time')';
m_avg_time = time_stats(:, 6);
m_buckets = multi_threaded(:,1);
m_mins = time_stats(:,1);
m_maxs = time_stats(:,5);
m_q1 = time_stats(:,2);
m_med = time_stats(:,3);
m_q3 = time_stats(:,4);
m_best_time = min(m_avg_time);
m_best_bucket = m_buckets(find(m_avg_time == min(m_avg_time)));

m_optimal_string = sprintf('Optimal Setting %d buckets in %d ms', m_best_bucket, m_best_time);
s_optimal_string = sprintf('Optimal Setting %d buckets in %d ms', s_best_bucket, s_best_time);

subplot(2,2, [1 2]);
plot(s_best_bucket, s_best_time, '@', s_buckets, s_avg_time);
text(s_best_bucket-2500, s_best_time+20, s_optimal_string);
title('Single-Threaded Bucket Sort');
xlabel('# of Buckets');
ylabel('Time (ms)');

subplot(2,2,[3 4]);
errorbar(s_buckets, s_med, s_med-s_q1, s_q3-s_med);
axis_x_min = 0;%min(s_buckets);
axis_x_max = max(s_buckets);
axis_y_min = min(s_q1)-min(s_q1)*.1;
axis_y_max = max(s_q3)+max(s_q3)*.1;
axis([axis_x_min axis_x_max axis_y_min axis_y_max]);
title('Single-Threaded Standard Deviation');
xlabel('# of Buckets');
ylabel('Time (ms)');
%% Range Plot
print -dpng 'single_threaded.png';
hold off


%Plot Multi Data
subplot(2,2, [1 2]);
plot(m_best_bucket, m_best_time, '@', m_buckets, m_avg_time)
text(m_best_bucket+10, m_best_time + 10, m_optimal_string);
title('Multi-Threaded Bucket Sort');
xlabel('# of Buckets');
ylabel('Time (ms)');

%% Std-dev plot
subplot(2,2, [3 4]);
errorbar(m_buckets, m_med, m_med-m_q1, m_q3-m_med);
axis_x_min = 0;%min(m_buckets);
axis_x_max = max(m_buckets);
axis_y_min = min(m_q1)-min(m_q1)*.1;
axis_y_max = max(m_q3)+max(m_q3)*.1;
axis([axis_x_min axis_x_max axis_y_min axis_y_max]);
title('Multi-Threaded Standard Deviation');
xlabel('# of Buckets');
ylabel('Time (ms)');
%% Range Plot
print -dpng 'multi_threaded.png';
hold off

clf();
plot(m_buckets, m_avg_time, s_buckets, s_avg_time);
legend('Multi-Threaded', 'Single Threaded');
title('Threading Compared');
xlabel('# of Buckets');
ylabel('Time (ms)');
print -dpng 'threading_compared.png';

