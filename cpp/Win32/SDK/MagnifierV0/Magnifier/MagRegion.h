// 2015-11-11T11:39+08:00
#pragma once

#include <memory>

namespace Mag
{

class Region
{
public:
    virtual ~Region() {}

    virtual void Draw(HDC hdc, const RECT &rcDest, const RECT &rcMag) = 0;
};


class DynamicRegion : public Region
{
public:    
    virtual void Draw(HDC hdc, const RECT &rcDest, const RECT &rcMag);
};


namespace Utility { class Canvas; }

class SnapshotRegion : public Region
{
public:
    SnapshotRegion();

    virtual void Draw(HDC hdc, const RECT &rcDest, const RECT &rcMag);

private:
    std::unique_ptr<Utility::Canvas> m_ScreenCache;
};

} // namespace Mag
