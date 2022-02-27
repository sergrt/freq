#include "TrieSaver.h"

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

constexpr auto tmp_file_prefix = "tmp_";
constexpr size_t read_buf_size = 1024;

void TrieSaver::save(const Trie& trie, const std::string& out_file_name) {
    traverse(trie, {});
    try {
        combine_tmp_files(out_file_name);
    } catch (std::exception&) {
        cleanup();
        throw;
    }
    cleanup();
}

TrieSaver::~TrieSaver() {
    // Just to be sure
    cleanup();
}

void TrieSaver::save_word(const std::string& w, int freq_file_id) {
    get_tmp_file_stream(freq_file_id) << w << "\n";
}

std::fstream& TrieSaver::get_tmp_file_stream(int freq) {
    if (const auto i = tmp_streams_.find(freq); i != std::end(tmp_streams_)) {
        return i->second;
    }

    const std::string filename = tmp_file_prefix + std::to_string(freq);
    tmp_streams_.emplace(freq, std::fstream(filename, std::fstream::in | std::fstream::out | std::ios::trunc));
    auto& tmp_file_stream = tmp_streams_[freq];
    if (!tmp_file_stream)
        throw std::system_error(errno, std::system_category(), "Unable to create temporary file");

    tmp_filenames_[freq] = filename;
    return tmp_file_stream;
}

void TrieSaver::traverse(const Trie& trie, const std::string& str_buf) {
    if (trie.word_counter > 0)
        save_word(str_buf, trie.word_counter);

    for (const auto& t : trie.children) {
        traverse(t.second, str_buf + std::string(1, t.first));
    }
}

void TrieSaver::combine_tmp_files(const std::string& out_file_name) {
    std::ofstream out_file(out_file_name, std::ios::trunc);
    if (!out_file)
        throw std::system_error(errno, std::system_category(), "Unable to open output file");

    std::vector<char> buf(read_buf_size);

    for (auto& p : tmp_streams_) {
        auto& file = p.second;
        file.seekg(0);
        while (file.getline(buf.data(), read_buf_size)) {
            if (file.gcount() != 0)
                out_file << p.first << " " << buf.data() << "\n";
        }
    }
}

void TrieSaver::cleanup() {
    tmp_streams_.clear();
    remove_tmp_files();
    tmp_filenames_.clear();
}

void TrieSaver::remove_tmp_files() const {
    for (auto& p : tmp_filenames_) {
        std::filesystem::remove(p.second);
    }
}
