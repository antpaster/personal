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
 ** \file  subtraction_as_template.c
 ** \brief Краткий комментарий к файлу
 **      Реализация шаблона вычитания
 ** Расширенный комментарий к файлу
 */

#ifdef T
#include <stdlib.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

void TEMPLATE( subtract, T) ( T *res, T *a, T *b, size_t size) {
    int i;
    T *currAddr;
    for( i = 0; i < size; ++i) {
        currAddr = res + i;
        *currAddr = *(a + i) - *(b + i);
    }
}

#endif

#endif

