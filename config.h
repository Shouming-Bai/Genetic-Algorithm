#ifndef CONFIG_H
#define CONFIG_H

/********************* include **************************/
#include <stdio.h>
#include <stdlib.h>

/********************* define ***************************/

typedef unsigned char           uint8;
typedef unsigned short int      uint16;
typedef unsigned long int       uint32;
typedef unsigned long long int  uint64;

#define X1_Lower_Bound  -5.0
#define X1_Upper_Bound   5.0
#define X2_Lower_Bound  -5.0
#define X2_Upper_Bound   5.0

#define POPULATION      20
#define CODE_LENGTH     17                              // CODE_LENGTH <= 32
#define CODE_MASK       ((unsigned long int)0x1FFFF)
#define CROSSOVER_RATE  0.8
#define MUTATION_RATE   0.01
#define MAX_GENERATIONS 500

/********************** functions ***********************/
double f_2_parameter(double x1, double x2);
double decode_x1(uint32 code);
double decode_x2(uint32 code);
uint64* generate_group(void);
void free_group(uint64* chrom);
double evalate(uint64 chrom);



#endif /*CONFIG_H*/
