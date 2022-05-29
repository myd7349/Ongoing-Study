\_setmode

- https://github.com/microsoft/vswhere/pull/149
- https://github.com/microsoft/vswhere/blob/develop/src/vswhere.lib/Console.cpp

  ```c
  void Console::Initialize() noexcept
  {
      if (!m_fInitialized)
      {
          if (m_args.get_UTF8())
          {
              static_cast<void>(::_setmode(_fileno(stdout), _O_U8TEXT));
          }
          else if (IsConsole(stdout))
          {
              static_cast<void>(::_setmode(_fileno(stdout), _O_WTEXT));
          }
          else
          {
              char sz[10];
              ::sprintf_s(sz, ".%u", ::GetConsoleCP());
  
              ::setlocale(LC_CTYPE, sz);
          }
  
          m_fColorSupported = IsVirtualTerminal(stdout);
          m_fInitialized = true;
      }
  }
  ```
