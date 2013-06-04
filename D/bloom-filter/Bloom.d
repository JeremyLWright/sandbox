/**
 * Brief: Bloom Filter in D 
 * Authors: Jeremy Wright <jeremy@codestrokes.com>
 * License: Copyright Jeremy Wright (c) 2011
 * Creative Commons Attribution-ShareAlike 3.0 Unported License.
 */    
import std.bitmanip;
import std.exception;
import std.stdio;
class Bloom {
    public:
        this(size_t size, uint function(string)[] hash_fns ...)
        {
            this.hash_functions = hash_fns;
            a.length = size;

        }
        ~this(){ }

        unittest
        {
        }

        invariant()
        {
            assert(hash_functions.length > 0);
        }

        void add(string s)
        {
            foreach(fn; hash_functions)
            {
                a[fn(s)%a.length] = 1;                
            }
        }

        bool query(string s)
        {
            foreach(fn; hash_functions)
            {
                if(!a[fn(s)%a.length])
                    return false;
            }
            return true;
        }
        debug void what()
        {
            foreach(t; a)
                writeln(t);
        }
    protected:
    private:
        BitArray a;
        uint function(string)[] hash_functions;
}
