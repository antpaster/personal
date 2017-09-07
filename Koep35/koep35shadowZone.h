#ifndef KOEP35SHADOWZONE_H
#define KOEP35SHADOWZONE_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdint.h>

#ifndef GrToRad
#define GrToRad ( M_PI / 180.0)
#endif

#ifndef RadToGr
#define RadToGr ( 180.0 / M_PI)
#endif

/*! Количество опорных точек ограничения обзора КОЭП */
#define NODE_POINT_COUNT_KOEP 151

/*! Нуль для вычислений */
#ifndef F_NULL
#define F_NULL 1e-20
#endif

/*! Система координат:
 * Азимут +Y --> положительный поворот вправо
 * Угол места +Z --> положительный поворот вверх */

/*! Перечисление типов теней на подвесках. Значение элементов перечисления должно быть нечетным для
 * отрицательных значений азимута, и четным для положительных значений азимута */
typedef enum EhangPointShadow
{
    PLANE_SHAPE_Y_POS         = 0, /*!< конструкция самолета, азимут [0; 150] */
    PLANE_SHAPE_Y_NEG         = 1, /*!< конструкция самолета, азимут [-150; 0] */
    TP4_RVV                   = 2, /*!< ТП4 РВВ, азимут [0; 150] */
    TP1_RVV                   = 3, /*!< ТП1 РВВ (кроме РВВ БД), азимут [-150; 0] */
    TP4_RVV_LD                = 4, /*!< ТП4 РВВ (пусковые установки), азимут [0; 150] */
    TP1_KAB_RVP_RVV_BD        = 5, /*!< ТП1 КАБ, РВП, РВВ БД, азимут [-150; 0] */
    TP4_KAB_RVP               = 6, /*!< ТП4 КАБ, РВП, азимут [0; 150] */
    TP1_UNCONTROL_AB          = 7, /*!< ТП1 неуправляемые АБ, азимут [-150; 0] */
    TP4_KAB_RVP_LD            = 8, /*!< ТП4 КАБ, РВП (пусковые установки), азимут [0; 150] */
    TP9_RVV                   = 9, /*!< ТП9 РВВ (кроме РВВ БД), азимут [-150; 0] */
    TP4_UNCONTROL_AB_NAR     = 10, /*!< ТП4 неуправляемые АБ, НАР, азимут [0; 150] */
    TP9_RVV_LD               = 11, /*!< ТП9 РВВ (кроме РВВ БД) (пусковые установки),
        азимут [-150; 0] */
    TP4_UNCONTROL_AB_NAR_LD  = 12, /*!< ТП4 неуправляемые АБ, НАР (пусковые установки),
        азимут [0; 150] */
    TP9_KAB_RVP_RVV_BD       = 13, /*!< ТП9 КАБ, РВП, РВВ БД, азимут [-150; 0] */
    TP6_RVV                  = 14, /*!< ТП6 РВВ, азимут [0; 150] */
    TP9_UNCONTROL_AB         = 15, /*!< ТП9 неуправляемые АБ, азимут [-150; 0] */
    TP6_RVV_LD               = 16, /*!< ТП6 РВВ (пусковые установки), азимут [0; 150] */
    TP9_KAB_RVP_RVV_BD_LD    = 17, /*!< ТП9 КАБ, РВП, РВВ БД (пусковые установки),
        азимут [-150; 0] */
    TP8_RVV                  = 18, /*!< ТП8 РВВ, азимут [0; 150] */
    TP9_UNCONTROL_AB_LD      = 19, /*!< ТП9 неуправляемые АБ (пусковые установки),
        азимут [-150; 0] */
    TP12_RVV                 = 20, /*!< ТП12 РВВ (кроме РВВ БД), азимут [0; 150] */
    SHALLOW_21               = 21, /*!< заглушка, азимут [ -150; 0] */
    TP12_KAB_RVP_RVV_BD      = 22, /*!< ТП12 КАБ, РВП, РВВ БД, азимут [0; 150] */
    SHALLOW_23               = 23, /*!< заглушка, азимут [ -150; 0] */
    TP12_KAB_RVP_RVV_BD_LD   = 24, /*!< ТП12 КАБ, РВП, РВВ БД (пусковые установки),
        азимут [0; 150] */
    SHALLOW_25               = 25, /*!< заглушка, азимут [ -150; 0] */
    TP12_UNCONTROL_AB_NAR    = 26, /*!< ТП12 неуправляемые АБ, НАР, азимут [0; 150] */
    SHALLOW_27               = 27, /*!< заглушка, азимут [ -150; 0] */
    TP12_UNCONTROL_AB_NAR_LD = 28, /*!< ТП12 неуправляемые АБ, НАР (пусковые установки),
        азимут [0; 150] */
    SHALLOW_29               = 29, /*!< заглушка, азимут [ -150; 0] */
    TP8_L265M10              = 30, /*!< ТП6 Л-265М10, азимут [0; 150] */
    SHALLOW_31               = 31, /*!< заглушка, азимут [ -150; 0] */
    HANG_POINT_SHADOW_ALL    = 32  /*!< всего теней - размер массива данных */
} ThangPointShadow;

/*! Функция ограничения углов обзора КОЭП
 * Значения углов в радианах
 **************************************************************************************************/
void koep35checkVisionAngles(
    double *Y, /*!< азимут в ССК */
    double *Z, /*!< угол места в ССК */
    uint8_t *limY, /*!< 0 - допустимое значение по Y, 1 - недопустимое значение по Y */
    uint8_t *limZ, /*!< 0 - допустимое значение по Z, 1 - недопустимое значение по Z */
    uint8_t *shadow1deg, /*!< признак затенения 1 град. */
    uint8_t *shadow5deg  /*!< признак затенения 5 град. */
);

#endif /* KOEP35SHADOWZONE_H */
