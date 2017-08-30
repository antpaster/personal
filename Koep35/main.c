#include <stdio.h>
#include <conio.h>

#include "koep35shadowZone.h"

int main( void)
{
    double y = -150.0 * GrToRad, z = 13.0 * GrToRad;
    char limY = 0, limZ = 0, shadow1deg = 0, shadow5deg = 0;

//    printf( "Enter the azimuth angle, y = ");
//    scanf( "%f", &y);
//    printf( "Enter the elevation angle, z = ");
//    scanf( "%f", &z);

    koep35checkVisionAngles( PLANE_SHAPE_Y_NEG, &y, &z, &limY, &limZ, &shadow1deg, &shadow5deg);
    printf( "PLANE_SHAPE_Y_NEG:\ny = %f, z = %f limY = %i, limZ = %i, shadow1deg = %i,"
        " shadow5deg = %i\n\n", y * RadToGr, z * RadToGr, limY, limZ, shadow1deg, shadow5deg);

//    printf( "Enter the azimuth angle, y = ");
//    scanf( "%f", &y);
//    printf( "Enter the elevation angle, z = ");
//    scanf( "%f", &z);

    y = 10.0 * GrToRad;
    z = 41.0 * GrToRad;
    limY = limZ = shadow1deg = shadow5deg = 0;
    koep35checkVisionAngles( TP4_RVV, &y, &z, &limY, &limZ, &shadow1deg, &shadow5deg);
    printf( "TP4_RVV:\ny = %f, z = %f limY = %i, limZ = %i, shadow1deg = %i,"
        " shadow5deg = %i\n", y * RadToGr, z * RadToGr, limY, limZ, shadow1deg, shadow5deg);

    getch( );
    return 0;
}

