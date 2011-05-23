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

uint[] bucket_sort(uint[] unsorted_data, immutable uint num_buckets, immutable uint threads)
{
    immutable auto interval = (minPos!("a > b")(unsorted_data)[0]/num_buckets)+1;
    auto buckets = new uint[][num_buckets];

    foreach(uint datum; unsorted_data)
    {
        scope(failure) { writefln("%d %d %d", datum, interval, num_buckets);}
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

double stddev(in double[] a)
{
    auto r = reduce!("a + b", "a + b * b")(tuple(0.0, 0.0), a);
    auto avg = r[0] / a.length;
    auto stdev = sqrt(r[1] / a.length - avg * avg);
    return stdev;
}

int main(string[] argv)
{
    enforce(argv.length == 5, "Usage: ./main <filename> <threads> <buckets> <output_file>");
    Stream f = new BufferedFile(argv[1]);
    OutputStream g = new BufferedFile(argv[4], FileMode.Append);
    scope(exit) { g.close();}
    
    auto threads = to!(uint)(argv[2]);
    auto buckets = to!(uint)(argv[3]);
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
        sort_data = bucket_sort(sort_data, buckets, threads);
        sw.stop();
        times ~= (sw.peek()-last).msecs;
        last = sw.peek();
        enforce(isSorted(sort_data));
    }
    
    g.writef("%d %d %f %f %f %f\n", buckets, threads, avg(times), minPos!("a > b")(times)[0], minPos(times)[0], stddev(times));//Buckets, threads, avg time, max time, min time
    g.flush();
    
    return 0;
}


