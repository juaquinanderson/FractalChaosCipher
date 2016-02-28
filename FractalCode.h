/*
 * FractalCode.h
 *
 *  Created on: Feb 22, 2016
 *      Author: juaquin
 */

#ifndef FRACTALCODE_H_
#define FRACTALCODE_H_

#include <climits>
#include <assert.h>
#include <math.h>

class FractalCode
{
    double Cx,Cy;
    double Zx,Zy;

    /*  gives sign of number */
    inline double sign(double d)
    {
        if (d<0) return(-1.0);
        else return(1.0);
    };

    inline unsigned int projecty(double y)
    // project y onto integer grid
    // this is just some scaling choice for testing,
    // dont know what is the best choice here

    {   unsigned long q;
        const double scale=(32768.0/2.0);
        const double offset=(32768.0);
        //assert(((NewZy*scale)+offset)>0.0);
        q=(y*scale)+offset;  //project to positive integer
        q&=1;  // least significant bit
        return q;
    }

    inline void findfirstroot()
    {
        /* Zn*Zn=Z(n+1)-c */
        Zx=Zx-Cx;
        Zy=Zy-Cy;

        double NewZx, NewZy, r;
        r=sqrt(Zx*Zx+Zy*Zy);
        /* sqrt of complex number algorithm from Peitgen, Jurgens, Saupe: Fractals for the classroom */
        if (Zx>0)
        {
            NewZx=sqrt(0.5*(Zx+r));
            NewZy=Zy/(2*NewZx);
        }
        else /* ZX <= 0 */
        {
            if (Zx<0)
            {
                NewZy=sign(Zy)*sqrt(0.5*(-Zx+r));
                NewZx=Zy/(2*NewZy);
            }
            else /* Zx=0 */
            {
                NewZx=sqrt(0.5*fabs(Zy));
                if (NewZx>0) NewZy=Zy/(2*NewZx);
                else NewZy=0;
            }
        };
        /* end sqrt of complex number algorithm */
        Zx=NewZx;
        Zy=NewZy;
    };

public:
    unsigned int Acode(unsigned int clear);  //Acode is inverse of Bcode
    unsigned int bitAcode(unsigned int clear);  //single bit version
    unsigned int Bcode(unsigned int crypt);  //applying them both consecutively, one after the other gets the original message
    unsigned int bitBcode(unsigned int crypt);  //single bit version

    FractalCode(double cx,double cy);
    virtual ~FractalCode();
};

/*  Example:
    	double Key_r=-0.687,Key_i=-0.312;  //key consists of point near mandelbrot set boundary

    	unsigned int Clear[50],CryptA[50],CryptB[50],DecodedAbyB[50],DecodedBbyA[50];

    	// make random message
    	for (int i=0;i<5;i++)
    		Clear[i]=rand()%1000;

    	// encode message with A
    	{
    		FractalCode Q(Key_r,Key_i);
    		for (int i=0;i<5;i++)
    		   CryptA[i]=Q.Acode(Clear[i]);
    	}

    	// encode message with B
    	{
    		FractalCode Q(Key_r,Key_i);
    		for (int i=0;i<5;i++)
    		   CryptB[i]=Q.Bcode(Clear[i]);
    	}

    	// decode message A with B
    	{
    		FractalCode Q(Key_r,Key_i);
    		for (int i=0;i<5;i++)
    		   DecodedAbyB[i]=Q.Bcode(CryptA[i]);
    	}

    	// decode message B with A
    	{
    		FractalCode Q(Key_r,Key_i);
    		for (int i=0;i<5;i++)
    		   DecodedBbyA[i]=Q.Acode(CryptB[i]);
    	}

    	// print results


    	for (int i=0;i<5;i++)
    		{
    		 cout
    		 <<i
    		 <<")   (Clear="<<Clear[i]
    		 <<")   (CryptA="<<CryptA[i]
    		 <<")   (CryptB="<<CryptB[i]
             <<")   (DecodeAbyB="<<DecodedAbyB[i]
             <<")   (DecodeBbyA="<<DecodedBbyA[i]
             <<")"<<endl;
    		};



 */

#endif /* FRACTALCODE_H_ */
