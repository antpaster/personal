/********************************** ukbo42 *************************************
 ** ОРГАНИЗАЦИЯ:     ОАО "РПКБ"
 ** СОЗДАН:          30.08.17 г. APasternak
 ** ИЗМЕНЕН:         30.08.17 г. APasternak
 *******************************************************************************
 ** ПЕРЕЧЕНЬ ИЗМЕНЕНИЙ:
 ** 30.08.17 г. APasternak. Суть внесенных изменений
 *******************************************************************************
 */
/*!
 ** \file  mgc_calc_as_template.h
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 08.09.17
 ** \brief MGC calculations templates description
 */

#ifndef MGC_CALC_AS_TEMPLATE_H
#define MGC_CALC_AS_TEMPLATE_H

#ifdef T
#include <stdlib.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

/*! Types of coordinate transformations enumeration
 ***************************************************************************************************
 */
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

    CONNECTED_TO_BEAM_Z_UP_Y_LEFT_CS,
    BEAM_Z_UP_Y_LEFT_TO_CONNECTED_CS,

    CONNECTED_TO_BEAM_Y_LEFT_Z_UP_CS,
    BEAM_Y_LEFT_Z_UP_TO_CONNECTED_CS
} TmgcTypes;

/*! MGC calculations template
 * \param[ out] result Result 3x3 matrix pointer
 * \param[ in] angles Angles for transformation pointer
 * \param[ in] mt type of the coordinate transformation
 ***************************************************************************************************
 * \return 0 - ok, 1 - Null pointer to result or angles
 */
int TEMPLATE( mgc_calc, T) ( T*, const T*, const TmgcTypes);

#endif

#endif

#endif // MGC_CALC_AS_TEMPLATE_H

