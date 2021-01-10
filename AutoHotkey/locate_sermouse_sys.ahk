FullPathFilename := "C:\Windows\System32\drivers\sermouse.sys"
Explorer := "explorer /select," . FullPathFilename
Run, %Explorer%

; References:
; https://stackoverflow.com/questions/37102222/ahk-code-to-locate-the-residing-folder-and-highlight-the-active-file
; https://autohotkey.com/board/topic/62884-can-ahk-find-files/
; https://stackoverflow.com/questions/54684467/ahk-script-to-find-in-the-current-folder-a-file-or-a-folder-with-the-latest-chan
