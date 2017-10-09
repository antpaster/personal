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
 ** \file  templates.h
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 30.08.17
 ** \brief Header master file of the template library
 */

#ifndef TEMPLATES_H
#define TEMPLATES_H

#ifndef F_NULL
#define F_NULL 1e-20 /*!< very tiny float number for zero division protection */
#endif

#define TEMPLATE_LIB /*!< whole library trigger */

#define CAT( X, Y) X##_##Y
#define TEMPLATE( X, Y) CAT( X, Y)

#include "all_possible_sums.h"
#include "all_possible_subtractions.h"
#include "all_possible_multiplications.h"
#include "all_possible_divisions.h"
#include "all_possible_insert_sorts.h"
#include "all_possible_min_max.h"
#include "all_possible_mgc_calcs.h"
#include "all_possible_matrix_ops.h"

#endif // TEMPLATES_H

