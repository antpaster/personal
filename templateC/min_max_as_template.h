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
 ** \file  min_max_as_template.h
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 30.08.17
 ** \brief Min / max array's element definition template description
 */

#ifndef MIN_MAX_AS_TEMPLATE_H_
#define MIN_MAX_AS_TEMPLATE_H_

#ifdef T
#include <stdlib.h>
#include <stdint.h>

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
int TEMPLATE( min_max, T)( T*, const T*, const size_t, const uint8_t);

#endif

#endif

#endif /* MIN_MAX_AS_TEMPLATE_H_ */
