// 4.17.0 0xc29c3c92
// Generated by imageconverter. Please, do not edit!

#include <BitmapDatabase.hpp>
#include <touchgfx/Bitmap.hpp>

extern const unsigned char image_blue_buttons_round_edge_small[]; // BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_ID = 0, Size: 170x60 pixels
extern const unsigned char image_blue_buttons_round_edge_small_pressed[]; // BITMAP_BLUE_BUTTONS_ROUND_EDGE_SMALL_PRESSED_ID = 1, Size: 170x60 pixels
extern const unsigned char image_bootscreen_01[]; // BITMAP_BOOTSCREEN_01_ID = 2, Size: 480x270 pixels
extern const unsigned char image_bootscreen_05[]; // BITMAP_BOOTSCREEN_05_ID = 3, Size: 480x270 pixels
extern const unsigned char image_rida_home_temp[]; // BITMAP_RIDA_HOME_TEMP_ID = 4, Size: 1684x1048 pixels

const touchgfx::Bitmap::BitmapData bitmap_database[] = {
    { image_blue_buttons_round_edge_small, 0, 170, 60, 11, 4, 148, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 50, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_blue_buttons_round_edge_small_pressed, 0, 170, 60, 11, 4, 148, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 50, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_bootscreen_01, 0, 480, 270, 0, 0, 480, ((uint8_t)touchgfx::Bitmap::RGB565) >> 3, 270, ((uint8_t)touchgfx::Bitmap::RGB565) & 0x7 },
    { image_bootscreen_05, 0, 480, 270, 0, 0, 480, ((uint8_t)touchgfx::Bitmap::RGB565) >> 3, 270, ((uint8_t)touchgfx::Bitmap::RGB565) & 0x7 },
    { image_rida_home_temp, 0, 1684, 1048, 0, 0, 1684, ((uint8_t)touchgfx::Bitmap::RGB565) >> 3, 1048, ((uint8_t)touchgfx::Bitmap::RGB565) & 0x7 }
};

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance()
{
    return bitmap_database;
}

uint16_t getInstanceSize()
{
    return (uint16_t)(sizeof(bitmap_database) / sizeof(touchgfx::Bitmap::BitmapData));
}
} // namespace BitmapDatabase
