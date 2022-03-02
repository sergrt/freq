#include "Trie.h"
#include "TrieSaver.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

constexpr auto in_file_name = "in.txt";
constexpr auto out_file_name = "out.txt";
constexpr size_t read_buf_size = 1024;

namespace {
bool is_char(const char c) {
    return c >= 'a' && c <= 'z';
}

void fill_trie_from_file(Trie& trie, const std::string& filename) {
    std::ifstream file(filename);
    if (!file)
        throw std::system_error(errno, std::system_category(), "Unable to open input file");

    std::vector<char> buf(read_buf_size);
    std::string buf_word;

    do {
        file.read(buf.data(), read_buf_size);
        const auto count = file.gcount();
        if (count == 0 && !file.eof()) {
            throw std::system_error(errno, std::system_category(), "Unable to read from input file");
        }

        int idx = 0;
        while (idx < count) {
            const auto c = static_cast<char>(tolower(buf[idx]));
            if (is_char(c)) {
                buf_word.append(1, c);
            } else if (!buf_word.empty()) {
                trie.insert(buf_word);
                buf_word.clear();
            }
            ++idx;
        }
    } while (!file.eof());

    if (!buf_word.empty())
        trie.insert(buf_word);
}
}

int main() {
    try {
        Trie trie;
        std::cout << "Processing file " << in_file_name << "...\n";
        fill_trie_from_file(trie, in_file_name);

        std::cout << "Saving to file " << out_file_name << "...\n";
        TrieSaver().save(trie, out_file_name);

        std::cout << "Done\n";
    } catch (std::exception& e) {
        std::cout << "Error: " << e.what();
    }
}
