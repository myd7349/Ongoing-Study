1. unique_any

   https://github.com/microsoft/wil/blob/2e225973d6c2ecf17fb4d376ddbeedb6db7dd82f/include/wil/resource.h#L4546

   ```c++
   typedef unique_any<HKEY, decltype(&::RegCloseKey), ::RegCloseKey> unique_hkey;
   ```

   and how it is used in [PowerToys](https://github.com/microsoft/PowerToys/blob/d7e09e83c27f8c6f64d149a78a864a8845dd593e/src/modules/fancyzones/FancyZonesLib/VirtualDesktopUtils.cpp#L54-L69):

   ```c++
       bool NewGetCurrentDesktopId(GUID* desktopId)
       {
           wil::unique_hkey key{};
           if (RegOpenKeyExW(HKEY_CURRENT_USER, NonLocalizable::RegKeyVirtualDesktops, 0, KEY_ALL_ACCESS, &key) == ERROR_SUCCESS)
           {
               GUID value{};
               DWORD size = sizeof(GUID);
               if (RegQueryValueExW(key.get(), NonLocalizable::RegCurrentVirtualDesktop, 0, nullptr, reinterpret_cast<BYTE*>(&value), &size) == ERROR_SUCCESS)
               {
                   *desktopId = value;
                   return true;
               }
           }
   
           return false;
       }
   ```

2. [GetProcAddressByFunctionDeclaration](https://github.com/microsoft/wil/blob/2e225973d6c2ecf17fb4d376ddbeedb6db7dd82f/include/wil/win32_helpers.h#L672)

   ```c++
   #define GetProcAddressByFunctionDeclaration(hinst, fn) reinterpret_cast<decltype(::fn)*>(GetProcAddress(hinst, #fn))
   ```

