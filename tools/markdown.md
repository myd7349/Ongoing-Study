1 [Diff syntax highlighting in Github Markdown](https://stackoverflow.com/questions/40883421/diff-syntax-highlighting-in-github-markdown)

```diff
diff --git a/CMakeLists.txt b/CMakeLists.txt
index d6f75cf..1d2cfdf 100755
--- a/CMakeLists.txt
+++ b/CMakeLists.txt
@@ -7,7 +7,7 @@ if(APPLE)
        set(WEBVIEW_LIBS "-framework WebKit")
 elseif(WIN32)
        set(WEBVIEW_COMPILE_DEFS "-DWEBVIEW_WINAPI=1")
-       set(WEBVIEW_LIBS "ole32 comctl32 oleaut32 uuid")
+       set(WEBVIEW_LIBS ole32 comctl32 oleaut32 uuid)
 else()
        set(WEBVIEW_COMPILE_DEFS "-DWEBVIEW_GTK=1")
        find_package(PkgConfig REQUIRED)

```

2 [TODO List](https://github.com/itchio/capsule/blob/master/README.md)

### Linux

  * Control
    * [x] X11 recording hotkey support (hardcoded to F9)
  * Video
    * [x] OpenGL capture
    * [ ] Vulkan capture

3 https://github.com/guodongxiaren/README

4 [How do I display local image in markdown?](https://stackoverflow.com/questions/41604263/how-do-i-display-local-image-in-markdown)

Softwares:

- Typora
- [Notable](https://github.com/notable/notable)
- [Obsidian](https://obsidian.md/)
- [turndown](https://github.com/mixmark-io/turndown)

Libraries:

- [milkdown](https://github.com/Saul-Mirone/milkdown)
- [MdXaml](https://github.com/whistyun/MdXaml)

Tools:

- [htmldoc](https://github.com/michaelrsweet/htmldoc)

