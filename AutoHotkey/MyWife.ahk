; 2016-12-16T09:49:10+08:00
; This is my wife. She is good-looking and a good helper.

; Insert the current date time when I tell her "Ctrl+T"
^T::
    FormatTime, CurrentDateTime, , yyyy-MM-ddThh:mm:ss{+}08:00
    Send, %CurrentDateTime%{Return}
Return


; References:
; [Trying to output a plus (+) sign](https://autohotkey.com/board/topic/57114-trying-to-output-a-plus-sign/)