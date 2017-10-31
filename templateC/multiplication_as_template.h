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
 ** \file  multiplication_as_template.h
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 30.08.17
 ** \brief Multiplication template description
 */

#ifndef MULTIPLICATION_AS_TEMPLATE_H
#define MULTIPLICATION_AS_TEMPLATE_H

#ifdef T
#include <stdlib.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

/*! Multiplication template
 * \param[ out] result Result array pointer
 * \param[ in] a 1st array-multiplicator pointer
 * \param[ in] b 2nd array-multiplicator pointer
 * \param[ in] size Size of the arrays
 ***************************************************************************************************
 * \return 0 - ok, 1 - Null pointer to result, a or b
 */
int TEMPLATE( multiply, T)( T*, const T*, const T*, const size_t);

#endif

#endif

#endif // MULTIPLICATION_AS_TEMPLATE_H

