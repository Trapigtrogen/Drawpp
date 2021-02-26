#ifndef DPP_FONT_H
#define DPP_FONT_H

#include <string>
#include <unordered_map>
#include <memory>

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
        float advance_y;
    };

    _DFont_impl(unsigned int,std::unordered_map<wchar_t,Char>&&);
    _DFont_impl(const _DFont_impl&) = delete;
 
    static std::tuple<unsigned int,std::unordered_map<wchar_t,Char>> load_font_texture(void* face, unsigned int size);
    static void init_lib();
    
    unsigned int texture_id = 0;
    std::unordered_map<wchar_t,Char> chars;

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

    DFont& operator=(const DFont&) = default;
    DFont& operator=(DFont&&) = default;

    static DFont load(const std::string& filename, int size);

    bool valid() const;

private:
    std::shared_ptr<_DFont_impl> impl;
    static void init_lib();
};


#endif