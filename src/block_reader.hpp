#pragma once

#include <cstring>
#include <iostream>
#include <istream>
#include <sstream>

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
                line = outstring_.str();
                return false;
            }

            if ("{" == input_line) {
                begin_block();
                line = outstring_.str();
                return true;
            }

            if ("}" == input_line) {
                end_block();
            }

            if (count) {
                outstring_ << ", ";
            }

            outstring_ << input_line;
        }

        line = outstring_.str();
        return true;
    }

    void SetSize(size_t s) { block_size_ = s; }

   private:
    size_t block_size_;
    std::istream& input_stream_;
    std::ostringstream outstring_{};
    bool dynamic_block_ = false;

    void begin_block() { dynamic_block_ = true; }

    void end_block() { dynamic_block_ = false; }
};
