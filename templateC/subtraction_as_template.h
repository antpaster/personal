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
 ** \file  subtraction_as_template.h
 ** \brief Краткий комментарий к файлу
 **      Описание шаблона вычитания
 ** Расширенный комментарий к файлу
 */

#ifndef SUBTRACTION_AS_TEMPLATE_H
#define SUBTRACTION_AS_TEMPLATE_H

#ifdef T
#include <stdlib.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

void TEMPLATE( subtract, T)( T*, T*, T*, size_t);
#endif

#endif

#endif // SUBTRACTION_AS_TEMPLATE_H

