// © Copyright 2011 Jeremy Wright. All Rights Reserved.
bucket_data = fscanfMat("single_threaded.dat");
time = bucket_data(1:$,3); mins = bucket_data(1:$, 5); maxs=bucket_data(1:$,4);buckets=bucket_data(1:$, 1); stdv = bucket_data(1:$, 6);

plot2d(buckets, time, rect=[min(buckets), min(mins)-(min(mins)*.1), max(buckets), max(maxs)+(max(maxs)*.1)]);
errbar(buckets, time, time - mins, maxs-time);
xtitle("Single Threaded Bucket Sort", "Bucket Size", "Time");
xs2jpg(gcf(), "single_threaded_bucket.jpg");
