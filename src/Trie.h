#pragma once

#include <map>
#include <string>

struct Trie final {
    void insert(const std::string& str);

    int word_counter = 0;
    std::map<char, Trie> children;

private:
    void insert_impl(const std::string& str);
};
