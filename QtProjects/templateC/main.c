#include <stdio.h>

#include "all_possible_sums.h"

int main( ) {
    int ai[ 3] = { 0, 2, 3};
    int bi[ 3] = { 0, 5, 6};

    float af[ 3] = { 1.0, 2.0, 3.0};
    float bf[ 3] = { 1.5, 2.5, 3.5};

    int i;
    for( i = 0; i < 3; ++i) {
        printf( "ai[ %d] = %d\n", i, ai[ i]);
    }

    printf( "\n");
    for( i = 0; i < 3; ++i) {
        printf( "af[ %d] = %f\n", i, af[ i]);
    }

    TEMPLATE( sum, int)( 3, ai, bi);
    TEMPLATE( sum, float)( 3, af, bf);

    for( i = 0; i < 3; ++i) {
        printf( "ai[ %d] = %d\n", i, ai[ i]);
    }

    printf( "\n");
    for( i = 0; i < 3; ++i) {
        printf( "af[ %d] = %f\n", i, af[ i]);
    }

    return 0;
}
