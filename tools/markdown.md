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

- [Drafts](https://getdrafts.com/)

- [StackEdit](https://stackedit.io/)

- Typora

- [MarkdownMonster](https://github.com/RickStrahl/MarkdownMonster)

- [marktext](https://github.com/marktext/marktext)

- [milkdowns](https://github.com/Saul-Mirone/milkdown)

- [Notable](https://github.com/notable/notable)

- [Notepads](https://github.com/0x7c13/Notepads)

- [Obsidian](https://obsidian.md/)

- [QOwnNotes](https://github.com/pbek/QOwnNotes)

- [turndown](https://github.com/mixmark-io/turndown)

- [MarkdownViewerPlusPlus](https://github.com/nea/MarkdownViewerPlusPlus)

- [WeChat Markdown Editor](https://github.com/doocs/md)

- [yn](https://github.com/purocean/yn)

- [Zettlr](https://github.com/Zettlr/Zettlr)

Libraries:

- [ByteMD](https://github.com/bytedance/bytemd)

- CommonMarkNet

- [docfx](https://github.com/dotnet/docfx)

  - [MarkdownMonster](https://github.com/RickStrahl/MarkdownMonster) - [issue](https://github.com/RickStrahl/MarkdownMonster/issues/20)

- [hoedown](https://github.com/hoedown/hoedown)

- [imgui_markdown](https://github.com/juliettef/imgui_markdown)

- [markdig](https://github.com/xoofx/markdig)

  - [MarkdownMonster](https://github.com/RickStrahl/MarkdownMonster)

  - [NETworkManager](https://github.com/BornToBeRoot/NETworkManager)

- [markdoc](https://github.com/markdoc/markdoc)

- MarkdownLite

- [milkdown](https://github.com/Saul-Mirone/milkdown)

- [MdXaml](https://github.com/whistyun/MdXaml)

  - [Markdown.Avalonia](https://github.com/whistyun/Markdown.Avalonia)

- [MyST-Parser](https://github.com/executablebooks/MyST-Parser)

- [reversemarkdown](https://github.com/mysticmind/reversemarkdown-net)

  - [MarkdownMonster](https://github.com/RickStrahl/MarkdownMonster)

- [texme](https://github.com/susam/texme)

Tools:

- [DownmarkerWPF](https://github.com/Code52/DownmarkerWPF)
- [htmldoc](https://github.com/michaelrsweet/htmldoc)
- [lint-md](https://github.com/lint-md/lint-md)
- [markdown-it-title](https://github.com/valeriangalliat/markdown-it-title)
- [markdownlint](https://github.com/DavidAnson/markdownlint)
  - [vscode-markdownlint](https://github.com/DavidAnson/vscode-markdownlint)
- [markdown-nice](https://github.com/mdnice/markdown-nice)
- [slidev](https://github.com/slidevjs/slidev)
- [Zettlr](https://github.com/Zettlr/Zettlr)

Online Editors:

- [awesome-web-editor](https://github.com/xjh22222228/awesome-web-editor)

- [EasyMDE](https://github.com/Ionaru/easy-markdown-editor/)

Templates:

- https://github.com/sdsawtelle/markdown-resume

- https://github.com/mszep/pandoc_resume
