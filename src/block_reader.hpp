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
        outstring_.str("");
        outstring_ << "bulk: ";

        for (auto count = 0; count < block_size_; count++) {
            std::string input_line;
            std::getline(input_stream_, input_line);

            if ("EOF" == input_line) {
                line = serialize();
                return false;
            }

            if ("{" == input_line) {
                begin_block();
                line = serialize();
                return true;
            }

            if ("}" == input_line) {
                end_block();
                line = serialize();
                return true;
            }

            add_line(input_line);
        }

        line = serialize();
        return true;
    }

    void SetSize(size_t s) { block_size_ = s; }

   private:
    size_t block_size_;
    std::istream& input_stream_;
    std::ostringstream outstring_{};
    bool dynamic_block_ = false;

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

    void begin_block() { dynamic_block_ = true; }

    void end_block() { dynamic_block_ = false; }
};
