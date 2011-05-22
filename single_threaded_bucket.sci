// © Copyright 2011 Jeremy Wright. All Rights Reserved.
bucket_data = fscanfMat("single_threaded.dat");
time = bucket_data(1:$,3); mins = bucket_data(1:$, 5); maxs=bucket_data(1:$,4);buckets=bucket_data(1:$, 1);
plot2d(buckets, time, rect=[min(buckets), min(mins)-500, max(buckets), max(maxs)+500]);
errbar(buckets, time, time - mins, maxs-time);
plot2d(buckets, time);
xtitle("Single Threaded Bucket Sort", "Time (ms)", "Bucket Size");
errbar(buckets, time, time - mins, maxs-time);
xs2jpg(gcf(), "single_threaded_bucket.jpg");
