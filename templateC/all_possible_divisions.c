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
 ** \file  all_possible_divisions.h
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 30.08.17
 ** \brief All possible types for division template realization
 */

#include "templates.h"

#ifdef TEMPLATE_LIB

#include "all_possible_divisions.h"

#ifdef T
#undef T
#endif

#define T float
#include "division_as_template.c"

#ifdef T
#undef T
#endif

#define T double
#include "division_as_template.c"

#ifdef T
#undef T
#endif

#define T int
#include "division_as_template.c"

#endif
