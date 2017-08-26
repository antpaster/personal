#ifndef VECT3RD_H
#define VECT3RD_H

#include "vect2rd.h"
#include "vect3rd.h"

/*! Vect3Rd
 **************************************************************************************************/
typedef struct SPrivateVect3Rd {
    TPrivateVect2Rd _privateVect2Rd;
    double _zValue;
} TPrivateVect3Rd;

typedef struct SVect3Rd {
    void *_privateVect3Rd;

    double ( *_getXvalue)( struct SVect3Rd*);
    double ( *_getYvalue)( struct SVect3Rd*);
    double ( *_getZvalue)( struct SVect3Rd*);
    uint8_t ( *_getValid)( struct SVect3Rd*);

    void ( *_setVect3Rd)( struct SVect3Rd*, double, double, double, uint8_t);
} TVect3Rd;

TVect3Rd* newVect3Rd( );
void deleteVect3Rd( TVect3Rd*);

int addVect3Rd( TVect3Rd*, TVect3Rd*, TVect3Rd*);
int subtractVect3Rd( TVect3Rd*, TVect3Rd*, TVect3Rd*);
int multiplyVect3Rd( TVect3Rd*, TVect3Rd*, TVect3Rd*);
int divideVect3Rd( TVect3Rd*, TVect3Rd*, TVect3Rd*);

#endif // VECT3RD_H

