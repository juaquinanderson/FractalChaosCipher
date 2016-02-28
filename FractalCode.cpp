/*
 * FractalCode.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: juaquin
 */

#include "FractalCode.h"

#include <climits>
#include <assert.h>
#include <math.h>
#include <iostream>
using namespace std;

unsigned int
FractalCode::bitAcode(unsigned int clearbit)
{
    int cryptbit=0;  // build cryptstream from clearstream

    {
        findfirstroot();

        unsigned long q = projecty(Zy);


        //Encode**** make cryptstream from clearstream
        unsigned int input,output,branch;

        {   unsigned int o1,o2,o3;
            input=(clearbit) & 1;

            o1=q & 1; //from iterated quadratic
            o2=input; //from input
            o3=o1^o2; // from parity

            output=o3; // output
            branch=o2; // branch in path to follow through IIM
            //Encode**** make cryptstream from clearstream
        }
        cryptbit=(output);

        if ((branch) != 0)
        {   //take branch to second root
            Zx=-Zx;
            Zy=-Zy;
        }
    }
    return cryptbit;
};

unsigned int
FractalCode::bitBcode(unsigned int cryptbit)
{
    int clearbit=0;  // build clearstream from cryptstream

    {
        findfirstroot();

        unsigned long q = projecty(Zy);


        //decode**** make clearstream from cryptstream
        unsigned int input,output,branch;

        {   unsigned int o1,o2,o3;

            input=(cryptbit) & 1;

            o1=q & 1; //from iterated quadratic
            o3=input; // from input, is parity that was encoded
            o2=o1^o3; //from input

            output=o2; // output
            branch=o2; // branch in path to follow through IIM
            //decode**** make clearstream from cryptstream
        }
        clearbit=(output);

        if ((branch) != 0)
        {   //take branch to second root
            Zx=-Zx;
            Zy=-Zy;
        }
    }
    return clearbit;
};


unsigned int
FractalCode::Acode(unsigned int clearstream)
{
    int cryptstream=0;  // build cryptstream from clearstream

    for (int Iteration=0; Iteration<32; (Iteration++))
    {

        //Encode**** make cryptstream from clearstream
        unsigned int input,output;
        input=(clearstream>>Iteration) & 1;
        output=bitAcode(input);
        cryptstream+=((output)<<Iteration);

    }
    return cryptstream;
};

unsigned int
FractalCode::Bcode(unsigned int cryptstream)
{
    int clearstream=0;  // build clearstream from cryptstream

    for (int Iteration=0; Iteration<32; (Iteration++))
    {
        //decode**** make clearstream from cryptstream
        unsigned int input,output;

        input=(cryptstream>>Iteration) & 1;
        output=bitBcode(input);
        clearstream+=((output)<<Iteration);

    }
    return clearstream;
};


FractalCode::FractalCode(double cx,double cy)
{
    Cx=cx;
    Cy=cy;

    Zx=Zy=0;

    //initialize Z by repeated encoding digits of pi to find fixed point
    for(int i=0; i<32; i++)Acode(3141592653);

}

FractalCode::~FractalCode()
{
}

