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
 ** \brief Краткий комментарий к файлу
 **      Описание допустимых типов для шаблона деления
 ** Расширенный комментарий к файлу
 */

#ifndef ALL_POSSIBLE_DIVISIONS_H
#define ALL_POSSIBLE_DIVISIONS_H

#include "templates.h"

#ifdef TEMPLATE_LIB

#ifdef T
#undef T
#endif

#define T float
#include "division_as_template.h"

#ifdef T
#undef T
#endif

#define T double
#include "division_as_template.h"

#ifdef T
#undef T
#endif

#define T int
#include "division_as_template.h"

#endif

#endif // ALL_POSSIBLE_DIVISIONS_H

