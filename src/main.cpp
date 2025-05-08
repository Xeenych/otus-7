#include "block_reader.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char* argv[]) {
    std::istringstream s{argv[1]};
    size_t block_size = 0;
    s >> block_size;
    std::cout << "Block size is: " << block_size << std::endl;

    BlockReader br{block_size, std::cin};

    std::string line;
    while (br.GetLine(line)) {
        std::cout << line << std::endl;
    }
    // вывод послденей строки перед EOF
    std::cout << line << std::endl;

    return 0;
}