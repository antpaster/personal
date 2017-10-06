#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "templates.h"

int main( ) {
    int ai[ 3] = { 0, 4, 3};
    int bi[ 3] = { 0, 5, 6};
    int iRes[ 3];
    int iMin = 5;

    float af[ 3] = { 1.0, 2.0, 3.0};
    float bf[ 3] = { 1.0, 2.5, 3.5};
    float fRes[ 3];
    float fMax;

    double dA[ 3] = { 2.0, -1.0, 6.5};
    double dB[ 3] = { -5.0, 1.3, 0.2};
    double dRes[ 3];
    double dMax = 0.0;

    size_t i, j;

    /*! Echoprint of the default data *************************************************************/
    printf( "Echoprint\n1st integer array\n");
    for( i = 0; i < 3; ++i) {
        printf( "ai[ %u] = %d\n", i, *( ai + i));
    }
    printf( "\n2nd integer array\n");
    for( i = 0; i < 3; ++i) {
        printf( "bi[ %u] = %d\n", i, *( bi + i));
    }
    printf( "\n1st float array\n");
    for( i = 0; i < 3; ++i) {
        printf( "af[ %u] = %f\n", i, *( af + i));
    }
    printf( "\n2nd float array\n");
    for( i = 0; i < 3; ++i) {
        printf( "bf[ %u] = %f\n", i, *( bf + i));
    }
    printf( "\n1st double array\n");
    for( i = 0; i < 3; ++i) {
        printf( "dA[ %u] = %f\n", i, *( dA + i));
    }
    printf( "\n2nd double array\n");
    for( i = 0; i < 3; ++i) {
        printf( "dB[ %u] = %f\n", i, *( dB + i));
    }


    /*! Min - max template testing ****************************************************************/
    /* Minimum value calc from the int array testing - ok */
    TEMPLATE( min_max, int)( &iMin, bi, 3, 0);
    printf( "\nMin int from bi = %d\n", iMin);
    /* Maximum value calc from the float array testing - ok */
    TEMPLATE( min_max, float)( &fMax, af, 3, 1);
    printf( "\nMax float from af = %f\n", fMax);
    /* Maximum value calc from the double array testing - ok */
    TEMPLATE( min_max, double)( &dMax, dA, 3, 1);
    printf( "\nMax double form dA = %f\n", dMax);


    /*! Sum template testing **********************************************************************/
    /* Int array sum testing - ok */
    TEMPLATE( add, int)( iRes, ai, bi, 3);
    printf( "\nInt array sum testing\n");
    for( i = 0; i < 3; ++i) {
        printf( "ai[ %u] + bi[ %u] = %d\n", i, i, *( iRes + i));
    }
    /* Float array sum testing - ok */
    TEMPLATE( add, float)( fRes, af, bf, 3);
    printf( "\nFloat array sum testing\n");
    for( i = 0; i < 3; ++i) {
        printf( "af[ %u] + bf[ %u] = %f\n", i, i, *( fRes + i));
    }
    /* Double array sum testing - ok */
    TEMPLATE( add, double)( dRes, dA, dB, 3);
    printf( "\nDouble array sum testing\n");
    for( i = 0; i < 3; ++i) {
        printf( "dA[ %u] + dB[ %u] = %f\n", i, i, *( dRes + i));
    }


    /*! Subtraction template testing **************************************************************/
    /* Int array subtraction testing - ok */
    TEMPLATE( subtract, int)( iRes, ai, bi, 3);
    printf( "\nInt array subtraction testing\n");
    for( i = 0; i < 3; ++i) {
        printf( "ai[ %u] - bi[ %u] = %d\n", i, i, *( iRes + i));
    }
    /* Float array subtraction testing - ok */
    TEMPLATE( subtract, float)( fRes, af, bf, 3);
    printf( "\nFloat array subtraction testing\n");
    for( i = 0; i < 3; ++i) {
        printf( "af[ %u] - bf[ %u] = %f\n", i, i, *( fRes + i));
    }
    /* Double array subtraction testing - ok */
    TEMPLATE( subtract, double)( dRes, dA, dB, 3);
    printf( "\nDouble array subtraction testing\n");
    for( i = 0; i < 3; ++i) {
        printf( "dA[ %u] - dB[ %u] = %f\n", i, i, *( dRes + i));
    }


    /*! Multiplication template testing ***********************************************************/
    /* Int array multiplication testing - ok */
    TEMPLATE( multiply, int)( iRes, ai, bi, 3);
    printf( "\nInt array multiplication testing\n");
    for( i = 0; i < 3; ++i) {
        printf( "ai[ %u] * bi[ %u] = %d\n", i, i, *( iRes + i));
    }
    /* Float array multiplication testing - ok */
    TEMPLATE( multiply, float)( fRes, af, bf, 3);
    printf( "\nFloat array multiplication testing\n");
    for( i = 0; i < 3; ++i) {
        printf( "af[ %u] * bf[ %u] = %f\n", i, i, *( fRes + i));
    }
    /* Double array multiplication testing - ok */
    TEMPLATE( multiply, double)( dRes, dA, dB, 3);
    printf( "\nDouble array multiplication testing\n");
    for( i = 0; i < 3; ++i) {
        printf( "dA[ %u] * dB[ %u] = %f\n", i, i, *( dRes + i));
    }


    /*! Divivsion template testing ****************************************************************/
    /* Int array division testing - ok */
    TEMPLATE( divide, int)( iRes, ai, bi, 3);
    printf( "\nInt array division testing\n");
    for( i = 0; i < 3; ++i) {
        printf( "ai[ %u] / bi[ %u] = %d\n", i, i, *( iRes + i));
    }
    /* Float array division testing - ok */
    TEMPLATE( divide, float)( fRes, af, bf, 3);
    printf( "\nFloat array division testing\n");
    for( i = 0; i < 3; ++i) {
        printf( "af[ %u] / bf[ %u] = %f\n", i, i, *( fRes + i));
    }
    /* Double array division testing - ok */
    TEMPLATE( divide, double)( dRes, dA, dB, 3);
    printf( "\nDouble array division testing\n");
    for( i = 0; i < 3; ++i) {
        printf( "dA[ %u] / dB[ %u] = %f\n", i, i, *( dRes + i));
    }


    /* Insert sort template testing ***************************************************************/
    /* Int array insert sort testing - ok */
    TEMPLATE( insert_sort, int)( ai, 3, 0);
    printf( "\nInt array insert sort testing\n");
    for( i = 0; i < 3; ++i) {
        printf( "ai[ %u] = %d\n", i, *( ai + i));
    }
    /* Float array insert sort testing - fail, todo */
    TEMPLATE( insert_sort, float)( bf, 3, 0);
    printf( "\nFloat array insert sort testing\n");
    for( i = 0; i < 3; ++i) {
        printf( "bf[ %u] = %d\n", i, *( bf + i));
    }
    /* Double array insert sorting - ok */
    TEMPLATE( insert_sort, double)( dA, 3, 1);
    printf( "\nDouble array insert sort testing\n");
    for( i = 0; i < 3; ++i) {
        printf( "dA[ %u] = %f\n", i, *( dA + i));
    }


    /*! MGC template testing **********************************************************************/
    double unitMatr[ 3][ 3];
    double *currAddr;
    double eulerAngles[ 3] = { M_PI / 6.0, M_PI / 12.0, 0.1 * M_PI};

    /* MGC calc testing - CCS 2 SCS - ok */
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            *currAddr = ( i == j) ? 1.0 : 0.0;
        }
    }
    TEMPLATE( mgc_calc, double)( unitMatr, eulerAngles, CONNECTED_TO_SPEED_CS);
    printf( "\nMGC calc testing - CCS 2 SCS\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            printf( "%f ", i, j, /**currAddr*/unitMatr[ i][ j]);
        }
        printf( "\n");
    }

    /* MGC calc testing - SCS 2 CCS - ok */
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            *currAddr = ( i == j) ? 1.0 : 0.0;
        }
    }
    TEMPLATE( mgc_calc, double)( unitMatr, eulerAngles, SPEED_TO_CONNECTED_CS);
    printf( "\nMGC calc testing - SCS 2 CCS\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            printf( "%f ", i, j, /**currAddr*/unitMatr[ i][ j]);
        }
        printf( "\n");
    }

    /* MGC calc testing - HCS 2 NCS - ok */
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            *currAddr = ( i == j) ? 1.0 : 0.0;
        }
    }
    TEMPLATE( mgc_calc, double)( unitMatr, eulerAngles, HORIZONTED_TO_NORMAL_CS);
    printf( "\nMGC calc testing - HCS 2 NCS\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            printf( "%f ", i, j, /**currAddr*/unitMatr[ i][ j]);
        }
        printf( "\n");
    }

    /* MGC calc testing - NCS 2 HCS - ok */
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            *currAddr = ( i == j) ? 1.0 : 0.0;
        }
    }
    TEMPLATE( mgc_calc, double)( unitMatr, eulerAngles, NORMAL_TO_HORIZONTED_CS);
    printf( "\nMGC calc testing - NCS 2 HCS\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            printf( "%f ", i, j, /**currAddr*/unitMatr[ i][ j]);
        }
        printf( "\n");
    }

    /* MGC calc testing - NCS 2 CCS - ok */
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            *currAddr = ( i == j) ? 1.0 : 0.0;
        }
    }
    TEMPLATE( mgc_calc, double)( unitMatr, eulerAngles, NORMAL_TO_CONNECTED_CS);
    printf( "\nMGC calc testing - NCS 2 CCS\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            printf( "%f ", i, j, /**currAddr*/unitMatr[ i][ j]);
        }
        printf( "\n");
    }

    /* MGC calc testing - CCS 2 NCS - ok */
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            *currAddr = ( i == j) ? 1.0 : 0.0;
        }
    }
    TEMPLATE( mgc_calc, double)( unitMatr, eulerAngles, CONNECTED_TO_NORMAL_CS);
    printf( "\nMGC calc testing - CCS 2 NCS\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            printf( "%f ", i, j, /**currAddr*/unitMatr[ i][ j]);
        }
        printf( "\n");
    }

    /* MGC calc testing - TCS 2 CCS - ok */
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            *currAddr = ( i == j) ? 1.0 : 0.0;
        }
    }
    TEMPLATE( mgc_calc, double)( unitMatr, eulerAngles, TRAJECTORY_TO_CONNECTED_CS);
    printf( "\nMGC calc testing - TCS 2 CCS\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            printf( "%f ", i, j, /**currAddr*/unitMatr[ i][ j]);
        }
        printf( "\n");
    }

    /* MGC calc testing - CCS 2 TCS - ok */
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            *currAddr = ( i == j) ? 1.0 : 0.0;
        }
    }
    TEMPLATE( mgc_calc, double)( unitMatr, eulerAngles, CONNECTED_TO_TRAJECTORY_CS);
    printf( "\nMGC calc testing - CCS 2 TCS\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            printf( "%f ", i, j, /**currAddr*/unitMatr[ i][ j]);
        }
        printf( "\n");
    }

    /* MGC calc testing - CCS 2 BCSZY - ok */
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            *currAddr = ( i == j) ? 1.0 : 0.0;
        }
    }
    TEMPLATE( mgc_calc, double)( unitMatr, eulerAngles, CONNECTED_TO_BEAM_Z_UP_Y_LEFT_CS);
    printf( "\nMGC calc testing - CCS 2 BCSZY\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            printf( "%f ", i, j, /**currAddr*/unitMatr[ i][ j]);
        }
        printf( "\n");
    }

    /* MGC calc testing - BCSZY 2 CCS - ok */
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            *currAddr = ( i == j) ? 1.0 : 0.0;
        }
    }
    TEMPLATE( mgc_calc, double)( unitMatr, eulerAngles, BEAM_Z_UP_Y_LEFT_TO_CONNECTED_CS);
    printf( "\nMGC calc testing - BCSZY 2 CCS\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            printf( "%f ", i, j, /**currAddr*/unitMatr[ i][ j]);
        }
        printf( "\n");
    }

    /* MGC calc testing - CCS 2 BCSYZ - ok */
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            *currAddr = ( i == j) ? 1.0 : 0.0;
        }
    }
    TEMPLATE( mgc_calc, double)( unitMatr, eulerAngles, CONNECTED_TO_BEAM_Y_LEFT_Z_UP_CS);
    printf( "\nMGC calc testing - CCS 2 BCSYZ\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            printf( "%f ", i, j, /**currAddr*/unitMatr[ i][ j]);
        }
        printf( "\n");
    }

    /* MGC calc testing - BCSYZ 2 CCS - ok */
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            *currAddr = ( i == j) ? 1.0 : 0.0;
        }
    }
    TEMPLATE( mgc_calc, double)( unitMatr, eulerAngles, BEAM_Y_LEFT_Z_UP_TO_CONNECTED_CS);
    printf( "\nMGC calc testing - BCSYZ 2 CCS\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            currAddr = unitMatr + i * j;
            printf( "%f ", i, j, /**currAddr*/unitMatr[ i][ j]);
        }
        printf( "\n");
    }


    /*! Matrix transposing testing ****************************************************************/
    /* Double matrix transposing testing - ok */
    double dMatr[ 3][ 3];

    srand( time( NULL));

    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            dMatr[ i][ j] = ( double)( rand( ) % 50);
        }
    }
    printf( "\nDouble matrix before the transposing\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            printf( "%f ", i, j, dMatr[ i][ j]);
        }
        printf( "\n");
    }
    TEMPLATE( transpose, double)( dMatr, 3, 3);
    printf( "\nDouble matrix after the transposing\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            printf( "%f ", i, j, dMatr[ i][ j]);
        }
        printf( "\n");
    }

    /* Float matrix transposing testing - ok */
    float fMatr[ 3][ 3];

    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            fMatr[ i][ j] = ( float)( rand( ) % 50);
        }
    }
    printf( "\nFloat matrix before the transposing\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            printf( "%f ", i, j, fMatr[ i][ j]);
        }
        printf( "\n");
    }
    TEMPLATE( transpose, float)( fMatr, 3, 3);
    printf( "\nFloat matrix after the transposing\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            printf( "%f ", i, j, fMatr[ i][ j]);
        }
        printf( "\n");
    }

    /*! Matrix multiplication testing *************************************************************/
    /* Double matrix multiplication testing - ok */
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            dMatr[ i][ j] = ( double)( rand( ) % 5);
        }
    }
    printf( "\nDouble matrix-multipicator 1\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            printf( "%f ", i, j, dMatr[ i][ j]);
        }
        printf( "\n");
    }

    double dMatrExtra[ 3][ 3];
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            dMatrExtra[ i][ j] = ( double)( rand( ) % 5);
        }
    }
    printf( "\nDouble matrix-multipicator 2\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            printf( "%f ", i, j, dMatrExtra[ i][ j]);
        }
        printf( "\n");
    }

    double dMatrResult[ 3][ 3];

    TEMPLATE( matr_multiply, double)( dMatrResult, dMatr, dMatrExtra, 3, 3, 3);
    printf( "\nDouble matrix result of the multiplication\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            printf( "%f ", i, j, dMatrResult[ i][ j]);
        }
        printf( "\n");
    }

    /* Float matrix multiplication testing - ok */
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            fMatr[ i][ j] = ( float)( rand( ) % 5);
        }
    }
    printf( "\nFloat matrix-multipicator 1\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            printf( "%f ", i, j, fMatr[ i][ j]);
        }
        printf( "\n");
    }

    float fMatrExtra[ 3][ 3];
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            fMatrExtra[ i][ j] = ( float)( rand( ) % 5);
        }
    }
    printf( "\nFloat matrix-multipicator 2\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            printf( "%f ", i, j, fMatrExtra[ i][ j]);
        }
        printf( "\n");
    }

    float fMatrResult[ 3][ 3];

//    TEMPLATE( matr_multiply, float)( fMatrResult, fMatr, fMatrExtra, 3, 3, 3);
    printf( "\nFloat matrix result of the multiplication\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            printf( "%f ", i, j, fMatrResult[ i][ j]);
        }
        printf( "\n");
    }


    /*! Matrux determinant calculation testing ****************************************************/
    /* Double matrix determinant calculation testing - fail */
    dMatr[ 0][ 0] = 1.0;
    dMatr[ 0][ 1] = 7.0;
    dMatr[ 0][ 2] = 1.0;
    dMatr[ 1][ 0] = 0.0;
    dMatr[ 1][ 1] = -1.0;
    dMatr[ 1][ 2] = 2.0;
    dMatr[ 2][ 0] = -5.0;
    dMatr[ 2][ 1] = 4.0;
    dMatr[ 2][ 2] = 3.0;

//    dMatr[ 0][ 0] = 1.0;
//    dMatr[ 0][ 1] = 0.0;
//    dMatr[ 0][ 2] = 0.0;
//    dMatr[ 1][ 0] = 0.0;
//    dMatr[ 1][ 1] = 1.0;
//    dMatr[ 1][ 2] = 0.0;
//    dMatr[ 2][ 0] = 0.0;
//    dMatr[ 2][ 1] = 0.0;
//    dMatr[ 2][ 2] = 1.0;

//    for( i = 0; i < 3; ++i) {
//        for( j = 0; j < 3; ++j) {
//            dMatr[ i][ j] = ( double)( rand( ) % 5);
//        }
//    }
    printf( "\nDouble matrix for determinant calculation\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            printf( "%f ", i, j, dMatr[ i][ j]);
        }
        printf( "\n");
    }

    double detDmatr;
    TEMPLATE( determine, double)( &detDmatr, dMatr, 3, 3);
    printf( "\nDeterminant value: %f\n", detDmatr);

    /* Float matrix determinant calculation testing - fail */
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            fMatr[ i][ j] = ( float)( rand( ) % 5);
        }
    }

    printf( "\nFloat matrix for determinant calculation\nSource matrix\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            printf( "%f ", i, j, fMatr[ i][ j]);
        }
        printf( "\n");
    }

    float detFmatr;
    TEMPLATE( determine, float)( &detFmatr, fMatr, 3, 3);
    printf( "\nDeterminant value: %f\n", detFmatr);

    /*! Matrix invertion testing ******************************************************************/
    /* Double matrix invertion testing - ok */
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            dMatr[ i][ j] = ( double)( rand( ) % 5);
        }
    }

//    dMatr[ 0][ 0] = 1.0;
//    dMatr[ 0][ 1] = 7.0;
//    dMatr[ 0][ 2] = 1.0;
//    dMatr[ 1][ 0] = 0.0;
//    dMatr[ 1][ 1] = -1.0;
//    dMatr[ 1][ 2] = 2.0;
//    dMatr[ 2][ 0] = -5.0;
//    dMatr[ 2][ 1] = 4.0;
//    dMatr[ 2][ 2] = 3.0;

    printf( "\nDouble matrix for invertion\nStraight matrix\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            printf( "%f ", i, j, dMatr[ i][ j]);
        }
        printf( "\n");
    }

    TEMPLATE( inverse, double)( dMatrResult, dMatr, 3);
    printf( "\nDouble matrix result of the invertion\nInverted matrix\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            printf( "%f ", i, j, dMatrResult[ i][ j]);
        }
        printf( "\n");
    }

    TEMPLATE( matr_multiply, double)( dMatrExtra, dMatr, dMatrResult, 3, 3, 3);
    printf( "\nResult of the multiplication of straight and inverted matrixes\nSupposed unit "
        "matrix\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            printf( "%f ", i, j, dMatrExtra[ i][ j]);
        }
        printf( "\n");
    }

    /* Float matrix invertion testing - fail */
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            fMatr[ i][ j] = ( float)( rand( ) % 5);
        }
    }
    printf( "\nFloat matrix for invertion\nStraight matrix\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            printf( "%f ", i, j, fMatr[ i][ j]);
        }
        printf( "\n");
    }

    TEMPLATE( inverse, float)( fMatrResult, fMatr, 3);
    printf( "\nFloat matrix result of the invertion\nInverted matrix\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            printf( "%f ", i, j, fMatrResult[ i][ j]);
        }
        printf( "\n");
    }

//    TEMPLATE( matr_multiply, float)( fMatrExtra, fMatr, fMatrResult, 3, 3, 3);
    printf( "\nResult of the multiplication of straight and inverted matrixes\nSupposed unit "
        "matrix\n");
    for( i = 0; i < 3; ++i) {
        for( j = 0; j < 3; ++j) {
            printf( "%f ", i, j, fMatrExtra[ i][ j]);
        }
        printf( "\n");
    }

    return 0;
}
