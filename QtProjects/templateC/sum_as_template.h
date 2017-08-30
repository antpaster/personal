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
 ** \file  sum_as_template.h
 ** \brief Краткий комментарий к файлу
 **      Описание шаблона суммирования
 ** Расширенный комментарий к файлу
 */

#ifndef SUM_AS_TEMPLATE_H
#define SUM_AS_TEMPLATE_H

#include "templates.h"

#ifdef TEMPLATE_LIB

#ifdef T
#include <stdlib.h>

#include "templates.h"

void TEMPLATE( add, T)( T*, T*, T*, size_t);
#endif

#endif

#endif // SUM_AS_TEMPLATE_H

