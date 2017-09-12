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
 ** \file  all_possible_mgc_calcs.c
 ** \brief Краткий комментарий к файлу
 **      Реализация допустимых типов для шаблона вычисления матрицы направляющих
 ** косинусов
 ** Расширенный комментарий к файлу
 */

#include "templates.h"

#ifdef TEMPLATE_LIB

#include "all_possible_mgc_calcs.h"

#ifdef T
#undef T
#endif

#define T float
#include "mgc_calc_as_template.c"

#ifdef T
#undef T
#endif

#define T double
#include "mgc_calc_as_template.c"

#endif
