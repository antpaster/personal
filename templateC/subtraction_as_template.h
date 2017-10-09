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
 ** \file  subtraction_as_template.h
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 30.08.17
 ** \brief Subtraction template description
 */

#ifndef SUBTRACTION_AS_TEMPLATE_H
#define SUBTRACTION_AS_TEMPLATE_H

#ifdef T
#include <stdlib.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

/*! Subtraction template
 * \param[ out] result Result array pointer
 * \param[ in] a Subtrahend array pointer
 * \param[ in] b Subtractor array pointer
 * \param[ in] size Arrays' sizes
 ***************************************************************************************************
 * \return 0 - ok, 1 - Null pointer to result, a or b
 */
int TEMPLATE( subtract, T)( T*, const T*, const T*, const size_t);

#endif

#endif

#endif // SUBTRACTION_AS_TEMPLATE_H

