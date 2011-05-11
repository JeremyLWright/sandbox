#!/usr/bin/dmd -run
/**
 * Version: Something Awesome
 */
import std.stdio;

char flags[8191];
/** 
 * Authors: Jeremy Wright
 * Version: Some
 */
int main()
{   int     i, prime, k, count, iter;
version(D_Coverage) {}
else { writefln("10 iterations"); }
    for (iter = 1; iter <= 10; iter++)
    {	count = 0;
	flags[] = true;
	for (i = 0; i < flags.length; i++)
	{   if (flags[i])
	    {	prime = i + i + 3;
		k = i + prime;
		while (k < flags.length)
		{
		    flags[k] = false;
		    k += prime;
		}
		count += 1;
	    }
	}
    }
    version(D_Coverage) {}
else { writefln("%d primes", count);}
    return 0;
}

