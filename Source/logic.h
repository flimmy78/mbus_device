#ifndef LOGIC_H
#define LOGIC_H

#include "user.h"

extern U8 logic_radioMeterAddr(U8* meterAddr);
extern U8 logic_saveConfig(U8 device, U32 baud, U8 mode, U8 meterType, U8 valveType);
#endif
