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
 ** \file  insert_sort_as_template.c
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 30.08.17
 ** \brief Simple insert sort template realization
 */

#ifdef T
#include <stdlib.h>
#include <math.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

/*! Simple insert sort template
 * \param[ in, out] result Array for sorting pointer
 * \param[ in] size Array size
 * \param[ in] ascendingFlag flag for sorting direction: 1 - ascending, 0 - descending
 ***************************************************************************************************
 * \return 0 - ok, 1 - null pointer to the array
 */
int TEMPLATE( insert_sort, T) ( T *result, const size_t size, const uint8_t ascendingFlag) {
    if( result) {
        T temp;
        int i, j;

//        T *currAddr;
//        for( i = 0; i < size; ++i) {
//            temp = *( result + i);

//            for( j = i - 1; j >= 0
//                && ( ( ascendingFlag) ? ( temp < *( result + j)) : ( temp > *( result + j))); --j) {
////                 && ( temp > *( result + j)); --j) {
//                currAddr = result + j + 1;
//                currAddr = result + j;
//            }

//            currAddr = result + j + 1;
//            *currAddr = temp;
//        }


//        T *currAddr;
//        for( i = 0; i < size; ++i) {
//            temp = *result;

//            result += ( i - 1 >= 0) ? i - 1 : 0;
//            for( j = i - 1; j >= 0
//                && ( ( ascendingFlag) ? ( temp < *result) : ( temp > *result)); --j) {
////                 && ( temp > *result); --j) {
//                currAddr = result + 1;
//                currAddr = result;

//                --result;
//            }

//            currAddr = result + j + 1;
//            *currAddr = temp;

//            ++result;
//        }


        for( i = 0; i < size; ++i) {
            temp = result[ i];

            for( j = i - 1; j >= 0
                && ( ( ascendingFlag) ? ( temp < result[ j]) : ( temp > result[ j])); --j) {
                result[ j + 1] = result[ j];
            }

            result[ j + 1] = temp;
        }

        return 0;
    }

    return 1;
}

#endif

#endif

