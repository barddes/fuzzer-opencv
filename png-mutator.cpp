//
// Created by barddes on 21/04/2021.
//
#include <fstream>
#include <iterator>
#include <cstring>
#include <iostream>
#include <bitset>
#include "png-mutator.h"

void Png::load_raw_data(const std::vector<uint8_t>& data) {
    _raw.clear();
    _raw.reserve(data.size());
    for (uint8_t e: data)
        _raw.push_back(e);
    _parse_raw();
}

Png::Png(const char *filename) {
    _raw = _read_file(filename);
    _parse_raw();
}

std::vector<uint8_t> Png::_read_file(const char *filename) {
    // open the file:
    std::ifstream file(filename, std::ios::binary);

    // Stop eating new lines in binary mode!!!
    file.unsetf(std::ios::skipws);

    // get its size:
    std::streampos fileSize;

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // reserve capacity
    std::vector<uint8_t> vec;
    vec.reserve(fileSize);

    // read the data:
    vec.insert(vec.begin(),
               std::istream_iterator<uint8_t>(file),
               std::istream_iterator<uint8_t>());

    return vec;
}

void Png::_parse_raw() {
    uint8_t* praw = _raw.data();
    uint8_t* eraw = _raw.data() + _raw.size();

    std::cout << "[INFO] Parsing raw data" << std::endl;
    std::cout << "[INFO] size = " << _raw.size() << std::endl;

    if(memcmp(praw, PNG_HEADER, 8) != 0){
        std::cerr << "Error: invalid png header" << std::endl;
        std::cerr << "PNG_HEADER  " << PNG_HEADER << std::endl;

        praw[9] = '\0';
        std::cerr << "FILE_HEADER " << praw << std::endl;
        throw;
    }
    praw+=8;

    while(praw < eraw) {
        std::cout << "[INFO] New chunk found" << std::endl;
        Chunk c = Chunk();

        memcpy(&c.length, praw, 4);
        c.length = __builtin_bswap32(c.length);
        praw+=4;
        std::cout << "[INFO] length = " << c.length << std::endl;

        memcpy(c.name, praw, 4);
        praw+=4;
        std::cout << "[INFO] name = " << c.name << std::endl;

        c.data.clear();
        c.data.reserve(c.length);
        for(int i = 0; i<c.length; i++)
            c.data.push_back(praw[i]);
        praw+=c.length;
        std::cout << "[INFO] " << c.length << " bytes read" << std::endl;

        memcpy(&c.crc, praw, 4);
        c.crc = __builtin_bswap32(c.crc);
        praw+=4;
        std::cout << "[INFO] CRC = " << c.crc << std::endl;

        chunks.push_back(c);
    }

    if(praw > eraw) {
        std::cerr << "Error: bad chunks" << std::endl;
        throw;
    }

    for(Chunk& c: chunks) {
        if(memcmp(c.name, "IHDR", 4) == 0){
            _ihdr = true;
            _load_ihdr(c);
        } else if(memcmp(c.name, "PLTE", 4) == 0){
            _plte = true;
        } else if(memcmp(c.name, "IDAT", 4) == 0){
            _idat = true;
        } else if(memcmp(c.name, "IEND", 4) == 0){
            _iend = true;
        }
    }

    if(!_ihdr) {
        std::cerr << "Error: IHDR chunk missing" << std::endl;
        throw;
    }

    if(!_plte  && _color_type == 3) {
        std::cerr << "Error: PLTE chunk missing" << std::endl;
        throw;
    }

    if(_plte && (_color_type == 0 || _color_type == 4)) {
        std::cerr << "Error: PLTE color and Color Type conflict" << std::endl;
        throw;
    }

    if(!_idat) {
        std::cerr << "Error: IDAT chunk missing" << std::endl;
        throw;
    }

    if(!_iend) {
        std::cerr << "Error: IEND chunk missing" << std::endl;
        throw;
    }

}

void Png::_load_ihdr(Png::Chunk &c) {
    uint8_t* p = c.data.data();

    memcpy(&_width, p, 4);
    _width = __builtin_bswap32(_width);
    p+=4;

    memcpy(&_height, p, 4);
    _height = __builtin_bswap32(_height);
    p+=4;

    _bit_depth = *(p++);
    _color_type = *(p++);
    _compression_method = *(p++);
    _filter_method = *(p++);
    _interlace_method = *(p++);
}

uint32_t Png::width() {
    return _width;
}

uint32_t Png::height() {
    return _height;
}
