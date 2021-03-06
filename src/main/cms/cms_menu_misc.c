/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Betaflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "platform.h"

#ifdef USE_CMS

#include "build/version.h"

#include "cms/cms.h"
#include "cms/cms_types.h"
#include "cms/cms_menu_ledstrip.h"

#include "common/utils.h"

#include "config/config.h"
#include "config/feature.h"

#include "drivers/time.h"

#include "fc/rc_controls.h"

#include "flight/mixer.h"

#include "pg/motor.h"
#include "pg/pg.h"
#include "pg/pg_ids.h"
#include "pg/rx.h"

#include "rx/rx.h"

#include "sensors/battery.h"

#include "cms_menu_misc.h"

//
// Misc
//

static const void *cmsx_menuRcOnEnter(displayPort_t *pDisp)
{
    UNUSED(pDisp);

    inhibitSaveMenu();

    return NULL;
}

static const void *cmsx_menuRcConfirmBack(displayPort_t *pDisp, const OSD_Entry *self)
{
    UNUSED(pDisp);

    if (self && self->type == OME_Back) {
        return NULL;
    } else {
        return MENU_CHAIN_BACK;
    }
}

//
// RC preview
//
static const OSD_Entry cmsx_menuRcEntries[] =
{
    { "-- RC PREV --", OME_Label, NULL, NULL, 0},

    { "ROLL",  OME_INT16, NULL, &(OSD_INT16_t){ &rcData[ROLL],     1, 2500, 0 }, DYNAMIC },
    { "PITCH", OME_INT16, NULL, &(OSD_INT16_t){ &rcData[PITCH],    1, 2500, 0 }, DYNAMIC },
    { "THR",   OME_INT16, NULL, &(OSD_INT16_t){ &rcData[THROTTLE], 1, 2500, 0 }, DYNAMIC },
    { "YAW",   OME_INT16, NULL, &(OSD_INT16_t){ &rcData[YAW],      1, 2500, 0 }, DYNAMIC },

    { "AUX1",  OME_INT16, NULL, &(OSD_INT16_t){ &rcData[AUX1],     1, 2500, 0 }, DYNAMIC },
    { "AUX2",  OME_INT16, NULL, &(OSD_INT16_t){ &rcData[AUX2],     1, 2500, 0 }, DYNAMIC },
    { "AUX3",  OME_INT16, NULL, &(OSD_INT16_t){ &rcData[AUX3],     1, 2500, 0 }, DYNAMIC },
    { "AUX4",  OME_INT16, NULL, &(OSD_INT16_t){ &rcData[AUX4],     1, 2500, 0 }, DYNAMIC },

    { "BACK",  OME_Back, NULL, NULL, 0},
    {NULL, OME_END, NULL, NULL, 0}
};

CMS_Menu cmsx_menuRcPreview = {
#ifdef CMS_MENU_DEBUG
    .GUARD_text = "XRCPREV",
    .GUARD_type = OME_MENU,
#endif
    .onEnter = cmsx_menuRcOnEnter,
    .onExit = cmsx_menuRcConfirmBack,
    .onDisplayUpdate = NULL,
    .entries = cmsx_menuRcEntries
};

static uint16_t motorConfig_minthrottle;

static const void *cmsx_menuMiscOnEnter(displayPort_t *pDisp)
{
    UNUSED(pDisp);

    motorConfig_minthrottle = motorConfig()->minthrottle;

    return NULL;
}

static const void *cmsx_menuMiscOnExit(displayPort_t *pDisp, const OSD_Entry *self)
{
    UNUSED(pDisp);
    UNUSED(self);

    motorConfigMutable()->minthrottle = motorConfig_minthrottle;

    return NULL;
}

static const OSD_Entry menuMiscEntries[]=
{
    { "-- MISC --", OME_Label, NULL, NULL, 0 },

    { "MIN THR",       OME_UINT16,  NULL,          &(OSD_UINT16_t){ &motorConfig_minthrottle,            1000, 2000, 1 }, REBOOT_REQUIRED },
    { "RC PREV",       OME_Submenu, cmsMenuChange, &cmsx_menuRcPreview, 0},

    { "BACK", OME_Back, NULL, NULL, 0},
    { NULL, OME_END, NULL, NULL, 0}
};

CMS_Menu cmsx_menuMisc = {
#ifdef CMS_MENU_DEBUG
    .GUARD_text = "XMISC",
    .GUARD_type = OME_MENU,
#endif
    .onEnter = cmsx_menuMiscOnEnter,
    .onExit = cmsx_menuMiscOnExit,
    .onDisplayUpdate = NULL,
    .entries = menuMiscEntries
};

#endif // CMS
