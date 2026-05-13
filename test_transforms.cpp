#include "text_transform.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

int main()
{
    using namespace std;

    vector<unique_ptr<text_transform>> transforms;
    transforms.push_back(make_unique<uppercase_transform>());
    transforms.push_back(make_unique<lowercase_transform>());
    transforms.push_back(make_unique<capitalize_transform>());
    transforms.push_back(make_unique<sentence_case_transform>());
    transforms.push_back(make_unique<swap_case_transform>());

    cout << "Available text transforms:\n";
    for (size_t i = 0; i < transforms.size(); ++i) {
        cout << "  " << (i + 1) << ". " << transforms[i]->name() << "\n";
    }

    const string sample = "hello, world! how are you?";
    cout << "\nOriginal text: \"" << sample << "\"\n";
    for (const auto& transform : transforms) {
        cout << "After \"" << transform->name() << "\": \"" << transform->apply(sample) << "\"\n";
    }

    return 0;
}