#pragma once

#include <istream>
#include <string>
#include <vector>

class BlockReader {
   public:
    explicit BlockReader(size_t s, std::istream& is) : block_size_{s}, input_stream_{is} {}

    void operator>>(std::vector<std::string>& vec) {
        bool ret = false;
        counter_ = block_size_;

        while (!ret) {
            std::string command;
            std::getline(input_stream_, command);

            if ("EOF" == command) {
                ret = on_eof();
            } else if ("{" == command) {
                ret = on_left_brace() && vec.size();
            } else if ("}" == command) {
                ret = on_right_brace() && vec.size();
            } else {
                ret = on_command(command, vec);
            }
        }
    }

    bool eof() const { return eof_; }

   private:
    const size_t block_size_;
    std::istream& input_stream_;

    bool eof_ = false;
    size_t counter_;
    int block_count_ = 0;

    bool on_eof() {
        eof_ = true;
        return true;
    }

    bool on_left_brace() {
        block_count_++;
        counter_ = block_size_;
        return (1 == block_count_) ? true : false;
    }

    bool on_right_brace() {
        if (block_count_ > 0) {
            block_count_--;
        }
        return (0 == block_count_) ? true : false;
    }

    bool on_command(std::string command, std::vector<std::string>& vec) {
        vec.push_back(command);
        if (!block_count_) {
            counter_--;
        }

        return counter_ ? false : true;
    }
};
