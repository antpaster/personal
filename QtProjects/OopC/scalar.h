#ifndef SCALAR_H
#define SCALAR_H

#include <stdint.h>

/*! Scalar
 **************************************************************************************************/
typedef struct SPrivateScalar {
    double _value;
    uint8_t _valid;
} TPrivateScalar;

typedef struct SScalar {
    void *_privateScalar;

    double ( *_getValue)( struct SScalar*);
    uint8_t ( *_getValid)( struct SScalar*);

    void ( *_setScalar)( struct SScalar*, double, uint8_t);
} TScalar;

TScalar* newScalar( );
void deleteScalar( TScalar*);

#endif // SCALAR_H

