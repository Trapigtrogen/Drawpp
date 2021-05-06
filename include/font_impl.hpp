#ifndef DPP_FONT_IMPL_H
#define DPP_FONT_IMPL_H

#include <unordered_map>
#include <cstdint>

///\private
struct DFont_impl
{
    struct Char
    {
        float tx_pos_x;
        float tx_pos_y;
        float tx_width;
        float tx_height;
        float height;
        float width;
        float bearing_x;
        float bearing_y;
        float advance_x;
        float advance_y;    //unused
    };

    DFont_impl() = default;
    DFont_impl(const DFont_impl&) = delete;
    ~DFont_impl();
    
    //Load a font from a font face. This should be used to initialize a font
    //Returns nullptr on failure
    static DFont_impl* load_font(void* face, const struct FontOptions& options);

    //Initialize the freetype library
    static void init_lib();

    //Cleanup the freetype library
    static void cleanup_lib();

    //Load a character into the bitmap and texture
    bool load_additional_char(wchar_t c);

    //Load all characters available in the font face
    void load_all_chars();

    //Create a texture from bitmap, and upload it to gpu
    void apply_texture();
    
    unsigned int texture_id = 0;
    std::unordered_map<wchar_t,Char> chars;

    float font_size = 0;
    float char_height = 0;
    float char_width = 0;
    float baseline = 0;
    float row_spacing = 0;
    float char_spacing = 0;
    int loaded_chars = 0;
    int current_column = 0;
    int current_row = 0;
    int chars_per_row = 0;
    int chars_per_col = 0;
    uint8_t* bitmap = nullptr;

    void* font_face;
    unsigned char* font_data;

    static void* lib_ptr;
};

#endif