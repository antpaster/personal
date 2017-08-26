#ifndef MATR3X3_H
#define MATR3X3_H

#include <stdint.h>

/*! Matr3x3
 **************************************************************************************************/
typedef struct SPrivateMatr3x3 {
    double **_matr;
//    double _row1[ 3];
//    double _row2[ 3];
//    double _row3[ 3];
} TPrivateMatr3x3;

typedef struct SMatr3x3 {
    void *_privateMatr3x3;

    double ( *_getValueByIndex)( struct SMatr3x3*, uint8_t, uint8_t);
    void ( *_setMatr3x3)( struct SMatr3x3*, double*, double*, double*);
} TMatr3x3;

TMatr3x3* newMatr3x3( );
void deleteMatr3x3( TMatr3x3*);

int addMatr3x3( TMatr3x3*, TMatr3x3*, TMatr3x3*);
int subtractMatr3x3( TMatr3x3*, TMatr3x3*, TMatr3x3*);
int multiplyMatr3x3( TMatr3x3*, TMatr3x3*, TMatr3x3*);
int divideMatr3x3( TMatr3x3*, TMatr3x3*, TMatr3x3*);
int transposeMatr3x3( TMatr3x3*, TMatr3x3*);

#endif // MATR3X3_H

