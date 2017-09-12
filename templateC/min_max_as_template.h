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
 ** \file  min_max_as_template.h
 ** \brief Краткий комментарий к файлу
 **      Описание шаблона нахождения минимального / максимального элементов массива
 ** Расширенный комментарий к файлу
 */

#ifndef MIN_MAX_AS_TEMPLATE_H_
#define MIN_MAX_AS_TEMPLATE_H_

#ifdef T
#include <stdlib.h>
#include <stdint.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

int TEMPLATE( min_max, T)( T*, const T*, const size_t, const uint8_t);

#endif

#endif

#endif /* MIN_MAX_AS_TEMPLATE_H_ */
