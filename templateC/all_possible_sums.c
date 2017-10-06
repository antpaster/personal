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
 ** \file  all_possible_sums.c
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 30.08.17
 ** \brief All possible types for sum template realization
 */

#include "templates.h"

#ifdef TEMPLATE_LIB

#include "all_possible_sums.h"

#ifdef T
#undef T
#endif

#define T float
#include "sum_as_template.c"

#ifdef T
#undef T
#endif

#define T double
#include "sum_as_template.c"

#ifdef T
#undef T
#endif

#define T int
#include "sum_as_template.c"

#endif
