1. is_same_v

   https://github.com/s9w/oof#performance--os-specific-details

   ```c++
   template<typename char_type>
   auto fast_print(const std::basic_string<char_type>& sss) -> void
   {
      HANDLE const output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
      const auto char_count = static_cast<DWORD>(sss.length());
      if constexpr (std::is_same_v<char_type, char>)
         WriteConsoleA(output_handle, sss.c_str(), char_count, nullptr, nullptr);
      else
         WriteConsoleW(output_handle, sss.c_str(), char_count, nullptr, nullptr);
   }
   ```

   