#include <stdio.h>
#include <conio.h>
#include <stdint.h>

#include "koep35shadowZone.h"

int main( void)
{
    double y = 40.0 * GrToRad, z = 13.0 * GrToRad;
    uint8_t limY = 0, limZ = 0, shadow1deg = 0, shadow5deg = 0;

    ThangPointShadow iHps;
    for( iHps = PLANE_SHAPE_Y_POS; iHps < HANG_POINT_SHADOW_ALL; ++iHps)
    {
        y = 40.0 * GrToRad;
        z = 13.0 * GrToRad;

        koep35checkVisionAngles( iHps, &y, &z, &limY, &limZ, &shadow1deg, &shadow5deg);
        printf( "\n\n%u:\ny = %f, z = %f limY = %i, limZ = %i, shadow1deg = %i,"
            " shadow5deg = %i\n", iHps, y * RadToGr, z * RadToGr, limY, limZ, shadow1deg,
            shadow5deg);
    }

    getch( );
    return 0;
}

