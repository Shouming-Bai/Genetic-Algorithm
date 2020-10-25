
#include "config.h"

double f_2_parameter(double x1, double x2)
{
    return 1.0/(x1*x1 + x2*x2 + 1);
}

double decode_x1(uint32 code)
{
    double x1;
    x1 = (double)X1_Lower_Bound + (double)code * (double)(X1_Upper_Bound - X1_Lower_Bound)/((1<<CODE_LENGTH) - 1);
    return x1;
}

double decode_x2(uint32 code)
{
    return decode_x1(code);
}

uint64* generate_group(void)
{
    uint64* chrom = (uint64*)malloc(sizeof(uint64) * POPULATION);
    uint32 i;
    uint64 tmp;

    srand(0);
    for (i = 0; i < POPULATION; i++)  // make chrom[i] a random number
    {
        chrom[i] = (uint64)rand();
        if( rand() & 0x1 )
            chrom[i] *= (uint64)rand();
        chrom[i] <<= 32;

        tmp = (uint64)rand();
        if( rand() & 0x1 )
            tmp *= (uint64)rand();
        chrom[i] |= tmp;

        chrom[i] &= ((uint64)CODE_MASK<<32) | (uint64)CODE_MASK;
    }
//    chrom[0] = ((uint64)0x1891 << 32) | 0xAA75;
//    chrom[1] = ((uint64)0x14507 << 32) | 0x1d46f;
//    for (i=0; i< POPULATION; i++)
//    {
//        printf("\nchrom[%d] :", i);
//        printf("\tx1 = %lx, x2 = %lx\n", (uint32)chrom[i], (uint32)(chrom[i]>>32) );
//        printf("\t\tx1 = %f, x2 = %f\n", decode_x1( chrom[i] ), decode_x2( chrom[i]>>32 ) );
//    }
    return chrom;
}

void free_group(uint64* chrom)
{
    free(chrom);
}

double evalate(uint64 chrom)
{
    double x1 = decode_x1((uint32)chrom & CODE_MASK);
    double x2 = decode_x2((uint32) (chrom>>32));

    return f_2_parameter(x1, x2);
}






















