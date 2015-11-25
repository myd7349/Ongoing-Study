// 2015-11-11T11:39+08:00
#pragma once

#include "Common/GdiplusHelper.h"

namespace Mag
{
class MagInstance : private Utility::GdiplusConsumer
{
public:
    virtual ~MagInstance() {}

    virtual void Draw(Gdiplus::Graphics &graphics, const POINT &ptCur) = 0;
};
} // namespace Mag
