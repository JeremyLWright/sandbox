outputfile = open("bucket_data.dat", "w")

for threads in range(1,20):
    for bucket_size in range(1,100):
        for time in range(20, 200):
            outputfile.write("%f %f %f\n"%(threads, bucket_size, time))

