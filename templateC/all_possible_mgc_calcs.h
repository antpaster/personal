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
 ** \brief Краткий комментарий к файлу
 **      Описание допустимых типов для шаблона вычисления матрицы направляющих
 ** косинусов
 ** Расширенный комментарий к файлу
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

