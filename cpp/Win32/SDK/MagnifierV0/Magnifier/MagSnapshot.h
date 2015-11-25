// 2015-11-18T10:01+08:00
#pragma once

#include "MagInstance.h"

#include <memory>

namespace Mag
{
namespace Utility { class Canvas; }

class MagSnapshot : public MagInstance
{
public:
    MagSnapshot();

    virtual void Draw(HDC hdc, const RECT &rcDest, const RECT &rcMag);

private:
    std::unique_ptr<Utility::Canvas> m_ScreenCache;
};
} // namespace Mag
