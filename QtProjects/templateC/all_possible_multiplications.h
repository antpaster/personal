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
 ** \file  all_possible_multiplications.h
 ** \brief Краткий комментарий к файлу
 **      Описание допустимых типов для шаблона умножения
 ** Расширенный комментарий к файлу
 */

#ifndef ALL_POSSIBLE_MULTIPLICATIONS_H
#define ALL_POSSIBLE_MULTIPLICATIONS_H

#include "templates.h"

#ifdef TEMPLATE_LIB

#ifdef T
#undef T
#endif

#define T float
#include "multiplication_as_template.h"

#ifdef T
#undef T
#endif

#define T double
#include "multiplication_as_template.h"

#ifdef T
#undef T
#endif

#define T int
#include "multiplication_as_template.h"

#endif

#endif // ALL_POSSIBLE_MULTIPLICATIONS_H

