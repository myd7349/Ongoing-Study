// 2015-11-26T11:11+08:00
#pragma once

#include <WinDef.h>


namespace Mag
{

class HostWnd
{
public:
    virtual ~HostWnd() {}
};

class StaticHostWnd : public HostWnd
{
public:
};

class TrackCurHostWnd : public HostWnd
{
public:
};

class DraggableHostWnd : public HostWnd
{
public:
};

} // namespace Mag
