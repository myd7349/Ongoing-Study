// 2015-12-03T10:56+08:00
#pragma once

#ifndef _MSC_VER
# error A MSVC-compatible compiler is needed.
#endif

#define RO_PROPERTY_SPEC_(getter) __declspec(property(get = getter))
#define WO_PROPERTY_SPEC_(setter) __declspec(property(put = setter))
#define RW_PROPERTY_SPEC_(getter, setter) __declspec(property(get = getter, put = setter))

#define RO_PROPERTY_DEF_(T, declarator) RO_PROPERTY_SPEC_(Get##declarator) T declarator
#define WO_PROPERTY_DEF_(T, declarator) WO_PROPERTY_SPEC_(Set##declarator) T declarator
#define RW_PROPERTY_DEF_(T, declarator) RW_PROPERTY_SPEC_(Get##declarator, Set##declarator) T declarator

#define RO_PROPERTY_ACCESSORIES_(T, declarator) T Get##declarator()
#define WO_PROPERTY_ACCESSORIES_(T, declarator) void Set##declarator(T val)
#define RW_PROPERTY_ACCESSORIES_(T, declarator) T Get##declarator(); void Set##declarator(T val)

#define PROPERTY_IMPL_(attr, T, declarator) \
    attr##_PROPERTY_DEF_(T, declarator); \
    attr##_PROPERTY_ACCESSORIES_(T, declarator);

#define RO_PROPERTY(T, declarator) PROPERTY_IMPL_(RO, T, declarator)
#define WO_PROPERTY(T, declarator) PROPERTY_IMPL_(WO, T, declarator)
#define RW_PROPERTY(T, declarator) PROPERTY_IMPL_(RW, T, declarator)

#define PROPERTY_GETTER(cls, T, declarator) T cls::Get##declarator()
#define PROPERTY_SETTER(cls, T, declarator, v) void cls::Set##declarator(T v)
