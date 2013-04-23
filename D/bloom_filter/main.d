/**
 * Brief: Implementation for Bloom Filter 
 * Authors: Jeremy Wright <jeremy@codestrokes.com>
 * License: Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */    
import Bloom;
import std.stdio;
import std.exception;
uint sax_hash(string key)
{
    uint h;
    foreach(ubyte b; key)
    {
        h^=(h<<5)+(h>>2)+b;
    }
    return h;
}

uint sdbm_hash(string key)
{
    uint h;
    foreach(ubyte b; key)
    {
        h= b + (h<<6) + (h<<16) - h;
    }
    return h;
}


int main(string[] args)
{
    Bloom b1 = new Bloom(5, &sax_hash, &sdbm_hash);
    b1.add("ford");
    debug b1.what();
    enforce(b1.query("ford"));
    enforce(!b1.query("chevy"));
    return 0;
}

