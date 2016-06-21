// 2016-06-21T13:49+08:00
#pragma once

#include <string>

struct Message {
    std::wstring message;
};

class Person {
public:
    void Say(const std::wstring &what) const;
    void Say(const Message &msg) const;
};