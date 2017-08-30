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
 ** \file  division_as_template.h
 ** \brief Краткий комментарий к файлу
 **      Описание шаблона деления
 ** Расширенный комментарий к файлу
 */

#ifndef DIVISION_AS_TEMPLATE_H
#define DIVISION_AS_TEMPLATE_H

#ifdef T
#include <stdlib.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

void TEMPLATE( divide, T)( T*, T*, T*, size_t);
#endif

#endif

#endif // DIVISION_AS_TEMPLATE_H

