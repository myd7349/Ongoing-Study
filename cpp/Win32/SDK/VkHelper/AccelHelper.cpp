#include "AccelHelper.h"

#include "../../../bitsutils.hpp"
#include "VkHelper.h"


bool IsValidAccelModifiers(WORD wAccelModifiers)
{
    ClearBits(wAccelModifiers, (WORD)FVIRTKEY);
    ClearBits(wAccelModifiers, (WORD)FCONTROL);
    ClearBits(wAccelModifiers, (WORD)FSHIFT);
    ClearBits(wAccelModifiers, (WORD)FALT);
    return wAccelModifiers == 0;
}

bool IsValidAccel(ACCEL accel)
{
    return VkUtils::IsKnownVkCode(accel.key)
        && !VkUtils::IsModifier(accel.key)
        && IsValidAccelModifiers(accel.fVirt);
}
