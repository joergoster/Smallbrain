#include "scores.h"
#include "types.h"

#include <cmath>

int piece_values[2][6] = { { 98, 337, 365, 477, 1025, 0}, { 114, 281, 297, 512,  936, 0} };

int killerscore1 = 900000;
int killerscore2 = 800000;

int reductions[256][120];

// Initialize reduction table
void init_reductions() {
    for (int moves = 0; moves < 256; moves++){
        for (int depth = 0; depth < MAX_PLY; depth++){
            reductions[moves][depth] = 1 + log(moves) * log(depth)  / 1.75;
        }
    }    
}