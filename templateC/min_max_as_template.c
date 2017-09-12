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

int TEMPLATE( min_max, T)( T *result, const T *a, const size_t size, const uint8_t maxFlag) {
    if( result && a) {
        int i;
        T tempRes = *a;

        for( i = 1; i < size; ++i) {
            if( ( ( maxFlag) ? ( tempRes < *( a + i)) : ( tempRes > *( a + i)))) {
                tempRes = *( a + i);
            }
        }

        *result = tempRes;

        return 0;
    }

    return 1;
}

#endif

#endif

