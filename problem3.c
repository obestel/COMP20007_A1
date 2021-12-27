/*
problem3.c

Driver function for Problem 3.

Skeleton written by Grady Fitzpatrick for COMP20007 Assignment 1 2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <limits.h>

/* Constants */
#define OLDCHIP 0
#define NEWCHIP 1
#define MAXNUMERATOR 100
#define MAXDENOMINATOR 100

/* Used to store all the statistics for a single chip. */
struct statistics;

/* Used to store all the statistics for both chips for each problem. */
struct chipStatistics;

struct statistics {
  int operations;
  int instances;
  int minOperations;
  double avgOperations;
  int maxOperations;
};

struct chipStatistics {
  struct statistics oldChipEuclid;
  struct statistics newChipEuclid;
  struct statistics oldChipSieve;
  struct statistics newChipSieve;
};

/* Set all statistics to 0s */
void initialiseStatistics(struct statistics *stats);

/* Collects the minimum, average and maximum operations from running all
combinations of numerators from 1 to the given maxNumerator and 1 to the given
maxDenominator. */
void collectStatistics(struct chipStatistics *chipStats, int maxNumerator,
  int maxDenominator);

/* Divides the number of operations by the number of instances. */
void calculateAverage(struct statistics *stats);

/* Prints out the minimum, average and maximum operations from given
statistics. */
void printStatistics(struct statistics *stats);

/* Calculates the number of operations required for Euclid's algorithm given the
numerator and denominator when running on the given chip type (one of OLDCHIP
and NEWCHIP) by moving through the steps of the algorithm and counting each
pseudocode operation. */
void euclid(int numerator, int denominator, int chip, struct statistics *s);

/* Calculates the number of operations required for the sieve of Eratosthenes
given the numerator and denominator when running on the given chip type (one of
OLDCHIP and NEWCHIP) by moving through the steps of the algorithm and counting
each pseudocode operation. */
void eratosthenes(int numerator, int denominator, int chip,
  struct statistics *s);

int main(int argc, char **argv){
  struct chipStatistics summaryStatistics;

  collectStatistics(&summaryStatistics, MAXNUMERATOR, MAXDENOMINATOR);

  printf("Old chip (Euclid):\n");
  printStatistics(&(summaryStatistics.oldChipEuclid));
  printf("\n");
  printf("New chip (Euclid)\n");
  printStatistics(&(summaryStatistics.newChipEuclid));
  printf("\n");
  printf("Old chip (Sieve)\n");
  printStatistics(&(summaryStatistics.oldChipSieve));
  printf("\n");
  printf("New chip (Sieve)\n");
  printStatistics(&(summaryStatistics.newChipSieve));
  printf("\n");

  return 0;
}

void collectStatistics(struct chipStatistics *chipStats, int maxNumerator,
  int maxDenominator){
  int numerator, denominator;
  /* Initialise all statistics */
  initialiseStatistics(&(chipStats->oldChipEuclid));
  initialiseStatistics(&(chipStats->newChipEuclid));
  initialiseStatistics(&(chipStats->oldChipSieve));
  initialiseStatistics(&(chipStats->newChipSieve));

  for(numerator = 1; numerator <= maxNumerator; numerator++){
    for(denominator = 1; denominator <= maxDenominator; denominator++){
      /* Run algorithms for all combinations of numerator and denominator. */
      euclid(numerator, denominator, OLDCHIP,
        &(chipStats->oldChipEuclid));
      euclid(numerator, denominator, NEWCHIP,
        &(chipStats->newChipEuclid));
      eratosthenes(numerator, denominator, OLDCHIP,
        &(chipStats->oldChipSieve));
      eratosthenes(numerator, denominator, NEWCHIP,
        &(chipStats->newChipSieve));
    }
  }
  calculateAverage(&(chipStats->oldChipEuclid));
  calculateAverage(&(chipStats->newChipEuclid));
  calculateAverage(&(chipStats->oldChipSieve));
  calculateAverage(&(chipStats->newChipSieve));
}

void calculateAverage(struct statistics *stats){
  stats->avgOperations = (double) stats->operations / stats->instances;
}

void initialiseStatistics(struct statistics *stats){
  stats->operations = 0;
  stats->instances = 10000;
  stats->minOperations = INT_MAX;
  stats->avgOperations = 0;
  stats->maxOperations = 0;
}




void euclid(int numerator, int denominator, int chip, struct statistics *s){
  /* IMPLEMENT THIS */
  int a,b ,t, num_a, den_a;
  int num_operations = 0;
  a = denominator;
  b = numerator;
  num_operations +=2 ;
  

  while(b!= 0){
    t = b ;
    b = a%b ;
    a = t ;
    num_operations +=8  ;
    
  }
  num_a = numerator/a;
  den_a = denominator/a;

  num_operations += 12 ;
  

  s->operations += num_operations ;


 if(num_operations> s->maxOperations){
        s->maxOperations = num_operations;
      }

 if(num_operations< s->minOperations){
        s->minOperations = num_operations;
      }
}





void eratosthenes(int numerator, int denominator, int chip,
  struct statistics *s){
  /* IMPLEMENT THIS*/

  int num, den , num_candidates,i, j;
  int count = 0 ;
  int num_operations = 0  ;
  
  num = numerator ;
  den = denominator ;
  if (num >den){
    num_candidates = den ;
  } else {
    num_candidates = num ;
  }
  int primes [num_candidates-1];
  for(i = 0; i<num_candidates; i++){
    primes[i] = 1;
  }
  i = 1;
  num_operations +=5 ;


  num_operations +=num_candidates ;
  while(i<num_candidates){
    count = 0;
    i +=1 ;
    num_operations +=1 ;

    num_operations +=1;
    if(primes[i]){

      
      j = i+i ;

      num_operations +=1 ;
      num_operations += (num_candidates/i - 1);
      while (j<num_candidates){
        if(j/i >1 && j%i ==0){
          primes[j] = 0 ;
          j = j + i ;
          
        }
      }
      if(chip ==0){
        num_operations +=11 ;}
      else { num_operations += 1;}

       ;
      while(num%i ==0 && den%i ==0){
        num = num/i ;
        den = den/i ;
        num_operations +=12;
        count += 1 ;
      }
      num_operations += (count*11) ;
    }
    
  }
  s->operations += num_operations ;

  if(num_operations> s->maxOperations){
     s->maxOperations = num_operations;
  }

  if(num_operations< s->minOperations){
    s->minOperations = num_operations;
  }
  }



void printStatistics(struct statistics *stats){
  printf("Minimum operations: %d\n", stats->minOperations);
  printf("Average operations: %f\n", stats->avgOperations);
  printf("Maximum operations: %d\n", stats->maxOperations);
}

