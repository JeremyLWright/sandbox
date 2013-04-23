
#include <iostream>
#include <fstream>
#include <math.h>
#include <sstream>
typedef struct {
    unsigned fraction:23;
    unsigned exp:8;
    unsigned sign:1;
} float_bits;
typedef union {
    float_bits fb;
    unsigned int i;
    float f;
} Number;
/*
   float get_value(float32_t convert)
   {
   current_value = 1.0;
   for(unsigned int i = 0; i < 23; ++i)
   {
   current_value = current_value + (float)((convert.fraction & ~i)>>i);
   }
   unsigned int exp = (convert.exp - 127);
   current_value = current_value << exp;
   if(convert.sign == 1)
   return current_value * -1;
   else
   return current_value;
   }*/
using namespace std;
int main ()
{
    Number n;
    std::cout.precision(8);
    std::cout.setf(ios::scientific,ios::floatfield);
int k = 0;
    n.fb.sign = 0; 
    n.fb.exp = 0;
    n.fb.fraction = 0;

    /* Start at zero and count all values to inf */
    ofstream foutx;
    ofstream fouty;
    ofstream foutz;
    string filenamex = "float_dist_x.dat";
    string filenamey = "float_dist_y.dat";
    string filenamez = "float_dist_z.dat";
    foutx.open(filenamex.c_str());
    fouty.open(filenamey.c_str());
    foutz.open(filenamez.c_str());
    
    /* Iterate through the exponents */
    for(unsigned int j = 0; j < pow(2,8)-1; ++j)
    {
	
	/*foutx << "[";
    fouty << "[";
    foutz << "[";*/
    /* Iterate through the fractions */
    for(unsigned int i = 1; i < pow(2,23)-1; i=i<<1)
    {
	foutx << j << endl;
	fouty << i << endl;
	foutz << n.f << endl;
        n.fb.fraction += i;
    }
        n.fb.exp++;
    }
 /*   foutx << "];";
    fouty << "];";
foutz << "];";
*/
    return 0;
}
