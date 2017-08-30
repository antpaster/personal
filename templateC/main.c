#include <stdio.h>

#include "templates.h"

int main( ) {
    int ai[ 3] = { 0, 2, 3};
    int bi[ 3] = { 0, 5, 6};
    int iRes[ 3];

    float af[ 3] = { 1.0, 2.0, 3.0};
    float bf[ 3] = { 0.0, 2.5, 3.5};
    float fRes[ 3];

    int i;
    for( i = 0; i < 3; ++i) {
        printf( "ai[ %d] = %d\n", i, ai[ i]);
    }

    printf( "\n");
    for( i = 0; i < 3; ++i) {
        printf( "af[ %d] = %f\n", i, af[ i]);
    }
    printf( "\n");

//    TEMPLATE( add, int)( iRes, ai, bi, 3);
//    TEMPLATE( add, float)( fRes, af, bf, 3);

//    TEMPLATE( subtract, int)( iRes, ai, bi, 3);
//    TEMPLATE( subtract, float)( fRes, af, bf, 3);

//    TEMPLATE( multiply, int)( iRes, ai, bi, 3);
//    TEMPLATE( multiply, float)( fRes, af, bf, 3);

    TEMPLATE( divide, int)( iRes, ai, bi, 3);
    TEMPLATE( divide, float)( fRes, af, bf, 3);

    for( i = 0; i < 3; ++i) {
        printf( "ai[ %d] = %d\n", i, iRes[ i]);
    }

    printf( "\n");
    for( i = 0; i < 3; ++i) {
        printf( "af[ %d] = %f\n", i, fRes[ i]);
    }

    double d1 = 5.0, d2 = 3.0, dRes;

    TEMPLATE( divide, double)( &dRes, &d1, &d2, 1);

    printf( "\nDivision of two double variables: %f\n", dRes);

    return 0;
}
