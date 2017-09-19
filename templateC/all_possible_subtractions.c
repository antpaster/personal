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
 ** \file  all_possible_subtractions.c
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 30.08.17
 ** \brief All possible types for subtraction template realization
 */

#include "templates.h"

#ifdef TEMPLATE_LIB

#include "all_possible_subtractions.h"

#ifdef T
#undef T
#endif

#define T float
#include "subtraction_as_template.c"

#ifdef T
#undef T
#endif

#define T double
#include "subtraction_as_template.c"

#ifdef T
#undef T
#endif

#define T int
#include "subtraction_as_template.c"

#endif
