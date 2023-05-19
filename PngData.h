#pragma once
#include <cstddef>
#include <memory>
#include <new>
#include <vector>
#include "RGBA.h"


class PngData {
   
public:
    void WritePng(const char *file, const int width, const int height, std::vector<uint32_t>* canvas);

    void ColorChange(const int width, const int height, std::vector<uint32_t>* canvas);

    uint32_t ColorInverse(uint32_t colorD);

    void ColorR(uint32_t& redColor) {
        redColor = redColor >> 24;
    }

    void ColorG(uint32_t& greenColor) {
        greenColor = greenColor >> 8;
    }

    void ColorB(uint32_t& blueColor) {
        blueColor = blueColor << 8;
    }

    void ColorA(uint32_t& blueColor) {
        blueColor = blueColor << 24;
    }
private:
    std::vector<MYRGBA> canpasData_;
};

