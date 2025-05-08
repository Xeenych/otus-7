#pragma once

#include <cstring>
#include <iostream>
#include <istream>
#include <sstream>
#include <vector>

class BlockReader {
   public:
    explicit BlockReader(size_t s, std::istream& is) : block_size_{s}, input_stream_{is} {}

    bool GetLine(std::string& line) {
        while (true) {
            std::string command;
            std::getline(input_stream_, command);

            if ("EOF" == command) {
                return on_eof();
            }

            if ("{" == command) {
                return on_left_brace();
            }

            if ("}" == command) {
                return on_right_brace();
            }

            on_command(command);
        }
    }

    void SetSize(size_t s) { block_size_ = s; }

   private:
    size_t block_size_;
    std::istream& input_stream_;
    std::ostringstream outstring_{};

    size_t counter_;

    size_t block_count_ = 0;

    std::vector<std::string> buffer_;

    void add_line(std::string s) { buffer_.push_back(s); }

    std::string serialize() {
        std::ostringstream o;
        if (buffer_.size()) {
            o << "bulk: ";
        }
        for (auto i = 0; i < buffer_.size(); i++) {
            if (i) {
                o << ", ";
            }
            o << buffer_[i];
        }
        buffer_.clear();
        return o.str();
    }

    bool is_dynamic() { return (0 != block_count_); }

    void begin_block() {
        block_count_++;
        counter_ = block_size_;
    }

    void end_block() { block_count_--; }

    bool on_eof() { return false; }
    bool on_left_brace() { return true; }
    bool on_right_brace() { return true; }
    void on_command(std::string command) {}
};
