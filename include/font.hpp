#ifndef DPP_FONT_H
#define DPP_FONT_H

#include <string>
#include <unordered_map>
#include <memory>

struct _DFont_impl
{
    struct Char
    {
        bool valid = false;
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

    struct FontProperties
    {
        float char_height = 0;
        float char_width = 0;
        float row_spacing = 0;
        float char_spacing = 0;
        int loaded_chars = 0;
        int current_column = 0;
        int current_row = 0;
        int chars_per_row = 0;
        uint8_t* bitmap = nullptr;
    };

    _DFont_impl(unsigned int,std::unordered_map<wchar_t,Char>&&);
    _DFont_impl(const _DFont_impl&) = delete;
    ~_DFont_impl();
 
    static std::tuple<unsigned int,FontProperties,std::unordered_map<wchar_t,Char>> load_font_texture(void* face, unsigned int size);
    static void init_lib();

    void load_additional_char(wchar_t c);
    
    unsigned int texture_id = 0;
    std::unordered_map<wchar_t,Char> chars;
    FontProperties properties; 

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

    static DFont load(const std::string& filename, int size, float row_spacing = 0.0f, float char_spacing = 0.0f);

    bool valid() const;

private:
    std::shared_ptr<_DFont_impl> impl;
    static void init_lib();
};


#endif