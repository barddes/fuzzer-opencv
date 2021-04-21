//
// Created by barddes on 21/04/2021.
//

#include <iostream>
#include "png-mutator.h"

//int main(int argc, char **argv) {
//    if(argc < 2) {
//        std::cerr << "Erro: Arquivo PNG nao informado" << std::endl;
//        throw;
//    }
//
//    Png png = Png(argv[1]);
//
//    std::cout << "Width:  " << png.width() << std::endl;
//    std::cout << "Height: " << png.height() << std::endl;
//
//    return 0;
//}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
    std::vector<uint8_t> data(Data, Data+Size);
    Png png = Png(data);

    std::cout << "Width:  " << png.width() << std::endl;
    std::cout << "Height: " << png.height() << std::endl;

    return 0;
}