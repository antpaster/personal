/********************************** ukbo42 *************************************
 ** ОРГАНИЗАЦИЯ:     ОАО "РПКБ"
 ** СОЗДАН:          12.09.17 г. APasternak
 ** ИЗМЕНЕН:         12.09.17 г. APasternak
 *******************************************************************************
 ** ПЕРЕЧЕНЬ ИЗМЕНЕНИЙ:
 ** 12.09.17 г. APasternak. Суть внесенных изменений
 *******************************************************************************
 */
/*!
 ** \file  all_possible_mgc_calcs.h
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 12.09.17
 ** \brief All possible types for MGC calculations template description
 */

#ifndef ALL_POSSIBLE_MGC_CALCS_H
#define ALL_POSSIBLE_MGC_CALCS_H

#include "templates.h"

#ifdef TEMPLATE_LIB

#ifdef T
#undef T
#endif

#define T float
#include "mgc_calc_as_template.h"

#ifdef T
#undef T
#endif

#define T double
#include "mgc_calc_as_template.h"

#endif

#endif // ALL_POSSIBLE_MGC_CALCS_H

