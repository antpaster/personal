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
 ** \file  all_possible_min_max.h
 ** \brief Краткий комментарий к файлу
 **      Описание допустимых типов для шаблона нахождения
 **      минимального / максимального элементов массива
 ** Расширенный комментарий к файлу
 */

#ifndef ALL_POSSIBLE_MIN_MAX_H_
#define ALL_POSSIBLE_MIN_MAX_H_

#include "templates.h"

#ifdef TEMPLATE_LIB

#ifdef T
#undef T
#endif

#define T float
#include "min_max_as_template.h"

#ifdef T
#undef T
#endif

#define T double
#include "min_max_as_template.h"

#ifdef T
#undef T
#endif

#define T int
#include "min_max_as_template.h"

#endif

#endif /* ALL_POSSIBLE_MIN_MAX_H_ */
