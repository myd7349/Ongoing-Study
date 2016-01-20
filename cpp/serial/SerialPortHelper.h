// 2015-12-15T10:09+08:00
#pragma once

#ifndef SERIAL_API
# define SERIAL_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

// GetSerialPortNumber("Silicon Labs CP210x USB to UART Bridge")
SERIAL_API int GetSerialPortNumber(const char *desc);

#ifdef __cplusplus
}
#endif