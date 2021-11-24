; 2016-12-16T09:49:10+08:00

; Insert the current date time when I tell her "Ctrl+T"
^T::
    FormatTime, CurrentDateTime, , yyyy-MM-ddTHH:mm:ss+08:00
    Clipboard := CurrentDateTime
    SendInput ^v{Return} ; It seems that "^V{Return}" not works as expected.
Return


; Show contents in clipboard
^+C::
    MsgBox %Clipboard%
Return


; References:
; [Trying to output a plus (+) sign](https://autohotkey.com/board/topic/57114-trying-to-output-a-plus-sign/)
; [Send plus sign as text](https://autohotkey.com/board/topic/81964-send-plus-sign-as-text/)