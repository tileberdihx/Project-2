#ifndef TEXT_TRANSFORM_H
#define TEXT_TRANSFORM_H

#include <algorithm>
#include <cctype>
#include <string>

class text_transform {
public:
    virtual ~text_transform() = default;

    [[nodiscard]] std::string name() const { return transform_name; }
    [[nodiscard]] virtual std::string apply(const std::string& text) const = 0;

protected:
    explicit text_transform(std::string name)
        : transform_name(std::move(name))
    {
    }

private:
    std::string transform_name;
};

class uppercase_transform : public text_transform {
public:
    uppercase_transform()
        : text_transform("To Uppercase")
    {
    }

    [[nodiscard]] std::string apply(const std::string& text) const override
    {
        std::string result = text;
        std::transform(result.begin(), result.end(), result.begin(), [](const unsigned char ch) {
            return static_cast<char>(std::toupper(ch));
        });
        return result;
    }
};

class lowercase_transform : public text_transform {
public:
    lowercase_transform()
        : text_transform("To Lowercase")
    {
    }

    [[nodiscard]] std::string apply(const std::string& text) const override
    {
        std::string result = text;
        std::transform(result.begin(), result.end(), result.begin(), [](const unsigned char ch) {
            return static_cast<char>(std::tolower(ch));
        });
        return result;
    }
};

class capitalize_transform : public text_transform {
public:
    capitalize_transform()
        : text_transform("Capitalize Words") {};

    [[nodiscard]] std::string apply(const std::string& text) const override
    {
        std::string result = text;
        bool new_word = true;
        for (char& c : result) {
            if (std::isspace(static_cast<unsigned char>(c))) {
                new_word = true;
            } else if (new_word) {
                c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
                new_word = false;
            }
        }
        return result;
    }
};

class sentence_case_transform : public text_transform {
public:
    sentence_case_transform()
        : text_transform("Sentence Case") {};

    [[nodiscard]] std::string apply(const std::string& text) const override
    {
        std::string result = text;
        bool new_sentence = true;
        for (char& c : result) {
            if (c == '.') {
                new_sentence = true;
                continue;
            }
            if (new_sentence && std::isalpha(static_cast<unsigned char>(c))) {
                c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
                new_sentence = false;
            } else {
                c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            }
        }
        return result;
    }
};

class swap_case_transform : public text_transform {
public:
    swap_case_transform()
        : text_transform("Swap Case") {};

    [[nodiscard]] std::string apply(const std::string& text) const override
    {
        std::string result = text;
        for (char& c : result) {
            if (std::isupper(static_cast<unsigned char>(c))) {
                c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            } else if (std::islower(static_cast<unsigned char>(c))) {
                c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
            }
        }
        return result;
    }
};

// TODO: bring code from the previous assignments.

#endif // TEXT_TRANSFORM_H
