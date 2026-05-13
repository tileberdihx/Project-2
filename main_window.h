#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "text_transform.h"

#include <QDialog>
#include <QMainWindow>
#include <QString>
#include <QTextDocument>
#include <QTextEdit>
#include <memory>
#include <vector>

class main_window : public QMainWindow {
public:
    main_window();

private:
    void setup_file_menu();
    void setup_edit_menu();
    void setup_format_menu();
    void setup_format_toolbar();

    void setup_search_menu();
    void setup_word_frequency_menu();

    void open_file();
    void save_file();
    void save_file_as();
    void update_title();
    void apply_transform(const text_transform& transform) const;
    void update_status_bar();

    void find_next(const QString& term, QTextDocument::FindFlags flags = QTextDocument::FindFlags()) const;
    void replace_current(const QString& term, const QString& replacement,
        QTextDocument::FindFlags flags = QTextDocument::FindFlags()) const;
    void replace_all(const QString& term, const QString& replacement,
        QTextDocument::FindFlags flags = QTextDocument::FindFlags()) const;

    QTextEdit* editor { nullptr };
    QString current_file;
    QDialog* find_replace_dlg { nullptr };
    QDialog* word_frequency_dlg { nullptr };

    std::vector<std::unique_ptr<text_transform>> transforms;
};

#endif // MAIN_WINDOW_H
