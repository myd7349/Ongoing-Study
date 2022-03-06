#include "Stopwatch.h"


Stopwatch::InternalData::InternalData()
{
    if (QueryPerformanceFrequency(&Frequency))
    {
        IsHighResolution = true;
        TickFrequency = static_cast<long double>(TicksPerSecond) / Frequency.QuadPart;
    }
    else
    {
        IsHighResolution = false;
        Frequency.QuadPart = TicksPerSecond;
        TickFrequency = 1.0;
    }
}


Stopwatch::InternalData Stopwatch::internalData_;


// References:
// https://github.com/pocoproject/poco/blob/master/Foundation/src/Stopwatch.cpp
/*
// http://www.cppblog.com/lingjingqiu/archive/2005/11/30/1435.html
struct Timer{
    void GetTime(__int64* ptime)
    {
        //QueryPerformanceCounter((LARGE_INTEGER*)ptime);
        __asm
        {
            push edx;
            push ecx;
            mov ecx,ptime;
            rdtsc
                mov [ecx],eax;
            mov [ecx+4],edx;
            pop ecx;
            pop edx;
        }
    }
};

Timer g_timer;

struct ProfilerSample
{
    __int64 begin;
    __int64 end;
    __int64 count;
    __int64 total;

    ProfilerSample() : begin(0), end(0), count(0), total(0)
    {}

    void Reset() {
        begin = end = count = total = 0;
    }

    void Begin() {
        g_timer.GetTime(&begin);
    }

    void End() {
        g_timer.GetTime(&end);
        total += (end - begin);
    }
};

class ProfilerNode
{
public:
    ProfilerNode* m_parent;
    ProfilerNode* m_son;
    ProfilerNode* m_sibling;

    const char* m_profName;

    ProfilerSample m_sample;

public:
    ProfilerNode(const char* name, ProfilerNode* parent);
    ~ProfilerNode();

    void Begin();
    void End();

    const char* GetName();
    const ProfilerSample* GetProfSample();

    ProfilerNode* GetSon(const char* str);
    ProfilerNode* GetDirectSon();
    ProfilerNode* GetNextSibling();
    ProfilerNode* GetParent();
};

ProfilerNode::ProfilerNode(const char* name, ProfilerNode* parent)
    : m_profName(name), m_parent(parent), m_son(NULL), m_sibling(NULL)
{
}

ProfilerNode::~ProfilerNode()
{
    delete m_son;
    delete m_sibling;
}

const char* ProfilerNode::GetName()
{
    return m_profName;
}

const ProfilerSample* ProfilerNode::GetProfSample()
{
    return &m_sample;
}

//获取一个儿子
ProfilerNode* ProfilerNode::GetSon(const char* str)
{
    ProfilerNode* p = m_son;

    while(p != NULL) {
        if(p->m_profName == str) {
            break;
        }
        p = p->GetNextSibling();
    }

    if(p == NULL)
    {
        p = new ProfilerNode(str, this);
        p->m_sibling = m_son;
        m_son = p;
    }

    return p;
}

//获取一个儿子
ProfilerNode* ProfilerNode::GetDirectSon()
{
    return m_son;
}

ProfilerNode* ProfilerNode::GetNextSibling()
{
    return m_sibling;
}

ProfilerNode* ProfilerNode::GetParent()
{
    return m_parent;
}

void ProfilerNode::Begin()
{
    m_sample.Begin();
}

void ProfilerNode::End()
{
    m_sample.End();
}

//性能分析管理器
//注意初始化顺序！
class ProfilerManager
{
private:
    ProfilerManager() : root("root", NULL), m_curProfNode(&root){}
    ProfilerManager(const ProfilerManager& rhs);
    ProfilerManager&  operator = (const ProfilerManager& rhs);

    static ProfilerManager s_profmgr;

private:
    ProfilerNode root;
    ProfilerNode* m_curProfNode;

public:
    static ProfilerManager& Instance() {
        return s_profmgr;
    }

    void BeginProfiler(const char* name);
    void EndProfiler();

    ProfilerNode* GetRootProfilerNode() {
        return &root;
    }
};

ProfilerManager ProfilerManager::s_profmgr;

void ProfilerManager::BeginProfiler(const char* name)
{
    m_curProfNode = m_curProfNode->GetSon(name);
    m_curProfNode->Begin();
}

void ProfilerManager::EndProfiler()
{
    m_curProfNode->End();
    m_curProfNode = m_curProfNode->GetParent();
}

class Profiler
{
public:
    Profiler(const char* name)
    {
        ProfilerManager::Instance().BeginProfiler(name);
    }
    ~Profiler()
    {
        ProfilerManager::Instance().EndProfiler();
    }
};

#define BEGIN_PROF(name) ProfilerManager::Instance().BeginProfiler(name);
#define END_PROF(name) ProfilerManager::Instance().EndProfiler();

LARGE_INTEGER j;

void OutputProf(ProfilerNode* p, int space = 0)
{
    ProfilerNode* tmp;

    const ProfilerSample* ps = p->GetProfSample();
    for(int i = 0; i < space; ++i) {
        cout << " ";
    }
    cout << p->GetName() << ": 调用次数: " << ps->count << " 调用总耗时: " << ps->total << endl;

    if(tmp = p->GetDirectSon()) {
        OutputProf(tmp, space+1);
    } else {
        if(tmp = p->GetNextSibling()) {
            OutputProf(tmp, space);
        }
    }
}
*/
