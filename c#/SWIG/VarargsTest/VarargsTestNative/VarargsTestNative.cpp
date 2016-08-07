#include "VarargsTestNative.h"

#include <cassert>
#include <cstdarg>

unsigned WrapAllLeads(std::vector<const int *> &leads, const int *lead0, va_list args)
{
    assert(lead0 != nullptr);
    if (lead0 == nullptr)
        return 0;

    leads.clear();
    leads.push_back(lead0);

    unsigned leadCount = 1;

    while (true)
    {
        const int *lead = va_arg(args, const int *);
        if (lead == nullptr)
            break;

        leads.push_back(lead);
        ++leadCount;
    }

    return leadCount;
}

bool RetrieveASamplingFromMultiLeadsData(std::vector<int>& aSampling, unsigned pos, unsigned dataLength, const std::vector<const int *> &leads)
{
    bool ok = !(0 == dataLength || pos >= dataLength || leads.empty());
    assert(ok);
    if (!ok)
        return false;

    auto leadCount = leads.size();
    aSampling.resize(leadCount);
    for (auto i = 0; i < aSampling.size(); ++i)
    {
        assert(leads[i] != nullptr);
        aSampling[i] = leads[i][pos];
    }

    return true;
}

bool RetrieveASamplingFromMultiLeadsData(std::vector<int>& aSampling, unsigned pos, unsigned dataLength, const int * lead0, va_list args)
{
    std::vector<const int *> leads;
    WrapAllLeads(leads, lead0, args);
    return RetrieveASamplingFromMultiLeadsData(aSampling, pos, dataLength, leads);
}

bool RetrieveASamplingFromMultiLeadsData(std::vector<int>& aSampling, unsigned pos, unsigned dataLength, const int * lead0, ...)
{
    va_list args;
    va_start(args, lead0);
    bool res = RetrieveASamplingFromMultiLeadsData(aSampling, pos, dataLength, lead0, args);
    va_end(args);
    return res;
}


