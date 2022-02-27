#include "Trie.h"

void Trie::insert(const std::string& str) {
    if (str.empty())
        return;

    insert_impl(str);
}

void Trie::insert_impl(const std::string& str) {
    Trie* trie = this;

    for (const auto& c : str) {
        trie = &trie->children[c];
    }
    ++trie->word_counter;
}