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
 ** \file  all_possible_insert_sorts.h
 ** \brief Краткий комментарий к файлу
 **      Описание допустимых типов для шаблона сортировки массива простыми
 **      вставками
 ** Расширенный комментарий к файлу
 */
#ifndef ALL_POSSIBLE_INSERT_SORTS_H_
#define ALL_POSSIBLE_INSERT_SORTS_H_

#include "templates.h"

#ifdef TEMPLATE_LIB

#ifdef T
#undef T
#endif

#define T float
#include "insert_sort_as_template.h"

#ifdef T
#undef T
#endif

#define T double
#include "insert_sort_as_template.h"

#ifdef T
#undef T
#endif

#define T int
#include "insert_sort_as_template.h"

#endif

#endif /* ALL_POSSIBLE_INSERT_SORTS_H_ */
