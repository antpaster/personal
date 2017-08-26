#ifndef TRIANGLE_H
#define TRIANGLE_H

typedef struct STriangle {
    void *_privateTriangle;

    double ( *_getSideA)( struct STriangle*);
    void ( *_setSideA)( struct STriangle*, double);

    double ( *_getSumAngle) ( struct STriangle*);
} TTriangle;

TTriangle* newTriangle( );
void deleteTriangle( TTriangle*);

double doTriangle( TTriangle *pTr);

#define doSomething( X) _Generic( ( X), \
    TTriangle* : doTriangle \
) (X)

#endif // TRIANGLE_H

