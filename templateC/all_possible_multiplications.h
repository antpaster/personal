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
 ** \file  all_possible_multiplications.h
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 30.08.17
 ** \brief All possible types for multiplication template description
 */

#ifndef ALL_POSSIBLE_MULTIPLICATIONS_H
#define ALL_POSSIBLE_MULTIPLICATIONS_H

#include "templates.h"

#ifdef TEMPLATE_LIB

#ifdef T
#undef T
#endif

#define T float
#include "multiplication_as_template.h"

#ifdef T
#undef T
#endif

#define T double
#include "multiplication_as_template.h"

#ifdef T
#undef T
#endif

#define T int
#include "multiplication_as_template.h"

#endif

#endif // ALL_POSSIBLE_MULTIPLICATIONS_H

