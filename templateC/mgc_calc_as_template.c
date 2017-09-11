/********************************** ukbo42 *************************************
 ** ОРГАНИЗАЦИЯ:     АО "РПКБ"
 ** СОЗДАН:          08.09.17 г. APasternak
 ** ИЗМЕНЕН:         08.09.17 г. APasternak
 *******************************************************************************
 ** ПЕРЕЧЕНЬ ИЗМЕНЕНИЙ:
 ** 08.09.17 г. APasternak. Суть внесенных изменений
 *******************************************************************************
 */
/*!
 ** \file  mgc_calc_as_template.c
 ** \brief Краткий комментарий к файлу
 **      Реализация шаблона вычисления матрицы направляющих косинусов
 ** Расширенный комментарий к файлу
 */

//#ifdef T
#include <stdlib.h>
#include <math.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

int TEMPLATE( mgc_calc, T) ( T *res, const T *angles, const TmgcTypes mt) {

    if( res && angles) {
        switch( mt) {
        case CONNECTED_TO_SPEED_CS: {
            double attackSin = sin( *angles);
            double attackCos = cos( *angles);
            double slideSin = sin( *( angles + 1));
            double slideCos = cos( *( angles + 1));

            double *currAddr = res;
            *currAddr = attackCos * slideCos;
            currAddr++;
            *currAddr = -attackSin * slideCos;
            currAddr++;
            *currAddr = slideSin;

            currAddr++;
            *currAddr = attackSin;
            currAddr++;
            *currAddr = attackCos;
            currAddr++;
            *currAddr = 0.0;

            currAddr++;
            *currAddr = -attackCos * slideSin;
            currAddr++;
            *currAddr = attackSin * slideSin;
            currAddr++;
            *currAddr = slideCos;

            return 0;
        }

        case SPEED_TO_CONNECTED_CS: {
            double attackSin = sin( *angles);
            double attackCos = cos( *angles);
            double slideSin = sin( *( angles + 1));
            double slideCos = cos( *( angles + 1));

            double *currAddr = res;
            *currAddr = attackCos * slideCos;
            currAddr++;
            *currAddr = attackSin;
            currAddr++;
            *currAddr = -attackCos * slideSin;

            currAddr++;
            *currAddr = -attackSin * slideCos;
            currAddr++;
            *currAddr = attackCos;
            currAddr++;
            *currAddr = attackSin * slideSin;

            currAddr++;
            *currAddr = slideSin;
            currAddr++;
            *currAddr = 0.0;
            currAddr++;
            *currAddr = slideCos;

            return 0;
        }

        case HORIZONTED_TO_NORMAL_CS: {
            double courseSin = sin( *angles);
            double courseCos = cos( *angles);

            double *currAddr = res;
            *currAddr = courseCos;
            currAddr++;
            *currAddr = 0.0;
            currAddr++;
            *currAddr = -courseSin;

            currAddr++;
            *currAddr = 0.0;
            currAddr++;
            *currAddr = 1.0;
            currAddr++;
            *currAddr = 0.0;

            currAddr++;
            *currAddr = courseSin;
            currAddr++;
            *currAddr = 0.0;
            currAddr++;
            *currAddr = courseCos;

            return 0;
        }

        case NORMAL_TO_CONNECTED_CS: {
            double courseSin = sin( *angles);
            double courseCos = cos( *angles);

            double *currAddr = res;
            *currAddr = courseCos;
            currAddr++;
            *currAddr = 0.0;
            currAddr++;
            *currAddr = courseSin;

            currAddr++;
            *currAddr = 0.0;
            currAddr++;
            *currAddr = 1.0;
            currAddr++;
            *currAddr = 0.0;

            currAddr++;
            *currAddr = -courseSin;
            currAddr++;
            *currAddr = 0.0;
            currAddr++;
            *currAddr = courseCos;

            return 0;
        }

        case HORIZONTED_TO_CONNECTED_CS: {
            double pitchSin = sin( *angles);
            double pitchCos = cos( *angles);
            double rollSin = sin( *( angles + 1));
            double rollCos = cos( *( angles + 1));

            double *currAddr = res;
            *currAddr = pitchCos;
            currAddr++;
            *currAddr = pitchSin;
            currAddr++;
            *currAddr = 0.0;

            currAddr++;
            *currAddr = -pitchSin * rollCos;
            currAddr++;
            *currAddr = pitchCos * rollCos;
            currAddr++;
            *currAddr = rollSin;

            currAddr++;
            *currAddr = pitchSin * rollSin;
            currAddr++;
            *currAddr = -pitchCos * rollSin;
            currAddr++;
            *currAddr = rollCos;

            return 0;
        }

        case CONNECTED_TO_HORIZONTED_CS: {
            double pitchSin = sin( *angles);
            double pitchCos = cos( *angles);
            double rollSin = sin( *( angles + 1));
            double rollCos = cos( *( angles + 1));

            double *currAddr = res;
            *currAddr = pitchCos;
            currAddr++;
            *currAddr = -pitchSin * rollCos;
            currAddr++;
            *currAddr = pitchSin * rollSin;

            currAddr++;
            *currAddr = pitchSin;
            currAddr++;
            *currAddr = pitchCos * rollCos;
            currAddr++;
            *currAddr = -pitchCos * rollSin;

            currAddr++;
            *currAddr = 0.0;
            currAddr++;
            *currAddr = rollSin;
            currAddr++;
            *currAddr = rollCos;

            return 0;
        }

        case NORMAL_TO_CONNECTED_CS: {
            double pitchSin = sin( *angles);
            double pitchCos = cos( *angles);
            double courseSin = sin( *( angles + 1));
            double courseCos = cos( *( angles + 1));
            double rollSin = sin( *( angles + 2));
            double rollCos = cos( *( angles + 2));

            double *currAddr = res;
            *currAddr = courseCos * pitchCos;
            currAddr++;
            *currAddr = pitchSin;
            currAddr++;
            *currAddr = courseSin * pitchCos;

            currAddr++;
            *currAddr = -courseCos * pitchSin * rollCos - courseSin * rollSin;
            currAddr++;
            *currAddr = pitchCos * rollCos;
            currAddr++;
            *currAddr = -courseSin * pitchSin * rollCos + courseCos * rollSin;

            currAddr++;
            *currAddr = courseCos * pitchSin * rollSin - courseSin * rollCos;
            currAddr++;
            *currAddr = -pitchCos * rollSin;
            currAddr++;
            *currAddr = courseSin * pitchSin * rollSin + courseCos * rollCos;

            return 0;
        }

        case CONNECTED_TO_NORMAL_CS: {
            double pitchSin = sin( *angles);
            double pitchCos = cos( *angles);
            double courseSin = sin( *( angles + 1));
            double courseCos = cos( *( angles + 1));
            double rollSin = sin( *( angles + 2));
            double rollCos = cos( *( angles + 2));

            double *currAddr = res;
            *currAddr = courseCos * pitchCos;
            currAddr++;
            *currAddr = -courseCos * pitchSin * rollCos - courseSin * rollSin;
            currAddr++;
            *currAddr = courseCos * pitchSin * rollSin - courseSin * rollCos;

            currAddr++;
            *currAddr = pitchSin;
            currAddr++;
            *currAddr = pitchCos * rollCos;
            currAddr++;
            *currAddr = -pitchCos * rollSin;

            currAddr++;
            *currAddr = courseSin * pitchCos;
            currAddr++;
            *currAddr = -courseSin * pitchSin * rollCos + courseCos * rollSin;
            currAddr++;
            *currAddr = courseSin * pitchSin * rollSin + courseCos * rollCos;

            return 0;
        }

        case TRAJECTORY_TO_CONNECTED_CS: {
            return 0;
        }

        case CONNECTED_TO_TRAJECTORY_CS: {
            return 0;
        }

        case CONNECTED_TO_BEAM_Z_UP_Y_LEFT_CS: {
            double phiYsin = sin( *angles);
            double phiYcos = cos( *angles);
            double phiZsin = sin( *( angles + 1));
            double phiZcos = cos( *( angles + 1));

            double *currAddr = res;
            *currAddr = phiZcos * phiYcos;
            currAddr++;
            *currAddr = phiZsin * phiYcos;
            currAddr++;
            *currAddr = -phiYsin;

            currAddr++;
            *currAddr = -phiZsin;
            currAddr++;
            *currAddr = phiZcos;
            currAddr++;
            *currAddr = 0.0;

            currAddr++;
            *currAddr = phiZcos * phiYsin;
            currAddr++;
            *currAddr = phiZsin * phiYsin;
            currAddr++;
            *currAddr = phiYcos;

            return 0;
        }

        case BEAM_Z_UP_Y_LEFT_TO_CONNECTED_CS: {
            double phiYsin = sin( *angles);
            double phiYcos = cos( *angles);
            double phiZsin = sin( *( angles + 1));
            double phiZcos = cos( *( angles + 1));

            double *currAddr = res;
            *currAddr = phiZcos * phiYcos;
            currAddr++;
            *currAddr = -phiZsin;
            currAddr++;
            *currAddr = phiZcos * phiYsin;

            currAddr++;
            *currAddr = phiZsin * phiYcos;
            currAddr++;
            *currAddr = phiZcos;
            currAddr++;
            *currAddr = phiZsin * phiYsin;

            currAddr++;
            *currAddr = -phiYsin;
            currAddr++;
            *currAddr = 0.0;
            currAddr++;
            *currAddr = phiYcos;

            return 0;
        }

        case CONNECTED_TO_BEAM_Y_LEFT_Z_UP_CS: {
            double phiYsin = sin( *angles);
            double phiYcos = cos( *angles);
            double phiZsin = sin( *( angles + 1));
            double phiZcos = cos( *( angles + 1));

            double *currAddr = res;
            *currAddr = phiYcos * phiZcos;
            currAddr++;
            *currAddr = phiZsin;
            currAddr++;
            *currAddr = -phiYsin * phiZcos;

            currAddr++;
            *currAddr = -phiYcos * phiZsin;
            currAddr++;
            *currAddr = phiZcos;
            currAddr++;
            *currAddr = phiYsin * phiZsin;

            currAddr++;
            *currAddr = phiYsin;
            currAddr++;
            *currAddr = 0.0;
            currAddr++;
            *currAddr = phiYcos;

            return 0;
        }

        case BEAM_Y_LEFT_Z_UP_TO_CONNECTED_CS: {
            double phiYsin = sin( *angles);
            double phiYcos = cos( *angles);
            double phiZsin = sin( *( angles + 1));
            double phiZcos = cos( *( angles + 1));

            double *currAddr = res;
            *currAddr = phiYcos * phiZcos;
            currAddr++;
            *currAddr = -phiYcos * phiZsin;
            currAddr++;
            *currAddr = phiYsin;

            currAddr++;
            *currAddr = phiZsin;
            currAddr++;
            *currAddr = phiZcos;
            currAddr++;
            *currAddr = 0.0;

            currAddr++;
            *currAddr = -phiYsin * phiZcos;
            currAddr++;
            *currAddr = phiYsin * phiZsin;
            currAddr++;
            *currAddr = phiYcos;

            return 0;
        }

        default:
            return 1;
        }
    }

    return 1;
}

#endif

//#endif

