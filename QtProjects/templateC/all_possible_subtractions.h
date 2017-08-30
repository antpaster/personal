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
 ** \file  all_possible_subtractions.h
 ** \brief Краткий комментарий к файлу
 **      Описание допустимых типов для шаблона вычитания
 ** Расширенный комментарий к файлу
 */

#ifndef ALL_POSSIBLE_SUBTRACTIONS_H
#define ALL_POSSIBLE_SUBTRACTIONS_H

#include "templates.h"

#ifdef TEMPLATE_LIB

#ifdef T
#undef T
#endif

#define T float
#include "subtraction_as_template.h"

#ifdef T
#undef T
#endif

#define T double
#include "subtraction_as_template.h"

#ifdef T
#undef T
#endif

#define T int
#include "subtraction_as_template.h"

#endif

#endif // ALL_POSSIBLE_SUBTRACTIONS_H

