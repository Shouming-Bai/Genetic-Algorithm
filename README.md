<h1 align = "center">遗传算法的编程实现</h1>

# 实验内容

编写遗传算法(GA)程序。熟练掌握GA算法的总体架构，掌握选择、交叉、变异等算子的程序编写，掌握轮盘赌等概率参数的程序编写。

自选一个GA算法的应用场景，进行程序编写和结果输出，并撰写实验报告。

# 实验报告

## Application Scene

Problems which appear to be particularly appropriate for solution by genetic algorithms include timetabling and scheduling problems, and many scheduling software packages are based on GAs[citation needed]. GAs have also been applied to engineering. Genetic algorithms are often applied as an approach to solve global optimization problems.

As a general rule of thumb genetic algorithms might be useful in problem domains that have a complex fitness landscape as mixing, i.e., mutation in combination with crossover, is designed to move the population away from local optima that a traditional hill climbing algorithm might get stuck in. Observe that commonly used crossover operators cannot change any uniform population. Mutation alone can provide ergodicity of the overall genetic algorithm process (seen as a Markov chain).

Examples of problems solved by genetic algorithms include: mirrors designed to funnel sunlight to a solar collector, antennae designed to pick up radio signals in space,[28] walking methods for computer figures,  optimal design of aerodynamic bodies in complex flow fields.

## Architecture

<img src=".\2020-10-25 211159.jpg" width = "70%"   height = "70%"  alt="图片名称" align=center />

The simulated annealing algorithm, a version of stochastic hill climbing where some downhill moves are allowed. Downhill moves are accepted readily early in the annealing schedule and then less often as time goes on. The schedule input determines the value of the temperature T as a function of time.

```c
#define POPULATION      6
#define CODE_LENGTH     17         // CODE_LENGTH <= 32
#define CODE_MASK       ((unsigned long int)0x1FFFF)
#define CROSSOVER_RATE  0.8
#define MUTATION_RATE   0.1
#define MAX_GENERATIONS 500
```

```c
double GA(void){
    /****** initialize the group ******/
    /*********** iteration ***********/
        // evaluate fitness
        // save the Elite
    		if( found ){
                printf("...");
            }
        // selection
        // crossover
        // mutation
    }
	if( !found )
        printf("...");
    return 0;
}
```

## Result

1. **Before changing the parameters**

   result:

```
No.1 chrom= 0000f966 000070d1, fitness= 0.113158
...
No.134 chrom= 0000fdfe 00010000, fitness= 0.998467		//best
...
No.333 chrom= 000127ed 00010002, fitness= 0.621830

Found it! It was in 134th generationNot Found!
```

2. **change the parameter:** `#define POPULATION      20`

```
No.1 chrom= 00012508 00013d62, fitness= 0.337768
No.2 chrom= 0000d885 0000a5ed, fitness= 0.213244
No.3 chrom= 0000d885 00010080, fitness= 0.627098
...
No.44 chrom= 0000bf30 0000bed9, fitness= 0.236880
No.45 chrom= 00009d1a 0000a7eb, fitness= 0.130030
No.46 chrom= 00010010 00010020, fitness= 0.999992	// best
No.47 chrom= 00011bb0 0000ea7f, fitness= 0.680805
No.48 chrom= 00011b31 0000fa5f, fitness= 0.772695
...
No.245 chrom= 0000ea90 000169ce, fitness= 0.183624

Found it! It was in 46th generationNot Found!
```

3. **change the parameter:** `#define MUTATION_RATE   0.01`

   ```
   No.1 chrom= 00012508 00013d62, fitness= 0.337768
   No.2 chrom= 00005084 0000ade9, fitness= 0.065284
   No.3 chrom= 0000d084 0000ade9, fitness= 0.225703
   ...
   No.119 chrom= 0000bc94 000075ab, fitness= 0.099665
   No.120 chrom= 0000bc94 000065ab, fitness= 0.084603
   No.121 chrom= 0000fc94 00010000, fitness= 0.995558		//best
   No.122 chrom= 0000bc94 00008000, fitness= 0.111310
   ...
   No.319 chrom= 0000efac 0000a804, fitness= 0.246631
   No.320 chrom= 0000efac 0000a844, fitness= 0.247654
   
   Found it! It was in 121th generationNot Found!
   Process returned 0 (0x0)   execution time : 0.528 s
   Press any key to continue.
   
   ```

