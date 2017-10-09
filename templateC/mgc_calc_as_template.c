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
 ** \author Anton Pasternak, antpaster@gmail.com
 ** \version 1.0
 ** \date 08.09.17
 ** \brief MGC calculations templates realization
 */

#ifdef T
#include <stdlib.h>
#include <math.h>

#include "templates.h"

#ifdef TEMPLATE_LIB

/*! MGC calculations template
 * \param[ out] result Result 3x3 matrix pointer
 * \param[ in] angles Angles for transformation pointer
 * \param[ in] mt type of the coordinate transformation
 ***************************************************************************************************
 * \return 0 - ok, 1 - Null pointer to result or angles
 */
int TEMPLATE( mgc_calc, T) ( T *result, const T *angles, const TmgcTypes mt) {

    if( result && angles) {
        switch( mt) {
        case CONNECTED_TO_SPEED_CS: {
            T attackSin = sin( *angles);
            T attackCos = cos( *angles);
            T slideSin = sin( *( angles + 1));
            T slideCos = cos( *( angles + 1));

            T *currAddr = result;
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
            T attackSin = sin( *angles);
            T attackCos = cos( *angles);
            T slideSin = sin( *( angles + 1));
            T slideCos = cos( *( angles + 1));

            T *currAddr = result;
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
            T courseSin = sin( *angles);
            T courseCos = cos( *angles);

            T *currAddr = result;
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

        case NORMAL_TO_HORIZONTED_CS: {
            T courseSin = sin( *angles);
            T courseCos = cos( *angles);

            T *currAddr = result;
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
            T pitchSin = sin( *angles);
            T pitchCos = cos( *angles);
            T rollSin = sin( *( angles + 1));
            T rollCos = cos( *( angles + 1));

            T *currAddr = result;
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
            T pitchSin = sin( *angles);
            T pitchCos = cos( *angles);
            T rollSin = sin( *( angles + 1));
            T rollCos = cos( *( angles + 1));

            T *currAddr = result;
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
            T pitchSin = sin( *angles);
            T pitchCos = cos( *angles);
            T courseSin = sin( *( angles + 1));
            T courseCos = cos( *( angles + 1));
            T rollSin = sin( *( angles + 2));
            T rollCos = cos( *( angles + 2));

            T *currAddr = result;
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
            T pitchSin = sin( *angles);
            T pitchCos = cos( *angles);
            T courseSin = sin( *( angles + 1));
            T courseCos = cos( *( angles + 1));
            T rollSin = sin( *( angles + 2));
            T rollCos = cos( *( angles + 2));

            T *currAddr = result;
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
            T trajSlopeSin = sin( *angles);
            T trajSlopeCos = cos( *angles);
            T wayAngleSin = sin( *( angles + 1));
            T wayAngleCos = cos( *( angles + 1));

            T *currAddr = result;
            *currAddr = trajSlopeCos * wayAngleCos;
            currAddr++;
            *currAddr = -trajSlopeSin * wayAngleCos;
            currAddr++;
            *currAddr = wayAngleSin;

            currAddr++;
            *currAddr = trajSlopeSin;
            currAddr++;
            *currAddr = trajSlopeCos;
            currAddr++;
            *currAddr = 0.0;

            currAddr++;
            *currAddr = -trajSlopeCos * wayAngleSin;
            currAddr++;
            *currAddr = trajSlopeSin * wayAngleSin;
            currAddr++;
            *currAddr = wayAngleCos;

            return 0;
        }

        case CONNECTED_TO_TRAJECTORY_CS: {
            T trajSlopeSin = sin( *angles);
            T trajSlopeCos = cos( *angles);
            T wayAngleSin = sin( *( angles + 1));
            T wayAngleCos = cos( *( angles + 1));

            T *currAddr = result;
            *currAddr = trajSlopeCos * wayAngleCos;
            currAddr++;
            *currAddr = trajSlopeSin;
            currAddr++;
            *currAddr = -trajSlopeCos * wayAngleSin;

            currAddr++;
            *currAddr = -trajSlopeSin * wayAngleCos;
            currAddr++;
            *currAddr = trajSlopeCos;
            currAddr++;
            *currAddr = trajSlopeSin * wayAngleSin;

            currAddr++;
            *currAddr = wayAngleSin;
            currAddr++;
            *currAddr = 0.0;
            currAddr++;
            *currAddr = wayAngleCos;

            return 0;
        }

        case CONNECTED_TO_BEAM_Z_UP_Y_LEFT_CS: {
            T phiYsin = sin( *angles);
            T phiYcos = cos( *angles);
            T phiZsin = sin( *( angles + 1));
            T phiZcos = cos( *( angles + 1));

            T *currAddr = result;
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
            T phiYsin = sin( *angles);
            T phiYcos = cos( *angles);
            T phiZsin = sin( *( angles + 1));
            T phiZcos = cos( *( angles + 1));

            T *currAddr = result;
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
            T phiYsin = sin( *angles);
            T phiYcos = cos( *angles);
            T phiZsin = sin( *( angles + 1));
            T phiZcos = cos( *( angles + 1));

            T *currAddr = result;
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
            T phiYsin = sin( *angles);
            T phiYcos = cos( *angles);
            T phiZsin = sin( *( angles + 1));
            T phiZcos = cos( *( angles + 1));

            T *currAddr = result;
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

#endif

