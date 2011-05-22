//Process the bucket sorted data, and save the plots.
//© Copyright 2011 Jeremy Wright. All Rights Reserved.

bucket_data = fscanfMat("bucket_data.dat");
threads = bucket_data(1:$, 1);
bucket_size = bucket_data(1:$, 2);
time = bucket_data(1:$, 3);

f = scf(0);
plot3d(threads, bucket_size, time);
xtitle("Multithreaded Bucket Sort", "# of Threads", "Bucket Size", "Time (ms)");
xs2jpg(gcf(), "bucket_3d.jpg");

scf(1);
plot2d(threads, time);
xtitle("Multithreaded Bucket Sort", "Time (ms)", "# of Threads");
xs2jpg(gcf(), "bucket_threads_vs_time.jpg");


scf(2);
plot2d(bucket_size, time);
xtitle("Multithreaded Bucket Sort", "Time (ms)", "Bucket Size");
xs2jpg(gcf(), "bucket_bucket_size_vs_time.jpg");
quit()
