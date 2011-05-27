/**
 * Brief: Bucket Sort in D 
 * Authors: Jeremy Wright <jeremy@codestrokes.com>
 * License: Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */    
import std.typecons;
import std.stdio;
import std.algorithm;
import std.stream;
import std.exception;
import std.conv;
import std.math;
import std.array;
import std.datetime;
import std.numeric;
import std.container;
import std.parallelism;

uint[] bucket_sort(uint[] unsorted_data, immutable uint num_buckets)
{
    immutable auto interval = (minPos!("a > b")(unsorted_data)[0]/num_buckets)+1;
    auto buckets = new uint[][num_buckets];

    foreach(uint datum; unsorted_data)
    {
        scope(failure) { writefln("%d %d %d", datum, interval, num_buckets);}
        buckets[datum/(interval)] ~= datum;
    }

    uint[] s;
    version(MultiThreaded)
    {
        foreach(ref bucket; taskPool.parallel(buckets))
        {
            bucket.sort;
        }

    }
    else 
    {
        foreach(uint[] bucket; buckets)
        {
            bucket.sort;
        }
    }
    
    foreach(uint[] bucket; buckets)
    {
        s ~= bucket;
    }
    return s;
}

int main(string[] argv)
{
    enforce(argv.length == 4, "Usage: ./main <filename> <buckets> <output_file>");
    Stream f = new BufferedFile(argv[1]);
    OutputStream g = new BufferedFile(argv[3], FileMode.Append);
    scope(exit) { g.close();}
    
    auto buckets = to!(uint)(argv[2]);
    uint[] sort_data;
    uint temp_uint;
    while(f.readf(&temp_uint))
    {
        sort_data ~= temp_uint;
    }
    f.close();

    StopWatch sw;
    double[] times;
    TickDuration last = TickDuration.from!"seconds"(0);
    foreach(unused; 0..10)
    {
        sw.start();
        sort_data = bucket_sort(sort_data, buckets);
        sw.stop();
        times ~= (sw.peek()-last).msecs;
        last = sw.peek();
        enforce(isSorted(sort_data));
    }
    
    g.writef("%d ", buckets);//Bucket
    foreach(time; times)
    {
        g.writef("%f ", time);
    }
    g.writef("\n");
    g.flush();
    
    return 0;
}


