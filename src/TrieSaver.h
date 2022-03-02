#pragma once

#include "Trie.h"

#include <fstream>
#include <map>
#include <unordered_map>

struct TrieSaver final {
    TrieSaver() = default;
    ~TrieSaver();

    TrieSaver(const TrieSaver&) = delete;
    TrieSaver& operator=(const TrieSaver&) = delete;

    void save(const Trie& trie, const std::string& out_file_name);

private:
    void traverse(const Trie& trie, const std::string& str_buf);
    void save_word(const std::string& w, int freq_file_id);
    std::fstream& get_tmp_file_stream(int freq);
    void combine_tmp_files(const std::string& out_file_name);
    void remove_tmp_files() const;
    void cleanup();

    std::map<int, std::fstream, std::greater<int>> tmp_streams_;
    std::unordered_map<int, std::string> tmp_filenames_;
};
