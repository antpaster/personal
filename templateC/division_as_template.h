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
 ** \file  division_as_template.h
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 30.08.17
 ** \brief Division template description
 */

#ifndef DIVISION_AS_TEMPLATE_H
#define DIVISION_AS_TEMPLATE_H

#ifdef T
#include <stdlib.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

/*! Division template
 * \param[ out] result Result array pointer
 * \param[ in] a Divisor array pointer
 * \param[ in] b Divider array pointer
 * \param[ in] size Arrays' size
 ***************************************************************************************************
 * \result 0 - ok, 1 - null pointer to result, a or b
 */
int TEMPLATE( divide, T)( T*, const T*, const T*, const size_t);
#endif

#endif

#endif // DIVISION_AS_TEMPLATE_H

