// 2015-11-18T10:01+08:00
#pragma once

#include "MagInstance.h"

namespace Mag
{
class MagDynamic : public MagInstance
{
public:    
    virtual void Draw(HDC hdc, const RECT &rcDest, const RECT &rcMag);
};
} // namespace Mag