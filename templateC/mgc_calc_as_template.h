/********************************** ukbo42 *************************************
 ** ОРГАНИЗАЦИЯ:     ОАО "РПКБ"
 ** СОЗДАН:          30 августа 2017 г. APasternak
 ** ИЗМЕНЕН:         30 августа 2017 г. APasternak
 *******************************************************************************
 ** ПЕРЕЧЕНЬ ИЗМЕНЕНИЙ:
 ** 30 августа 2017 г. APasternak. Суть внесенных изменений
 *******************************************************************************
 */
/*!
 ** \file  mgc_calc_as_template.h
 ** \brief Краткий комментарий к файлу
 **      Определение шаблона вычисления матрицы направляющих косинусов
 ** Расширенный комментарий к файлу
 */

#ifndef MGC_CALC_AS_TEMPLATE_H
#define MGC_CALC_AS_TEMPLATE_H

//#ifdef T
#include <stdlib.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

typedef enum EmgcTypes {
    CONNECTED_TO_SPEED_CS = 0,
    SPEED_TO_CONNECTED_CS,

    HORIZONTED_TO_NORMAL_CS,
    NORMAL_TO_HORIZONTED_CS,

    HORIZONTED_TO_CONNECTED_CS,
    CONNECTED_TO_HORIZONTED_CS,

    NORMAL_TO_CONNECTED_CS,
    CONNECTED_TO_NORMAL_CS,

    TRAJECTORY_TO_CONNECTED_CS,
    CONNECTED_TO_TRAJECTORY_CS,

    SPEED_TO_CONNECTED_CS,
    CONNECTED_TO_SPEED_CS,

    CONNECTED_TO_BEAM_Z_UP_Y_LEFT_CS,
    BEAM_Z_UP_Y_LEFT_TO_CONNECTED_CS,

    CONNECTED_TO_BEAM_Y_LEFT_Z_UP_CS,
    BEAM_Y_LEFT_Z_UP_TO_CONNECTED_CS
} TmgcTypes;

int TEMPLATE( mgc_calc, T) ( T*, const T*, const TmgcTypes);

#endif

//#endif

#endif // MGC_CALC_AS_TEMPLATE_H

