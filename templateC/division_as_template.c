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
 ** \file  division_as_template.c
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 30.08.17
 ** \brief Division template realization
 */

#ifdef T
#include <stdlib.h>
#include <math.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

/*! Division template
 * \param[ out] result Result array pointer
 * \param[ in] a Divisor array pointer
 * \param[ in] b Divider array pointer
 * \param[ in] size Arrays' size
 ***************************************************************************************************
 * \result 0 - ok, 1 - null pointer to result, a or b
 */
int TEMPLATE( divide, T) ( T *result, const T *a, const T *b, const size_t size) {
    if( result && a && b) {
        int i;
        T *currAddr;
        for( i = 0; i < size; ++i) {
            currAddr = result + i;
            *currAddr = *( a + i) / ( fabs( *( b + i)) > F_NULL ? *( b + i) : F_NULL);
        }

        return 0;
    }

    return 1;
}

#endif

#endif

