#pragma once

#include <cstring>
#include <iostream>
#include <istream>
#include <sstream>
#include <vector>

class BlockReader {
   public:
    explicit BlockReader(size_t s, std::istream& is) : block_size_{s}, input_stream_{is} {}

    void operator>>(std::vector<std::string>& vec) {
        bool ret = false;
        while (!ret) {
            std::string command;
            std::getline(input_stream_, command);

            if ("EOF" == command) {
                ret = on_eof();
            } else if ("{" == command) {
                ret = on_left_brace();
            } else if ("}" == command) {
                ret = on_right_brace();
            } else {
                ret = on_command(command, vec);
            }
        }
    }

    void SetSize(size_t s) { block_size_ = s; }

   private:
    size_t block_size_;
    std::istream& input_stream_;
    std::ostringstream outstring_{};

    size_t counter_;

    size_t block_count_ = 0;

    bool is_dynamic() { return (0 != block_count_); }

    void begin_block() {
        block_count_++;
        counter_ = block_size_;
    }

    void end_block() { block_count_--; }

    bool on_eof() { return true; }
    bool on_left_brace() { return false; }
    bool on_right_brace() { return false; }

    bool on_command(std::string command, std::vector<std::string>& vec) {
        vec.push_back(command);
        return false;
    }
};
