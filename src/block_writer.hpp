#pragma once

#include <ostream>
#include <string>
#include <vector>

class BlockWriter {
   public:
    BlockWriter(std::ostream& o) : o_{o} {}

    void operator<<(std::vector<std::string> vec) {
        if (vec.size()) {
            o_ << "bulk: ";
        }
        for (auto i = 0; i < vec.size(); i++) {
            if (i) {
                o_ << ", ";
            }
            o_ << vec[i];
        }
    }

   private:
    std::ostream& o_;
};