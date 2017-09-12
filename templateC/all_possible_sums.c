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
 ** \brief Краткий комментарий к файлу
 **      Реализация допустимых типов для шаблона суммирования
 ** Расширенный комментарий к файлу
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
