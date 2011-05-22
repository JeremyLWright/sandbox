import std.stdio;
import BucketSort;
import std.stream;
import std.exception;
import std.conv;

int main(string[] argv)
{
    enforce(argv.length == 2);
    Stream f = new BufferedFile(argv[1]);
    int[] sort_data;
    int temp_int;
    while(f.readf(&temp_int))
    {
        sort_data ~= temp_int;
        writefln("%d", temp_int);
    }
    writefln("Length: %d", sort_data.length);
    f.close();

    OutputStream g = new BufferedFile("sorted.out", FileMode.OutNew);
    scope(exit) { g.close();}
    foreach(int i; sort_data)
    {
        g.writeLine(text(i));
    }

    return 0;
}


