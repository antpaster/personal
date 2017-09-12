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
 ** \file  insert_sort_as_template.h
 ** \brief Краткий комментарий к файлу
 **      Описание шаблона сортировки массива простыми вставками
 ** Расширенный комментарий к файлу
 */

#ifndef INSERT_SORT_AS_TEMPLATE_H_
#define INSERT_SORT_AS_TEMPLATE_H_

#ifdef T
#include <stdlib.h>
#include <stdint.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

//int TEMPLATE( insert_sort, T)( T*, T*, size_t, uint8_t);
int TEMPLATE( insert_sort, T)( T*, size_t, uint8_t);
#endif

#endif

#endif /* INSERT_SORT_AS_TEMPLATE_H_ */
