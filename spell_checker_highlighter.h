#ifndef SPELL_CHECKER_HIGHLIGHTER_H
#define SPELL_CHECKER_HIGHLIGHTER_H

#include "spell_checker.h"

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QTextDocument>

class spell_checker_highlighter : public QSyntaxHighlighter {
    Q_OBJECT

public:
    explicit spell_checker_highlighter(QTextDocument* document, const spell_checker& checker)
        : QSyntaxHighlighter(document)
        , checker(checker)
    {
        misspelled_format.setUnderlineStyle(QTextCharFormat::WaveUnderline);
        misspelled_format.setUnderlineColor(Qt::red);
    }

protected:
    void highlightBlock(const QString& text) override
    {

        int start = -1;
        for (int i = 0; i <= text.length(); ++i) {
            const bool is_letter = (i < text.length()) && text[i].isLetter();
            if (is_letter && start == -1) {
                start = i;
            } else if (!is_letter && start != -1) {
                const QString word = text.mid(start, i - start);
                const std::string norm = spell_checker::normalize(word.toStdString());
                if (!norm.empty() && !checker.is_correct(norm)) {
                    setFormat(start, i - start, misspelled_format);
                }
                start = -1;
            }
        }
    }

private:
    const spell_checker& checker;
    QTextCharFormat misspelled_format;
};

#endif // SPELL_CHECKER_HIGHLIGHTER_H