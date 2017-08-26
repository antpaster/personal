#ifndef VECT2RD_H
#define VECT2RD_H

#include <stdint.h>

/*! Vect2Rd
 **************************************************************************************************/
typedef struct SPrivateVect2Rd {
    TPrivateScalar _privateScalar;
    double _yValue;
} TPrivateVect2Rd;

typedef struct SVect2Rd {
    void *_privateVect2Rd;

    double ( *_getXvalue)( struct SVect2Rd*);
    double ( *_getYvalue)( struct SVect2Rd*);
    uint8_t ( *_getValid)( struct SVect2Rd*);

    void ( *_setVect2Rd)( struct SVect2Rd*, double, double, uint8_t);
} TVect2Rd;

TVect2Rd* newVect2Rd( );
void deleteVect2Rd( TVect2Rd*);

#endif // VECT2RD_H

