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
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 30.08.17
 ** \brief Min / max array's element definition template realization
 */

#ifdef T
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

/*! Min / max array's element definition template
 * \param[ out] result Result variable pointer
 * \param[ in] a Array pointer
 * \param[ in] size Array size
 * \param[ in] maxFlag Variable that defines whether we find maximum element or not:
 * 1 - max element, 0 - min element
 ***************************************************************************************************
 * \return 0 - ok, 1 - Null pointer to result or array
 */
int TEMPLATE( min_max, T)( T *result, const T *a, const size_t size, const uint8_t maxFlag) {
    if( result && a) {
        size_t i;
        T tempRes = *a;

        for( i = 1; i < size; ++i) {
            if( ( maxFlag) ? ( tempRes < *( a + i)) : ( tempRes > *( a + i))) {
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

