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
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 30.08.17
 ** \brief Simple insert sort template description
 */

#ifndef INSERT_SORT_AS_TEMPLATE_H_
#define INSERT_SORT_AS_TEMPLATE_H_

#ifdef T
#include <stdlib.h>
#include <stdint.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

/*! Simple insert sort template
 * \param[ in, out] result Array for sorting pointer
 * \param[ in] size Array size
 * \param[ in] ascendingFlag flag for sorting direction: 1 - ascending, 0 - descending
 ***************************************************************************************************
 * \return 0 - ok, 1 - null pointer to the array
 */
int TEMPLATE( insert_sort, T)( T*, const size_t, const uint8_t);

#endif

#endif

#endif /* INSERT_SORT_AS_TEMPLATE_H_ */
