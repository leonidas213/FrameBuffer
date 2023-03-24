#pragma once

#include <string.h>
#include "stdio.h"
#include <stdint.h>
#include <stdlib.h>
#include <cmath.h>

enum class Rotation
{
    deg0,
    deg90,
};
enum class Mode
{
    invert = -1,
    erase = 0,
    draw = 1,
    replace = 2,
    combine = 3

};

enum class Colors
{
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    YELLOW = 3,
    BLUE = 4,
    MAGENTA = 5,
    CYAN = 6,
    WHITE = 7
};
enum class BufferType
{
    monochrome,
    rgbSingle,
    rgbDouble // todo
};
class FrameBuffer
{

public:
    unsigned char *buffer;
    const unsigned char *font = font_8x8;
    int Size = 1024;
    BufferType bufferType = BufferType::monochrome;

    FrameBuffer(int width = 128, int height = 64, BufferType type = BufferType::monochrome);
    void Constructor(int width = 128, int height = 64, BufferType type = BufferType::monochrome);
    int width = 128, height = 64;
    void bufferOr(int n, unsigned char byte);
    void bufferAND(int n, unsigned char byte);
    void bufferXOR(int n, unsigned char byte);

    void setBuffer(unsigned char *new_buffer);
    void clear();
    void fill();
    void fill(Colors color);
    unsigned char *getBuffer();

    void setPixel(int16_t x, int16_t y, Colors color = Colors::WHITE, Mode mode = Mode::draw);
    void setPixels(int16_t x, int16_t y, char color = 255, Mode mode = Mode::draw);
    int getPixel(int x, int y);

    void addBitmapImage(int16_t anchorX, int16_t anchorY, uint16_t image_width, uint16_t image_height, uint8_t *image, Mode mode = Mode::draw, bool slow = false);

    void drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, Colors color = Colors::WHITE, Mode mode = Mode::draw);
    void drawCircle(uint16_t x0, uint16_t y0, int8_t r, Colors color = Colors::WHITE, Mode mode = Mode::draw);
    void drawRect(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, Colors color = Colors::WHITE, Mode mode = Mode::draw);
    void drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Colors color = Colors::WHITE, Mode mode = Mode::draw);

    void fillCircle(uint16_t x0, uint16_t y0, uint16_t r, Colors color = Colors::WHITE, Mode mode = Mode::draw);
    void fillRect(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, Colors color = Colors::WHITE, Mode mode = Mode::draw);
    void drawFastHLine(uint16_t x, uint16_t y, uint16_t w, Colors color = Colors::WHITE, Mode mode = Mode::draw);
    void drawFastVLine(uint16_t x, uint16_t y, uint16_t h, Colors color = Colors::WHITE, Mode mode = Mode::draw);
    
  
  };
