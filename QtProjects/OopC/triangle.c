#include <stdlib.h>
#include "triangle.h"

typedef struct SPrivateTriangle {
    double sideA;
    double sideB;
    double sideC;
} TPrivateTriangle;

typedef struct SPrivatePyramid {
    TPrivateTriangle pt;
    double height;
} TPrivatePyramid;

static double getSideA( TTriangle *pTr) {
    return ( ( TPrivateTriangle*)( pTr->_privateTriangle))->sideA;
}

static void setSideA( TTriangle *pTr, double value) {
    ( ( TPrivateTriangle*)( pTr->_privateTriangle))->sideA = value;
}

TTriangle* newTriangle() {
    TTriangle *pTr;

    pTr = ( TTriangle*)malloc( sizeof( TTriangle));
    pTr->_privateTriangle = malloc( sizeof( TPrivateTriangle));
    pTr->_getSideA = &getSideA;
    pTr->_setSideA = &setSideA;

    return pTr;
}

void deleteTriangle( TTriangle *pTr) {
    free( pTr->_privateTriangle);
    free( pTr);
}
