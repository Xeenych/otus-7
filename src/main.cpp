#include <cassert>
#include <iostream>
#include <sstream>

int main(int argc, char* argv[]) {
    std::istringstream s{argv[1]};
    int block_size = 0;
    s >> block_size;

    std::cout << "Block size is: " << block_size << std::endl;

    return 0;
}