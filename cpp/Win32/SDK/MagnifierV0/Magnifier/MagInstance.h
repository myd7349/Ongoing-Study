// 2015-11-11T11:39+08:00
#pragma once

#include "Common/GdiplusHelper.h"

namespace Mag
{
class MagInstance : private Utility::GdiplusConsumer
{
public:
    virtual ~MagInstance() {}

    virtual void Draw(HDC hdc, const RECT &rcDest, const RECT &rcMag) = 0;
};
} // namespace Mag
