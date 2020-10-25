#include "ga.h"

typedef struct __fitness    Fitness;
struct __fitness{
    double eval;
    double lower;
    double upper;
    uint8 n_dart;
};

uint32 dead_stack[100];    // 100 < POPULATION
int top;

void evaluate_fitness(uint64* chrom, Fitness* fitness, uint64* winner_chrom, double* winner_fitness)
{
    uint32 i;
    uint64 sum_fitness = 0;
    *winner_chrom = 0;
    *winner_fitness = 0;

    // evaluate fitness
    for(i=0; i<POPULATION; i++)
    {
        fitness[i].eval = evalate(chrom[i]);
        sum_fitness += fitness[i].eval;

        if(fitness[i].eval > *winner_fitness ){
            *winner_fitness = fitness[i].eval;
            *winner_chrom = chrom[i];
        }

        fitness[i].n_dart = 0;
    }
    // prepare roulette wheel:
    fitness[0].eval = fitness[0].eval / sum_fitness;
    fitness[0].lower = 0;
    fitness[0].upper = fitness[0].eval;
    for(i=1; i<POPULATION; i++)
    {
        fitness[i].eval = fitness[i].eval / sum_fitness;
        fitness[i].lower = fitness[i-1].upper;
        fitness[i].upper = fitness[i].lower + fitness[i].eval;
    }
    fitness[POPULATION-1].upper = 1;
}

void select(uint64* chrom, Fitness* fitness)
{
    uint32 i, left, mid, right;
    double dart;
    top = -1;
    // throw darts:
    for(i=0; i<POPULATION; i++)
    {
        dart = (double)rand() / RAND_MAX;
        left = 0;
        right = POPULATION - 1;
        mid = (left+right) >>2;
        while( 1 )  // mark the region where the dart got
        {
            if( dart >= fitness[mid].upper ){
                left = mid + 1;
            }else if( dart < fitness[mid].lower ){
                right = mid - 1;
            }else{
                fitness[mid].n_dart ++;
                break;
            }
            mid = (left+right) >>2;
        }
    }
    // eliminate losers, push loser into dead_stack:
    for(i=0; i<POPULATION; i++)
    {
        if( fitness[i].n_dart == 0 )
            dead_stack[++top] = i;
    }
    // copy winner to vacant position
    for(i=0; i<POPULATION; i++)
    {
        while(fitness[i].n_dart > 1 ){
            chrom[dead_stack[top--]] = chrom[i];
            fitness[i].n_dart --;
        }
    }
}

void crossover(uint64* chrom)
{
    uint32 i, site;
    uint64 tmp, mask;
    for( i=0; i<POPULATION; i+=2)
    {
        if( (double)rand()/RAND_MAX < CROSSOVER_RATE )
        {
            // determine the Cross site
            site = rand() % (CODE_LENGTH * 2 - 1);
            site = site - CODE_LENGTH + 32;
            mask = ((uint64)0x01 << site) - 1;

            // save chrom[i]_low_bits into tmp :
            tmp = chrom[i] & mask;

            // move chrom[i+1]_low_bits into chrom[i]_low_bits
            chrom[i] &= ~mask;
            chrom[i] |= chrom[i+1] & mask;

            // move tmp into chrom[i+1]_low_bits
            chrom[i+1] &= ~mask;
            chrom[i] |= tmp;
        }
    }
}

void mutate(uint64* chrom)
{
    uint32 i, site;
    static uint64 threshold = (double)RAND_MAX * MUTATION_RATE;

    for(i=0; i<POPULATION; i++)
    {
        for(site=0; site<CODE_LENGTH; site++)
        {
            if( rand() <= threshold )
                chrom[i] ^= (uint64)0x01 << site;
        }
        for(site=32; site<32+CODE_LENGTH; site++)
        {
            if( rand() <= threshold )
                chrom[i] ^= (uint64)0x01 << site;
        }
    }
}

double GA(void)
{
    uint32 No_Generation=0, n_consecutive_times=0;
    uint64 new_winner_chrom, real_winner_chrom;
    double new_winner_fitness=0, real_winner_fitness=0;
    Fitness* fitness = (Fitness*) malloc( sizeof(Fitness)*POPULATION );

    /*********** initialize the group ***********/
    uint64* chrom = generate_group();

    /*********** iteration ***********/
    while(No_Generation++ < MAX_GENERATIONS)
    {
        // evaluate fitness
        evaluate_fitness(chrom, fitness, &new_winner_chrom, &new_winner_fitness);
        // save the Elite
        if( new_winner_fitness > real_winner_fitness)
        {
            n_consecutive_times = 0;
            real_winner_fitness = new_winner_fitness;
            real_winner_chrom = new_winner_chrom;
        }
        else
        {
            n_consecutive_times ++;
            if(n_consecutive_times >= 200 )
            {
                printf("\nFound it! It was in %luth generation", No_Generation-200);
                break;
            }
        }
        printf("No.%lu chrom= %08lx %08lx, fitness= %f\n", No_Generation, \
               (uint32)(new_winner_chrom>>32), (uint32)new_winner_chrom, new_winner_fitness);

        // selection
        select(chrom, fitness);

        // crossover
        crossover(chrom);

        // mutation
        mutate(chrom);
    }

    free(fitness);
    free_group(chrom);

    printf("Not Found!");
    return 0;
}






