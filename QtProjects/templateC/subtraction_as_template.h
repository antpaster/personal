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
 ** \file  subtraction_as_template.h
 ** \brief Краткий комментарий к файлу
 **      Описание шаблона вычитания
 ** Расширенный комментарий к файлу
 */

#ifndef SUBTRACTION_AS_TEMPLATE_H
#define SUBTRACTION_AS_TEMPLATE_H

#include "templates.h"

#ifdef TEMPLATE_LIB

#ifdef T
#include <stdlib.h>

#include "templates.h"

void TEMPLATE( subtract, T)( T*, T*, T*, size_t);
#endif

#endif

#endif // SUBTRACTION_AS_TEMPLATE_H

