/*
 * Library for USB automated driver installation
 * Copyright (c) 2010-2017 Pete Batard <pete@akeo.ie>
 * Parts of the code from libusb by Daniel Drake, Johannes Erdfelt et al.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
#pragma once
#include <windows.h>

/*
 * Maximum length for any string used by libwdi structures
 */
#define WDI_MAX_STRLEN		200

#if defined(DLL_EXPORT)
#define LIBWDI_EXP __declspec(dllexport)
#else
#define LIBWDI_EXP
#endif

/*
 * Set the default calling convention to WINAPI (__stdcall)
 */
#if !defined(LIBWDI_API)
#define LIBWDI_API WINAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Log level
 */
enum wdi_log_level {
	WDI_LOG_LEVEL_DEBUG,
	WDI_LOG_LEVEL_INFO,
	WDI_LOG_LEVEL_WARNING,
	WDI_LOG_LEVEL_ERROR,
	WDI_LOG_LEVEL_NONE
};

/*
 * Error codes. Most libwdi functions return 0 on success or one of these
 * codes on failure.
 * You can use wdi_strerror() to retrieve a short string description of
 * a wdi_error enumeration value.
 */
enum wdi_error {
	/** Success (no error) */
	WDI_SUCCESS = 0,

	/** Input/output error */
	WDI_ERROR_IO = -1,

	/** Invalid parameter */
	WDI_ERROR_INVALID_PARAM = -2,

	/** Access denied (insufficient permissions) */
	WDI_ERROR_ACCESS = -3,

	/** No such device (it may have been disconnected) */
	WDI_ERROR_NO_DEVICE = -4,

	/** Entity not found */
	WDI_ERROR_NOT_FOUND = -5,

	/** Resource busy, or API call already running */
	WDI_ERROR_BUSY = -6,

	/** Operation timed out */
	WDI_ERROR_TIMEOUT = -7,

	/** Overflow */
	WDI_ERROR_OVERFLOW = -8,

	/** Another installation is pending */
	WDI_ERROR_PENDING_INSTALLATION = -9,

	/** System call interrupted (perhaps due to signal) */
	WDI_ERROR_INTERRUPTED = -10,

	/** Could not acquire resource (Insufficient memory, etc) */
	WDI_ERROR_RESOURCE = -11,

	/** Operation not supported or unimplemented on this platform */
	WDI_ERROR_NOT_SUPPORTED = -12,

	/** Entity already exists */
	WDI_ERROR_EXISTS = -13,

	/** Cancelled by user */
	WDI_ERROR_USER_CANCEL = -14,

	/** Couldn't run installer with required privileges */
	WDI_ERROR_NEEDS_ADMIN = -15,

	/** Attempted to run the 32 bit installer on 64 bit */
	WDI_ERROR_WOW64 = -16,

	/** Bad inf syntax */
	WDI_ERROR_INF_SYNTAX = -17,

	/** Missing cat file */
	WDI_ERROR_CAT_MISSING = -18,

	/** System policy prevents the installation of unsigned drivers */
	WDI_ERROR_UNSIGNED = -19,

	/** Other error */
	WDI_ERROR_OTHER = -99

	/** IMPORTANT: when adding new values to this enum, remember to
	   update the wdi_strerror() function implementation! */
};

/*
 * Set the log verbosity
 */
LIBWDI_EXP int LIBWDI_API wdi_set_log_level(int level);

/*
 * Set the Windows callback message for log notification
 */
LIBWDI_EXP int LIBWDI_API wdi_register_logger(HWND hWnd, UINT message, DWORD buffsize);

/*
 * Unset the Windows callback message for log notification
 */
LIBWDI_EXP int LIBWDI_API wdi_unregister_logger(HWND hWnd);

/*
 * Read a log message after a log notification
 */
LIBWDI_EXP int LIBWDI_API wdi_read_logger(char* buffer, DWORD buffer_size, DWORD* message_size);

#ifdef __cplusplus
}
#endif
