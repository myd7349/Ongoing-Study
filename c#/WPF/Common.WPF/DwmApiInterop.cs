﻿/* 
 * Copyright (c) 2011, 2012 NOVALISTIC
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

using System;
using System.Runtime.InteropServices;
using System.Security;

namespace Common.WPF
{
	#region Structures

	/// <summary>
	/// Defines a structure containing margin dimensions.
	/// </summary>
	[StructLayout(LayoutKind.Sequential)]
	public struct MARGINS
	{
		public int cxLeftWidth,
			cxRightWidth,
			cyTopHeight,
			cyBottomHeight;
	}

	#endregion

	public static class DwmApiInterop
	{
		#region Constants

		public const int HTCLIENT = 0x1;
		public const int HTCAPTION = 0x2;

		public const int WM_NCHITTEST = 0x84;
		public const int WM_DWMCOMPOSITIONCHANGED = 0x31E;

		#endregion

		#region Helper methods

		/// <summary>
		/// Determines whether the cursor is on the client area.
		/// </summary>
		/// <param name="hWnd">The window handle that is receiving and processing the window message.</param>
		/// <param name="uMsg">The window message.</param>
		/// <param name="wParam">Additional message information.</param>
		/// <param name="lParam">Additional message information.</param>
		/// <returns>true if the cursor is on the client area; otherwise, false.</returns>
		public static bool IsOnClientArea(IntPtr hWnd, int uMsg, IntPtr wParam, IntPtr lParam)
		{
			if (uMsg == WM_NCHITTEST)
			{
				if (DefWindowProc(hWnd, uMsg, wParam, lParam).ToInt32() == HTCLIENT)
				{
					return true;
				}
			}

			return false;
		}

		#endregion

		#region Managed wrapper methods

		/// <summary>
		/// Determines whether desktop composition is enabled on the client system.
		/// </summary>
		/// <returns>true if desktop composition is enabled; otherwise, false.</returns>
		public static bool IsCompositionEnabled()
		{
			bool isEnabled = false;
			NativeMethods.DwmIsCompositionEnabled(ref isEnabled);
			return isEnabled;
		}

		/// <summary>
		/// Extends the window frame into the client area.
		/// </summary>
		/// <param name="hWnd">The window handle whose client area to extend the window frame into.</param>
		/// <param name="margins">The amount of window frame to extend around the client area.</param>
		/// <returns>S_OK on success; otherwise, an HRESULT error code.</returns>
		public static int ExtendFrameIntoClientArea(IntPtr hWnd, ref MARGINS margins)
		{
			return NativeMethods.DwmExtendFrameIntoClientArea(hWnd, ref margins);
		}

		/// <summary>
		/// Invokes the default window message procedure for the given window handle.
		/// </summary>
		/// <param name="hWnd">The window handle that is receiving and processing the window message.</param>
		/// <param name="uMsg">The window message.</param>
		/// <param name="wParam">Additional message information.</param>
		/// <param name="lParam">Additional message information.</param>
		/// <returns>The result of the message processing, which depends on the message.</returns>
		public static IntPtr DefWindowProc(IntPtr hWnd, int uMsg, IntPtr wParam, IntPtr lParam)
		{
			return NativeMethods.DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

		#endregion
	}

	[SuppressUnmanagedCodeSecurity]
	internal static class NativeMethods
	{
		[DllImport("dwmapi.dll")]
		internal static extern void DwmIsCompositionEnabled(ref bool isEnabled);

		[DllImport("dwmapi.dll")]
		internal static extern int DwmExtendFrameIntoClientArea(IntPtr hWnd, ref MARGINS margins);

		[DllImport("user32.dll")]
		internal static extern IntPtr DefWindowProc(IntPtr hWnd, int uMsg, IntPtr wParam, IntPtr lParam);
	}
}
