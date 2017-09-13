/********************************** ukbo42 *************************************
 ** ОРГАНИЗАЦИЯ:     ОАО "РПКБ"
 ** СОЗДАН:          13.09.17 г. APasternak
 ** ИЗМЕНЕН:         13.09.17 г. APasternak
 *******************************************************************************
 ** ПЕРЕЧЕНЬ ИЗМЕНЕНИЙ:
 ** 13.09.17 г. APasternak. Суть внесенных изменений
 *******************************************************************************
 */
/*!
 ** \file  all_possible_matrix_ops.c
 ** \brief Краткий комментарий к файлу
 **      Реализация допустимых типов для шаблонов матричных операций
 ** Расширенный комментарий к файлу
 */

#include "templates.h"

#ifdef TEMPLATE_LIB

#include "all_possible_matrix_ops.h"

#ifdef T
#undef T
#endif

#define T float
#include "matrix_ops_as_template.c"

#ifdef T
#undef T
#endif

#define T double
#include "matrix_ops_as_template.c"

#endif

