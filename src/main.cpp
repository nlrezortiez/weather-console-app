#include "include/app.hpp"

int main(int argc, char** argv) {
    if (argc < 1) {
        std::cout << "No config provided.\n";
        return 1;
    }
    run(argv[1]);
    return 0;
}