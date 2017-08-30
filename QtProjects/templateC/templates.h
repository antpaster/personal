/********************************** ukbo42 *************************************
 ** ОРГАНИЗАЦИЯ:     ОАО "РПКБ"
 ** СОЗДАН:          30 августа 2017 г. APasternak
 ** ИЗМЕНЕН:         30 августа 2017 г. APasternak
 *******************************************************************************
 ** ПЕРЕЧЕНЬ ИЗМЕНЕНИЙ:
 ** 30 августа 2017 г. APasternak. Суть внесенных изменений
 *******************************************************************************
 */
/*!
 ** \file  templates.h
 ** \brief Краткий комментарий к файлу
 **      Заголовочный мастер-файл библиотеки шаблонов
 ** Расширенный комментарий к файлу
 */

#ifndef TEMPLATES_H
#define TEMPLATES_H

#ifndef F_NULL
#define F_NULL 1e-20 /* очень маленькое число для защиты от деления на 0 */
#endif

#define TEMPLATE_LIB /* триггер библиотеки */

#define CAT( X, Y) X##_##Y
#define TEMPLATE( X, Y) CAT( X, Y)

#include "all_possible_sums.h"
#include "all_possible_subtractions.h"
#include "all_possible_multiplications.h"
#include "all_possible_divisions.h"

#endif // TEMPLATES_H

