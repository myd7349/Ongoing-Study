#include "AccelHelper.h"

#include "../../../bitsutils.hpp"
#include "VkHelper.h"


bool IsValidAccelModifiers(WORD wAccelModifiers)
{
    return ClearBits(wAccelModifiers,
        static_cast<WORD>(FVIRTKEY | FCONTROL | FSHIFT | FALT)) == 0;
}

bool IsValidAccel(ACCEL accel)
{
    return VkUtils::IsKnownVkCode(accel.key)
        && !VkUtils::IsModifier(accel.key)
        && IsValidAccelModifiers(accel.fVirt);
}
