#include <ft2build.h>
#include FT_FREETYPE_H

#include <font.hpp>
#include <debug.hpp>
#include <glad/glad.h>
#include <cstdio>
#include <string>
#include <tuple>


const std::wstring dpp_chars = L" aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ1234567890!\"@#$%&/{([)]=}?\\+^'*-_.:,;<>|";

std::tuple<unsigned int,std::unordered_map<wchar_t,_DFont_impl::Char>> _DFont_impl::load_font_texture(void* _face, unsigned int size)
{
    #define _ERR(where) if(err){dbg::error("Failed to load font at ",#where,"\n\terror: ",err); return std::tuple<unsigned int,std::unordered_map<wchar_t,_DFont_impl::Char>>(0u,std::unordered_map<wchar_t,_DFont_impl::Char>());}

    FT_Face face = reinterpret_cast<FT_Face>(_face);

    int err = FT_Set_Char_Size(face,0,64*size,0,0);
    _ERR(set_size)

    int c_width = (face->bbox.xMax - face->bbox.xMin)*(size / float(face->units_per_EM));
    int width = dpp_chars.length() * c_width;
    int height = (face->bbox.yMax - face->bbox.yMin)*(size / float(face->units_per_EM))+1;
    float height2 = height / 2.0f;
    float c_width2 = c_width / 2.0f;

    //uint32_t* bitmap = new uint32_t[width*height];
    uint8_t* bitmap = new uint8_t[width*height];

    std::unordered_map<wchar_t,_DFont_impl::Char> data;

    for(int i = 0; i < dpp_chars.length(); ++i)
    {
        wchar_t c = dpp_chars[i];
        int glyph_index = FT_Get_Char_Index(face,c);

        err = FT_Load_Glyph(face,glyph_index,FT_LOAD_DEFAULT);
        //std::cerr << i << '\n';
        _ERR(load_glyph)
        
        err = FT_Render_Glyph(face->glyph,FT_RENDER_MODE_NORMAL);
        _ERR(render_glyph)

        int base_x = ((i * c_width) + c_width2 - (face->glyph->bitmap.width / 2.0f));
        int base_y = height2 - (face->glyph->bitmap.rows / 2.0f);

        data[c].tx_pos_x = base_x / width;
        data[c].tx_pos_y = base_y  / height;
        data[c].tx_width = face->glyph->bitmap.width / width;
        data[c].tx_height = face->glyph->bitmap.rows / height;
        data[c].width = face->glyph->bitmap.width;
        data[c].height = face->glyph->bitmap.rows;
        data[c].bearing_x = face->glyph->bitmap_left;
        data[c].bearing_y = face->glyph->bitmap_top;
        data[c].advance_x = face->glyph->advance.x;
        data[c].advance_y = face->glyph->advance.y;

        for(int y = 0; y < face->glyph->bitmap.rows; ++y)
        {
            for(int x = 0; x < face->glyph->bitmap.width; ++x)
            {
                bitmap[(y+base_y) * width + base_x + x] =
                *(face->glyph->bitmap.buffer + y * face->glyph->bitmap.width + x);
                //printf("%s",bitmap[(y+base_y) * width + base_x + x]>0?"1":"0");
            }
            //printf("\n");
        }
        //printf("\n");
    }

    unsigned int t_id = 0;
    glGenTextures(1,&t_id);
    glBindTexture(GL_TEXTURE_2D,t_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap);
    
    glBindTexture(GL_TEXTURE_2D, 0);

    delete[] bitmap;

    return std::tuple<unsigned int, std::unordered_map<wchar_t, _DFont_impl::Char>>(t_id,data);
}

_DFont_impl::_DFont_impl(unsigned int id,std::unordered_map<wchar_t,_DFont_impl::Char>&& cd)
{
    texture_id = id;
    chars = std::move(cd);
}

void _DFont_impl::init_lib()
{
    if(lib_ptr == nullptr)
    {
        int e = FT_Init_FreeType(reinterpret_cast<FT_Library*>(&lib_ptr));

        if(e)
        {
            dbg::error("Failed to initialize freetype: ", e);
        }
    }
}

DFont DFont::load(const std::string& fname, int size)
{
    if(size < 1) return DFont();

    FILE* f = std::fopen(fname.data(),"rb");

    if(f == nullptr)
    {
        dbg::error("Failed to load font file: ", fname);
        return DFont();
    }

    fseek(f,0,SEEK_END);
    size_t l = ftell(f);
    fseek(f,0,SEEK_SET);

    unsigned char* data = new unsigned char[l+1];
    data[l] = 0;

    fread(data,1,l,f);

    FT_Face face;

    int err = FT_New_Memory_Face(reinterpret_cast<FT_Library>(_DFont_impl::lib_ptr),data,l,0,&face);

    delete[] data;

    if(err)
    {
        dbg::error("Failed to loaf font data '", fname, "', error: ", err);
        return DFont();
    }

    std::tuple<unsigned int, std::unordered_map<wchar_t, _DFont_impl::Char>> r = _DFont_impl::load_font_texture(face,size);

    unsigned int t = std::get<0>(r);
    std::unordered_map<wchar_t, _DFont_impl::Char>& m = std::get<1>(r);

    if(!t)
    {
        dbg::error("Failed to load font texture'", fname, "'");
        return DFont();
    }

    DFont result;
    result.impl = std::shared_ptr<_DFont_impl>(new _DFont_impl(t,std::move(m)));

    return result;
}

void DFont::init_lib()
{
    _DFont_impl::init_lib();
}

bool DFont::valid() const
{
    return bool(impl);
}

void* _DFont_impl::lib_ptr = nullptr;