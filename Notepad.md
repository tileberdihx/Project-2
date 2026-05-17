# Notepad — Project Report

## Overview

This project extends the Notepad application built across Practices 5–8 into a more capable editor. It adds two required features (exception handling and spell checker) and three optional features (font dialog, color picker, zoom), plus a cursor line/column indicator in the status bar.

---

## Required Features

### 1. Exception Handling

`notepad_exception.h` defines a four-class hierarchy:

- `notepad_exception` — base, inherits `std::runtime_error`, stores the error message
- `file_not_found_exception` — thrown when `QFileInfo::exists()` returns false
- `file_read_exception` — thrown when a file cannot be opened for reading
- `file_write_exception` — thrown when a file cannot be opened for writing

Both `open_file()` and `save_file()` wrap their `QFile` operations in `try / catch (const notepad_exception& e)` blocks. On failure, `QMessageBox::critical(this, "Error", ...)` shows the message from `e.what()`.

### 2. Spell Checker

`spell_checker.h` loads `data/words.txt` into a `std::set<std::string>` at startup. `is_correct()` normalizes the word and checks membership. `suggestions()` collects words within Levenshtein edit distance 1, then edit distance 2 with the same starting letter.

`spell_checker_highlighter.h` subclasses `QSyntaxHighlighter`. Qt calls `highlightBlock()` on every paragraph when the document changes. Misspelled words get `SpellCheckUnderline` in red.

Right-clicking a misspelled word shows up to 5 suggestions. `Tools > Check Spelling...` calls `rehighlight()` to re-run the pass.

---

## Optional Features

### 1. Cursor Line / Column Indicator (Optional #1)

A `QLabel* label_cursor` is added as a permanent widget to the status bar. Connected to both `textChanged` and `cursorPositionChanged`. Displays `"Ln N, Col M"`.

### 2. Font Dialog (Optional #2)

`Format > Font...` opens `QFontDialog::getFont()`. The chosen font is applied via `cursor.mergeCharFormat()` to the selection or whole document.

### 3. Text Color (Optional #3)

`Format > Text Color...` opens `QColorDialog::getColor()`. Applied via `QTextCharFormat::setForeground()` and `cursor.mergeCharFormat()`.

### 4. Zoom (Optional #8)

`View > Zoom In / Zoom Out / Reset Zoom` with shortcuts `Ctrl++`, `Ctrl+-`, `Ctrl+0`. Uses `editor->zoomIn()` and `editor->zoomOut()`.

---

## Sort

`sort.h` implements `my::sort` — a selection sort template. The word frequency dialog uses it with a lambda to sort pairs by count descending.