/**
 * Brief: Bucket Sort in D 
 * Authors: Jeremy Wright <jeremy@codestrokes.com>
 * License: Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */    

import std.stdio;
import std.algorithm;
import std.stream;
import std.exception;
import std.conv;
import std.math;
import std.array;
import std.datetime;
import std.numeric;

uint[] bucket_sort(uint[] unsorted_data, immutable uint num_buckets, immutable uint threads)
{
    immutable auto interval = (pow(2,31)/num_buckets)+1;
    uint[][] buckets;
    buckets.length = num_buckets;

    foreach(uint datum; unsorted_data)
    {
        scope(failure) { writefln("%d %d %d", datum, interval, buckets.length);}
        buckets[datum/(interval)] ~= datum;
    }

    uint[] s;
    foreach(uint[] bucket; buckets)
    {
        s ~= bucket.sort;
    }


    return s;
}

// Average numbers in an array
double avg(in double[] a)
{
    if (a.length == 0) return 0;
    FPTemporary!double result = 0;
    foreach (e; a) result += e;
    return result / a.length;
}

int main(string[] argv)
{
    enforce(argv.length == 2, "Usage: ./main <filename>");
    Stream f = new BufferedFile(argv[1]);
    OutputStream g = new BufferedFile("single_threaded.dat", FileMode.OutNew);
    scope(exit) { g.close();}
    
    auto threads = 1;
    auto buckets = 5000;
    uint[] sort_data;
    uint temp_uint;
    while(f.readf(&temp_uint))
    {
        sort_data ~= temp_uint;
    }
    f.close();

    for(int num_buckets = 500; num_buckets < 10000; num_buckets += 500)
    {
        StopWatch sw;
        double[] times;
        TickDuration last = TickDuration.from!"seconds"(0);
        foreach(unused; 0..5)
        {
            sw.start();
            sort_data = bucket_sort(sort_data, num_buckets, threads);
            sw.stop();
            times ~= (sw.peek()-last).msecs;
            last = sw.peek();
            enforce(isSorted(sort_data));
        }

        g.writef("%d %d %f %f %f\n", num_buckets, threads, avg(times), minPos!("a > b")(times)[0], minPos(times)[0]);//Buckets, threads, avg time, max time, min time
        g.flush();
    }
    return 0;
}


