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
 ** \file  insert_sort_as_template.c
 ** \brief Краткий комментарий к файлу
 **      Реализация шаблона сортировки массива простыми вставками
 ** Расширенный комментарий к файлу
 */

#ifdef T
#include <stdlib.h>
#include <math.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

//int TEMPLATE( insert_sort, T) ( T *res, T *a, size_t size, uint8_t ascendingFlag) {
int TEMPLATE( insert_sort, T) ( T *res, size_t size, uint8_t ascendingFlag) {
    int result = 1;

    if( res/* && a*/) {
        int i, j;

//        memmove( res, a, size * sizeof( T));

//        T *currAddr;
//        T temp;
//        for( i = 0; i < size; ++i) {
//            temp = *res;

//            for( j = i - 1; j >= 0
////                && ( ( ascendingFlag) ? ( temp > *( res + j)) : ( temp < *( res + j))); j--) {
//                 && ( temp > *( res + j)); j--) {
//                currAddr = res + j + 1;
//                *currAddr = *( res + j);

//                --res;
//            }

//            currAddr = res + j + 1;
//            *currAddr = temp;

//            ++res;
//        }

        T temp;
        for( i = 0; i < size; ++i) {
            temp = res[ i];

            for( j = i - 1; j >= 0
//                && ( ( ascendingFlag) ? ( temp > res[ j]) : ( temp < res[ j])); j--) {
                && ( temp > res[ j]); j--) {
                res[ j + 1] = res[ j];
            }

            temp = res[ j + 1];
        }

        result = 0;
    }

    return result;
}

#endif

#endif

