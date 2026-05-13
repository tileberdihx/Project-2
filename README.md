Object-oriented Programming, Project
====================================

## Developer Tools

* [CLion](https://www.jetbrains.com/clion/download)
* [Git SCM](https://git-scm.com/downloads)

## Libraries

* [Qt 6](https://www.qt.io)

### Installing Qt 6

In this project, you will build a GUI application using the popular library Qt (pronounced "cute"). The lab computers already have Qt installed; however, if you are working on a personal computer, you will need to follow the instructions below to install it for your operating system. It is advisable to do so as soon as possible and to contact your instructors if you encounter any problems. Failure to complete the setup in time may prevent you from finishing and submitting the project by its deadline. Please be aware that no extensions will be granted, and not having the library set up will result in a zero for the project.

#### Windows

1. Download the following [archive](https://drive.google.com/file/d/14iCNNsdpZTj4t9ZNz4Mdi79Hd6pWwuab/view) and extract it to the `C:` drive. Ensure that after extraction there is a directory named `Qt` (`C:\Qt`), and inside it, a directory named `6.10.2` (`C:\Qt\6.10.2`). If you do not trust our package, you can install Qt 6 yourself using the official online [installer](https://www.qt.io/download-open-source). Select version `6.10.2`; install Qt Creator too, do not install any additional components, as the full installation requires significant disk space.
2. Run PowerShell as an administrator. Once open, execute the code below to set global OS variables that will help build tools locate your Qt 6 installation:

```powershell
[System.Environment]::SetEnvironmentVariable("Qt6_DIR", "C:\Qt\6.10.2\mingw_64", "Machine")

$currentPath = [System.Environment]::GetEnvironmentVariable("Path", "Machine")
$newDir = "C:\Qt\6.10.2\mingw_64\bin"
if ($currentPath -notlike "*$newDir*") {
    $updatedPath = "$currentPath;$newDir"
    [System.Environment]::SetEnvironmentVariable("Path", $updatedPath, "Machine")
}
```

#### macOS

1. Install or update the [Homebrew](https://brew.sh) package manager.
2. Install Qt 6 libraries with Homebrew by running `brew install qt6` in the Terminal application.
3. Install Qt 6 Creator IDE with Homebrew by running `brew install --cask qt-creator` in the Terminal application.

#### Ubuntu

1. Install Qt 6 with the system package manager by running `sudo apt install qt6-base-dev libqt6svg6` in the Terminal application.
2. Install Qt Creator IDE by running `sudo apt install qtcreator` in the Terminal application.

---

## Important Notes

The project will be graded during a live demo. You will walk the instructor through your implementation, explain design decisions, and answer questions about your code.

Ensure your code style is consistent: indent code properly, separate logical blocks with a blank line, and use variable names that follow a consistent naming style and concisely describe the data they store. The code style for all files must conform to the configuration in `.clang-format`. By default, `.clang-format` is set to the WebKit style; see the [WebKit Code Style Guidelines](https://webkit.org/code-style-guidelines) for details. If you prefer a different style, update `.clang-format` accordingly. Ensure that your source files adhere to the selected style. Format your source code manually or use CLion's autoformatting tools. However, we recommend starting with manual formatting to build good programming habits. The project is graded during a live demo, so style is reviewed by the instructor rather than enforced by an automated check.

Your files and directories must be named according to the requirements outlined at the bottom of this page. Moreover, your repository must not contain extraneous files or unrelated code, especially within the folder designated for project tasks.

If you are instructed to use a particular function, you must base your solution on that function, even if a better solution exists without it. Use only language facilities that have been discussed during class.

Remember that this requirements document, the grader file, and any requirements mentioned informally by the instructors during lectures or labs are all considered official and must be followed. Failure to do so may result in lost points. Do not assume that the document below is the only set of rules to follow.

To ensure you are aware of all requirements, attend classes regularly and actively engage with your instructors. If you are unsure about the correct approach, visit office hours to clarify expectations and avoid losing points. If you cannot attend office hours, do not hesitate to reach out to your instructors through other means, such as email.

---

## Project Description

![Base version of Notepad before Extension](https://raw.githubusercontent.com/rachmiroff/images/refs/heads/main/auca/com-119/spring-2026/project/01.png)

Extend the Notepad application, built across Practices 5 to 8 (lab and homework problems combined), into a more capable WordPad-like editor. Your starting point is a functional application that already supports file operations, an `Edit` menu (undo, redo, cut, copy, paste, select all), text case transforms (uppercase, lowercase, capitalize, sentence case, swap case), rich text formatting (bold, italic, underline), find and replace, word frequency analysis, and a status bar with live word and line counts.

You must implement both required features and at least three optional features of your choice.

When you first open the project in CLion, edit the run configuration and set Working Directory to `$ProjectFileDir$` so that relative paths like `data/images/bold.svg` and `data/words.txt` resolve correctly. Otherwise the toolbar icons will not appear at runtime and the spell checker will report every word as misspelled.

The grader matches the main window by its `windowTitle`. Keep `Notepad` as the title when no file is open; the starter `update_title()` switches to `Notepad: <path>` after a file is loaded. The grader accepts any title that begins with `Notepad`, so if you change the format, keep `Notepad` as the prefix. The error dialog from `QMessageBox::critical` must use the title `Error` exactly. Dialog windowTitles `Find / Replace` and `Word Frequency` must also be preserved.

---

## Required Features

### 1. Exception Handling

Integrate the exception hierarchy from Practice #8 into the application:

* Create `notepad_exception.h` with `notepad_exception`, `file_not_found_exception`, `file_read_exception`, and `file_write_exception` (as in Practice #8).
* Wrap `open_file()` and `save_file()` in `try / catch` blocks; display errors with `QMessageBox::critical`.

### 2. Spell Checker

Add a spell checker using the provided `data/words.txt` word list (one word per line). The list is `words_alpha.txt` from [dwyl/english-words](https://github.com/dwyl/english-words), released into the public domain under [The Unlicense](https://github.com/dwyl/english-words/blob/master/LICENSE.md) (370105 lowercase a-z entries).

Requirements:

* Load the word list from `data/words.txt` at startup (read into a `std::set<std::string>` or similar).
* Real-time inline highlighting: misspelled words are underlined in red as you type, using a `QSyntaxHighlighter` subclass with `QTextCharFormat::SpellCheckUnderline`.
* Right-click context menu: right-clicking a misspelled word shows a `QMenu` with up to 5 spelling suggestions; clicking a suggestion replaces the word in the editor.
* Add a `Tools` > `Check Spelling...` menu item that re-runs the highlight pass over the whole document.
* A word is misspelled if, after lowercasing and stripping non-alphabetic characters, it is not found in the word list.

---

## Optional Features

Choose at least three from the table below. More is better.

| # | Feature                        | Description                                                                                    |
|---|--------------------------------|------------------------------------------------------------------------------------------------|
| 1 | Cursor line / column indicator | Add current cursor line and column to the existing status bar                                  |
| 2 | Font dialog                    | `Format` > `Font...` opens `QFontDialog`; applies selected font to selection or whole document |
| 3 | Color picker                   | `Format` > `Text Color...` opens `QColorDialog`; applies to selection                          |
| 4 | Print                          | `File` > `Print...` opens `QPrintDialog` and prints via `QTextEdit::print()`                   |
| 5 | Recent files                   | `File` > `Recent Files` submenu (last 5 opened files, persisted across sessions)               |
| 6 | Line numbers                   | Display line numbers in a margin beside the editor                                             |
| 7 | Syntax highlight               | Highlight C++ or Python keywords using `QSyntaxHighlighter`                                    |
| 8 | Zoom                           | `View` > `Zoom In` / `Zoom Out` / `Reset Zoom` (`Ctrl++` / `Ctrl+-` / `Ctrl+0`)                |

---

## Deliverables

By the project deadline, push your final code to your GitHub repository. During the demo you must be able to:

1. Build the project from scratch with `cmake -S . -B build && cmake --build build`.
2. Run the application and demonstrate all required and chosen optional features.
3. Explain any class you added, any design decision you made.

In addition, submit a `Notepad.md` file in your repository that describes your implementation: which optional features you chose, why, and how each one works at a high level.

---

## Expected Repository Structure

```
. (.idea, .gitignore, .clang-format, CMakeLists.txt, Readme.md, Notepad.md)
├── main.cpp
├── main_window.h
├── main_window.cpp
├── text_transform.h
├── find_replace_dialog.ui
├── word_frequency_dialog.ui
├── sort.h
├── notepad_exception.h
├── spell_checker.h
├── spell_checker_highlighter.h
├── ...other files you need
└── data/
    ├── words.txt
    └── images/
        ├── bold.svg
        ├── italic.svg
        └── underline.svg
```

Additional `.h`, `.cpp`, and `.ui` files for optional features are welcome.

---

## Documentation

### C++

* `class`: <https://en.cppreference.com/w/cpp/language/class>
* `constructor`: <https://en.cppreference.com/w/cpp/language/constructor>
* `this`: <https://en.cppreference.com/w/cpp/language/this>
* `access-specifier`: <https://en.cppreference.com/w/cpp/language/access>
* `static`: <https://en.cppreference.com/w/cpp/language/static>
* `throw`: <https://en.cppreference.com/w/cpp/language/throw>
* `try-block`: <https://en.cppreference.com/w/cpp/language/try>
* `stdexcept`: <https://en.cppreference.com/w/cpp/header/stdexcept>
* `invalid_argument`: <https://en.cppreference.com/w/cpp/error/invalid_argument>
* `operator overloading`: <https://en.cppreference.com/w/cpp/language/operators>
* `friend`: <https://en.cppreference.com/w/cpp/language/friend>
* `std::string`: <https://en.cppreference.com/w/cpp/string/basic_string>
* `destructors`: <https://en.cppreference.com/w/cpp/language/destructor>
* `copy constructor`: <https://en.cppreference.com/w/cpp/language/copy_constructor>
* `move constructor`: <https://en.cppreference.com/w/cpp/language/move_constructor>
* `copy assignment operator`: <https://en.cppreference.com/w/cpp/language/as_operator.html>
* `move assignment operator`: <https://en.cppreference.com/w/cpp/language/move_assignment>
* `rule of three/five/zero`: <https://en.cppreference.com/w/cpp/language/rule_of_three>
* `template`: <https://en.cppreference.com/w/cpp/language/templates>
* `lambda expressions`: <https://en.cppreference.com/w/cpp/language/lambda>
* `derived classes`: <https://en.cppreference.com/w/cpp/language/derived_class>
* `virtual functions`: <https://en.cppreference.com/w/cpp/language/virtual>
* `abstract classes`: <https://en.cppreference.com/w/cpp/language/abstract_class>
* `std::unique_ptr`: <https://en.cppreference.com/w/cpp/memory/unique_ptr>
* `std::make_unique`: <https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique>
* `std::vector`: <https://en.cppreference.com/w/cpp/container/vector>
* `std::transform`: <https://en.cppreference.com/w/cpp/algorithm/transform>
* `std::toupper / std::tolower`: <https://en.cppreference.com/w/cpp/string/byte/toupper>
* `std::sort`: <https://en.cppreference.com/w/cpp/algorithm/sort>
* `std::map`: <https://en.cppreference.com/w/cpp/container/map>
* `std::pair`: <https://en.cppreference.com/w/cpp/utility/pair>
* `std::set`: <https://en.cppreference.com/w/cpp/container/set>
* `std::ifstream`: <https://en.cppreference.com/w/cpp/io/basic_ifstream>

### Qt

* `Qt 6 Documentation`: <https://doc.qt.io/qt.html>
* `Qt Widgets Documentation`: <https://doc.qt.io/qt-6/qtwidgets-index.html>
* `QMainWindow`: <https://doc.qt.io/qt-6/qmainwindow.html>
* `QTextEdit`: <https://doc.qt.io/qt-6/qtextedit.html>
* `QPushButton`: <https://doc.qt.io/qt-6/qpushbutton.html>
* `QVBoxLayout`: <https://doc.qt.io/qt-6/qvboxlayout.html>
* `QHBoxLayout`: <https://doc.qt.io/qt-6/qhboxlayout.html>
* `QMenuBar`: <https://doc.qt.io/qt-6/qmenubar.html>
* `QMenu`: <https://doc.qt.io/qt-6/qmenu.html>
* `QAction`: <https://doc.qt.io/qt-6/qaction.html>
* `QFileDialog`: <https://doc.qt.io/qt-6/qfiledialog.html>
* `QFile`: <https://doc.qt.io/qt-6/qfile.html>
* `QTextStream`: <https://doc.qt.io/qt-6/qtextstream.html>
* `QString`: <https://doc.qt.io/qt-6/qstring.html>
* `QKeySequence`: <https://doc.qt.io/qt-6/qkeysequence.html>
* `QToolBar`: <https://doc.qt.io/qt-6/qtoolbar.html>
* `QTextCharFormat`: <https://doc.qt.io/qt-6/qtextcharformat.html>
* `QTextCursor`: <https://doc.qt.io/qt-6/qtextcursor.html>
* `QDialog`: <https://doc.qt.io/qt-6/qdialog.html>
* `QTextDocument::find`: <https://doc.qt.io/qt-6/qtextdocument.html#find>
* `QStatusBar`: <https://doc.qt.io/qt-6/qstatusbar.html>
* `Qt Designer / .ui files`: <https://doc.qt.io/qt-6/designer-using-a-ui-file.html>
* `QMessageBox`: <https://doc.qt.io/qt-6/qmessagebox.html>
* `QSyntaxHighlighter`: <https://doc.qt.io/qt-6/qsyntaxhighlighter.html>
* `QFontDialog`: <https://doc.qt.io/qt-6/qfontdialog.html>
* `QColorDialog`: <https://doc.qt.io/qt-6/qcolordialog.html>
* `QPrintDialog`: <https://doc.qt.io/qt-6/qprintdialog.html>