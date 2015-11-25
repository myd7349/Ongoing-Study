// 2015-11-18T10:01+08:00
#pragma once

#include "MagInstance.h"

namespace Mag
{
class MagSnapshot : public MagInstance
{
public:
    ~MagSnapshot();

    virtual void Draw(Gdiplus::Graphics &graphics, const POINT &ptCur);

private:
};
} // namespace Mag
