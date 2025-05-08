#pragma once

#include <cstring>
#include <iostream>
#include <istream>
#include <sstream>

class BlockReader {
   public:
    explicit BlockReader(size_t s, std::istream& is) : block_size_{s}, input_stream_{is} {}

    bool GetLine(std::string& line) {
        std::ostringstream outstring{};
        outstring << "bulk: ";

        for (auto count = block_size_; count--;) {
            std::string input_line;
            std::getline(input_stream_, input_line);

            if ("EOF" == input_line) {
                line = outstring.str();
                return false;
            }

            outstring << input_line;
            if (0 != count) {
                outstring << ", ";
            }
        }

        line = outstring.str();
        return true;
    }

    void SetSize(size_t s) { block_size_ = s; }

   private:
    size_t block_size_;
    std::istream& input_stream_;
};
