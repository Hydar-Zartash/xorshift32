#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "xorshift.h"

uint32_t xorshift32(uint32_t state[]){
    uint32_t x =state[0];
    x ^= x << 23; x ^= x >> 7; x ^= x << 5; //alternating xorshifts of prime values
    state[0] = x; //reset initial state for next iteration
    return x;
}

uint32_t rangen(int mini, int maxi){
    uint32_t state[1] = {maxi};
    time_t seconds; //get curent time to substitute environmental randomness. 
    time(&seconds); //set seconds variable to the the seconds since 01/01/1970 
    int gens = seconds%100; //number of generations will be between 1 and a thousand for speed
    uint32_t generations[gens]; //stor generations in uint32 array
    for (int i = 0; i < gens; i++){
        generations[i] = xorshift32(state); //add random value to the list for every generation
    }
    return (generations[gens-1]%(maxi-mini) + mini); //mod last value by max - min then add min to ensure the value lies in specified range
}



