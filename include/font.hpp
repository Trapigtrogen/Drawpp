#ifndef DPP_FONT_H
#define DPP_FONT_H

#include <string>
#include <unordered_map>
#include <memory>

struct FontOptions
{
    float size = 10.0f;
    float row_spacing = 0.0f;
    float char_spacing = 0.0f;
    std::wstring charset = L"";
    bool load_all = false;
};

struct _DFont_impl
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

    _DFont_impl() = default;
    _DFont_impl(const _DFont_impl&) = delete;
    ~_DFont_impl();
    
    //Load a font from a font face. This should be used to initialize a font
    //Returns nullptr on failure
    static std::shared_ptr<_DFont_impl> load_font(void* face, const FontOptions& options);

    //Initialize the freetype library
    static void init_lib();

    //Load a character into the bitmap and texture
    bool load_additional_char(wchar_t c);

    //Load all characters available in the font face
    void load_all_chars();

    //Create a texture from bitmap, and upload it to gpu
    void apply_texture();
    
    unsigned int texture_id = 0;
    std::unordered_map<wchar_t,Char> chars;

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
    void* font_data;

    static void* lib_ptr;
};

class DFont
{
    friend class Application;
    friend class DGraphics;
public:

    DFont() = default;
    DFont(const DFont&) = default;
    DFont(DFont&&) = default;
    ~DFont() = default;

    DFont& operator=(const DFont&) = default;
    DFont& operator=(DFont&&) = default;

    static DFont load(const std::string& filename, float size, float row_spacing = 0.0f, float char_spacing = 0.0f);
    static DFont load(const std::string& filename, const FontOptions& options);

    void ClearCharset(const std::wstring& new_charset);

    bool valid() const;

private:
    static void init_lib();
    
    std::shared_ptr<_DFont_impl> impl;
};


#endif