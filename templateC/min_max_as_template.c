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
 ** \file  min_max_as_template.c
 ** \brief Краткий комментарий к файлу
 **      Реализация шаблона нахождения минимального / максимального элементов массива
 ** Расширенный комментарий к файлу
 */

#ifdef T
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

T TEMPLATE( min_max, T)( T *a, size_t size, uint8_t maxFlag) {
    int i;
    T res = *a;

    for( i = 1; i < size; ++i) {
        if( ( ( maxFlag) ? ( res < *( a + i)) : ( res > *( a + i)))) {
            res = *( a + i);
        }
    }

    return res;
}

#endif

#endif

