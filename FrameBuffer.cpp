#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int width, int height, BufferType type)
{
    switch (type)
    {
    case BufferType::monochrome:
        this->buffer = new unsigned char[width * height / 8];
        this->bufferType = BufferType::monochrome;
        this->Size = width * height / 8;
        break;
    case BufferType::rgbSingle:
        this->buffer = new unsigned char[width * height / 2];
        this->bufferType = BufferType::rgbSingle;
        this->Size = width * height / 2;
        break;
    default:
        break;
    }

    this->width = width;
    this->height = height;
    clear();
}
void FrameBuffer::Constructor(int width, int height, BufferType type)
{
    switch (type)
    {
    case BufferType::monochrome:
        this->buffer = new unsigned char[width * height / 8];
        this->bufferType = BufferType::monochrome;
        this->Size = width * height / 8;
        break;
    case BufferType::rgbSingle:
        this->buffer = new unsigned char[width * height / 2];
        this->bufferType = BufferType::rgbSingle;
        this->Size = width * height / 2;
        break;
    default:
        break;
    }

    this->width = width;
    this->height = height;
    clear();
}

void FrameBuffer::bufferOR(int n, unsigned char byte)
{
    if (n > (Size - 1))
        return;
    this->buffer[n] |= byte;
}

void FrameBuffer::bufferAND(int n, unsigned char byte)
{
    if (n > (Size - 1))
        return;
    this->buffer[n] &= byte;
}

void FrameBuffer::bufferxOR(int n, unsigned char byte)
{
    if (n > (Size - 1)()
        return;
    this->buffer[n] ^= byte;
}

void FrameBuffer::setBuffer(unsigned char *new_buffer)
{
    this->buffer = new_buffer;
}
unsigned char *FrameBuffer::getBuffer()
{
    return this->buffer;
}

void FrameBuffer::clear()
{
    memset(this->buffer, 0, Size);
}
void FrameBuffer::fill()
{
    memset(this->buffer, 255, Size);
}
void FrameBuffer::fill(Colors color)
{
    if (this->bufferType == BufferType::monochrome)
        if (color == Colors::BLACK)
            memset(this->buffer, 0, Size);
        else
            memset(this->buffer, 255, Size);
    else
    {
        char byte = (char)color;
        byte = (byte << 3) || color;
        memset(this->buffer, color, Size);
    }
}
void FrameBuffer::addBitmapImage(int16_t anchorX, int16_t anchorY, uint16_t image_width, uint16_t image_height, uint8_t *image, Mode mode, bool slow)
{
    uint8_t byte = 0;

    // goes over every single bit in image and sets pixel data on its coordinates
    if (this->bufferType == BufferType::monochrome)
    {
        for (uint16_t y = 0; y < image_height; y++)
        {
            for (uint16_t x = 0; x < image_width / 8; x++)
            {
                byte = image[y * (image_width / 8) + x];
                for (uint16_t z = 0; z < 8; z++)
                {
                    if ((byte >> (7 - z)) & 1)
                    {
                        setPixel(x * 8 + z + anchorX, y + anchorY, Colors::WHITE, mode);
                    }
                }
            }
        }
    }
    else if (this->bufferType == BufferType::rgbSingle)
    {
        uint16_t xSize = (image_width >> 1) << 1;
        uint16_t ySize = (image_height >> 1) << 1;
        for (uint16_t y = 0; y < ySize; y++)
        {
            for (uint16_t x = 0; x < xSize; x++)
            {
                unsigned long index = (y * image_width + x) / 2;

                byte = image[index];

                setPixels(x + anchorX, y + anchorY, byte, mode);
            }
        }
        /// for (uint16_t y = 0; y < image_height; y++)
        ///{
        ///     for (uint16_t x = 0; x < image_width; x++)
        ///     {
        ///         unsigned long index = (y * image_width + x) / 2;
        ///         bool bit = !(y * image_width + x) % 2;

        ///        byte = (image[index] >> (bit * 3)) & 7;

        ///        setPixel(x + anchorX, y + anchorY, (Colors)(byte), mode);

        ///        if (slow)
        ///        {
        ///        }
        ///    }
        ///}
    }
}

int FrameBuffer::getPixel(int x, int y)
{
    int value = 0;
    int index = 0;
    int bit = 0;
    switch (this->bufferType)
    {
    case (BufferType::monochrome):
        if (x > this->width || y > this->height)
            value = -1;
        index = (y * this->width + x) / 8;
        bit = (y * this->width + x) % 8;
        value = (this->buffer[index] >> bit) & 1;
        break;
    case (BufferType::rgbSingle):
        if (x > this->width || y > this->height)
            value = -1;
        index = (y * this->width + x) / 2;
        bit = (y * this->width + x) % 2;

        value = (this->buffer[index] >> (bit * 3)) & 7;

        // printf("value: %d, index: %d, index2: %d", value,index ,index >> 1);
        break;
    default:
        break;
    }
    return value;
}
void FrameBuffer::setPixel(int16_t x, int16_t y, Colors color, Mode mode)
{
    if ((x < 0) || (x >= this->width) || (y < 0) || (y >= this->height))
        return;
    uint16_t byte = 0;
    switch (this->bufferType)
    {
    case BufferType::monochrome:

        byte = 1 << (y & 7);

        if (mode == Mode::draw || color != Colors::BLACK)
        {
            this->bufferOR(x + ((y / 8) * this->width), byte);
        }
        else if (mode == Mode::clear || color == Colors::BLACK)
        {
            this->bufferAND(x + ((y / 8) * this->width), ~byte);
        }
        else if (mode == Mode::invert)
        {
            this->bufferxOR(x + ((y / 8) * this->width), byte);
        }
        else
        {
            this->bufferOR(x + ((y / 8) * this->width), byte);
        }

        break;
    case BufferType::rgbSingle:
        byte = (char)color;
        char repbyte = 0xf8;
        bool second = false;
        if (x + (y * this->width) & 1)
        {
            if (byte)
                byte = byte << 3;
            repbyte = 0xc7;
            second = true;
        }

        if (mode == Mode::draw)
        {
            this->bufferOR((x + (y * this->width)) >> 1, byte);
        }
        else if (mode == Mode::clear)
        {
            this->bufferAND((x + (y * this->width)) >> 1, ~byte);
        }
        else if (mode == Mode::invert)
        {
            this->bufferxOR((x + (y * this->width)) >> 1, byte);
        }
        else if (mode == Mode::replace)
        {
            this->bufferAND((x + (y * this->width)) >> 1, repbyte);
            this->bufferOR((x + (y * this->width)) >> 1, byte);
        }
        else if (mode == Mode::combine)
        {
            if (second)
            {
                if (byte & 0x38)
                {
                    this->bufferAND((x + (y * this->width)) >> 1, repbyte);
                    this->bufferOR((x + (y * this->width)) >> 1, byte);
                }
            }
            else
            {
                if (byte & 0x7)
                {
                    this->bufferAND((x + (y * this->width)) >> 1, repbyte);
                    this->bufferOR((x + (y * this->width)) >> 1, byte);
                }
            }
        }
        break;
    }
}
void FrameBuffer::setPixels(int16_t x, int16_t y, char pixel, Mode mode)
{
    if ((x < 0) || (x >= this->width) || (y < 0) || (y >= this->height) || this->bufferType != BufferType::rgbSingle)
        return;

    if (mode == Mode::draw)
    {
        this->bufferOR((x + (y * this->width)) >> 1, pixel);
    }
    else if (mode == Mode::clear)
    {
        this->bufferAND((x + (y * this->width)) >> 1, ~pixel);
    }
    else if (mode == Mode::invert)
    {
        this->bufferxOR((x + (y * this->width)) >> 1, pixel);
    }
    else if (mode == Mode::replace)
    {
        this->bufferAND((x + (y * this->width)) >> 1, 0);
        this->bufferOR((x + (y * this->width)) >> 1, pixel);
    }
    else if (mode == Mode::combine)
    {
        return;
    }
}
void FrameBuffer::drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, Colors color, Mode mode)
{

    bool angle = abs(y1 - y0) > abs(x1 - x0);
    if (angle)
    {
        uint16_t temp = x0;
        x0 = y0;
        y0 = temp;

        temp = x1;
        x1 = y1;
        y1 = temp;
    }

    if (x0 > x1)
    {
        uint16_t temp = x0;
        x0 = x1;
        x1 = temp;

        temp = y0;
        y0 = y1;
        y1 = temp;
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int16_t err = dx / 2;
    int16_t ydirection;

    if (y0 < y1)
    {
        ydirection = 1;
    }
    else
    {
        ydirection = -1;
    }

    for (; x0 <= x1; x0++)
    {
        if (angle)
        {
            setPixel(y0, x0, color, mode);
        }
        else
        {
            setPixel(x0, y0, color, mode);
        }
        err -= dy;
        if (err < 0)
        {
            y0 += ydirection;
            err += dx;
        }
    }
}
void FrameBuffer::drawFastHLine(uint16_t x, uint16_t y, uint16_t w, Colors color, Mode mode)
{
    drawLine(x, y, x + w - 1, y, color, mode);
}
void FrameBuffer::drawFastVLine(uint16_t x, uint16_t y, uint16_t h, Colors color, Mode mode)
{
    drawLine(x, y, x, y + h - 1, color, mode);
}
void FrameBuffer::drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Colors color, Mode mode)
{
    drawLine(x0, y0, x1, y1, color, mode);
    drawLine(x1, y1, x2, y2, color, mode);
    drawLine(x2, y2, x0, y0, color, mode);
}
void FrameBuffer::fillCircle(uint16_t x0, uint16_t y0, uint16_t r, Colors color, Mode mode)
{
    for (int i = 0; i <= 90; i++)
    {
        double angle = i * 3.14 / 180;
        int y = int(r * std::sin(angle));
        int x = int(r * std::cos(angle));
        setPixel(x0 - x, y0 - y, color, mode);
        setPixel(x0 - x, y0 + y, color, mode);
        setPixel(x0 + x, y0 - y, color, mode);
        setPixel(x0 + x, y0 + y, color, mode);
        drawLine(x0 - x, y0 - y, x0 - x, y0 + y, color, mode);
        drawLine(x0 + x, y0 - y, x0 + x, y0 + y, color, mode);
    }
}
void FrameBuffer::drawCircle(uint16_t x0, uint16_t y0, int8_t r, Colors color, Mode mode)
{

    for (int i = 0; i <= 90; i++)
    {
        double angle = i * 3.14 / 180;
        int y = int(r * std::sin(angle));
        int x = int(r * std::cos(angle));
        setPixel(x0 - x, y0 - y, color, mode);
        setPixel(x0 - x, y0 + y, color, mode);
        setPixel(x0 + x, y0 - y, color, mode);
        setPixel(x0 + x, y0 + y, color, mode);
    }
}
void FrameBuffer::fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, Colors color, Mode mode)
{
    for (uint16_t i = x; i < x + w; i++)
    {
        drawFastVLine(i, y, h, color, mode);
    }
}
void FrameBuffer::drawRect(uint16_t x_start, uint16_t y_start, uint16_t width, uint16_t height, Colors color, Mode mode)
{
    for (uint16_t i = x_start; i < x_start + width; i++)
    {
        setPixel(i, y_start, color, mode);
        setPixel(i, y_start + height, color, mode);
    }
    for (uint16_t i = y_start; i < y_start + height; i++)
    {
        setPixel(x_start, i, color, mode);
        setPixel(x_start + width, i, color, mode);
    }
}
