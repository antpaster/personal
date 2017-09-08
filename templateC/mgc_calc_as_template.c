/********************************** ukbo42 *************************************
 ** ОРГАНИЗАЦИЯ:     АО "РПКБ"
 ** СОЗДАН:          08.09.17 г. APasternak
 ** ИЗМЕНЕН:         08.09.17 г. APasternak
 *******************************************************************************
 ** ПЕРЕЧЕНЬ ИЗМЕНЕНИЙ:
 ** 08.09.17 г. APasternak. Суть внесенных изменений
 *******************************************************************************
 */
/*!
 ** \file  mgc_calc_as_template.c
 ** \brief Краткий комментарий к файлу
 **      Реализация шаблона вычисления матрицы направляющих косинусов
 ** Расширенный комментарий к файлу
 */

//#ifdef T
#include <stdlib.h>
#include <math.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

int TEMPLATE( mgc_calc, T) ( T *res, const T *angles, const TmgcTypes mt) {

    if( res && angles) {
        switch( mt) {
        case CONNECTED_TO_SPEED_CS:
            break;

        case SPEED_TO_CONNECTED_CS:
            break;

        case HORIZONTED_TO_NORMAL_CS:
            break;

        case NORMAL_TO_CONNECTED_CS:
            break;

        case HORIZONTED_TO_CONNECTED_CS:
            break;

        case CONNECTED_TO_HORIZONTED_CS:
        {
            double pitchSin = sin( *angles);
            double pitchCos = cos( *angles);
            double rollSin = sin( *( angles + 1));
            double rollCos = cos( *( angles + 1));

            double *currAddr = res;
            *currAddr = pitchCos;
            currAddr = res + 1;
            *currAddr = -pitchSin * rollCos;
            currAddr = res + 2;
            *currAddr = pitchSin * rollSin;

            currAddr = res + 3;
            *currAddr = pitchSin;
            currAddr = res + 4;
            *currAddr = pitchCos * rollCos;
            currAddr = res + 5;
            *currAddr = -pitchCos * rollSin;

            currAddr = res + 6;
            *currAddr = 0.0;
            currAddr = res + 7;
            *currAddr = rollSin;
            currAddr = res + 8;
            *currAddr = rollCos;
        }
            break;

        case TRAJECTORY_TO_CONNECTED_CS:
            break;

        case CONNECTED_TO_TRAJECTORY_CS:
            break;

        case SPEED_TO_CONNECTED_CS:
            break;

        case CONNECTED_TO_SPEED_CS:
            break;

        default:
            return 1;
        }
    }

    return 1;
}

#endif

//#endif

