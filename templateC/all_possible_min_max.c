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
 ** \file  all_possible_min_max.c
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 30.08.17
 ** \brief All possible types for min / max elemants definition template realization
 */

#include "templates.h"

#ifdef TEMPLATE_LIB

#include "all_possible_min_max.h"

#ifdef T
#undef T
#endif

#define T float
#include "min_max_as_template.c"

#ifdef T
#undef T
#endif

#define T double
#include "min_max_as_template.c"

#ifdef T
#undef T
#endif

#define T int
#include "min_max_as_template.c"

#endif
