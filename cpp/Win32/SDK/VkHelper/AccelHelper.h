#ifndef ACCELHELPER_H_
#define ACCELHELPER_H_

#include <functional>

#include "Win32Cmn.h"

bool IsValidAccelModifiers(WORD wAccelModifiers);
bool IsValidAccel(ACCEL accel);

namespace std {
    template <>
    struct hash<ACCEL> {
        size_t operator()(const ACCEL &accel) const {
            return hash<unsigned long>()(MAKELONG(MAKEWORD(accel.fVirt, LOBYTE(accel.key)), LOWORD(accel.cmd)));
        }
    };
}

#endif // ACCELHELPER_H_
