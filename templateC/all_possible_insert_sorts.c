/********************************** ukbo42 *************************************
 ** ОРГАНИЗАЦИЯ:     ОАО "РПКБ"
 ** СОЗДАН:          30 августа 2017 г. APasternak
 ** ИЗМЕНЕН:         30 августа 2017 г. APasternak
 *******************************************************************************
 ** ПЕРЕЧЕНЬ ИЗМЕНЕНИЙ:
 ** 30 августа 2017 г. APasternak. Суть внесенных изменений
 *******************************************************************************
 */
/*!
 ** \file  all_possible_insert_sorts.c
 ** \brief Краткий комментарий к файлу
 **      Реализация допустимых типов для шаблона сортировки элементов массива
 **      простыми вставками
 ** Расширенный комментарий к файлу
 */

#include "templates.h"

#ifdef TEMPLATE_LIB

#include "all_possible_insert_sorts.h"

#ifdef T
#undef T
#endif

#define T float
#include "insert_sort_as_template.c"

#ifdef T
#undef T
#endif

#define T double
#include "insert_sort_as_template.c"

#ifdef T
#undef T
#endif

#define T int
#include "insert_sort_as_template.c"

#endif
