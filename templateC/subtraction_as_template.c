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
 ** \file  subtraction_as_template.c
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 30.08.17
 ** \brief Subtraction template realization
 */

#ifdef T
#include <stdlib.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

/*! Subtraction template
 * \param[ out] result Result array pointer
 * \param[ in] a Subtrahend array pointer
 * \param[ in] b Subtractor array pointer
 * \param[ in] size Arrays' sizes
 ***************************************************************************************************
 * \return 0 - ok, 1 - Null pointer to result, a or b
 */
int TEMPLATE( subtract, T) ( T *result, const T *a, const T *b, const size_t size) {
    if( result && a && b) {
        size_t i;
        T *currAddr;
        for( i = 0; i < size; ++i) {
            currAddr = result + i;
            *currAddr = *( a + i) - *( b + i);
        }

        return 0;
    }

    return 1;
}

#endif

#endif

