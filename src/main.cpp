#include "block_reader.hpp"
#include "block_writer.hpp"

#include <iostream>
#include <sstream>

int main(int argc, char* argv[]) {
    std::istringstream s{argv[1]};
    size_t block_size = 0;
    s >> block_size;
    std::cout << "Block size is: " << block_size << std::endl;

    BlockReader br{block_size, std::cin};
    BlockWriter bw{std::cout};

    std::vector<std::string> commands;

    while (!br.eof()) {
        br >> commands;
        bw << commands;
        commands.clear();
    }

    return 0;
}