#include <ft2build.h>
#include FT_FREETYPE_H

#include <font.hpp>
#include <debug.hpp>
#include <glad/glad.h>
#include <cstdio>
#include <string>
#include <tuple>

const std::wstring dpp_chars = L" aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXyYzZ1234567890!\"@#$%&/{([)]=}?\\+^'*-_.:,;<>|";
//const std::wstring dpp_chars = L" tesxoinrv";


std::tuple<unsigned int,_DFont_impl::FontProperties,std::unordered_map<wchar_t,_DFont_impl::Char>> _DFont_impl::load_font_texture(void* _face, unsigned int size)
{
    FT_Face face = reinterpret_cast<FT_Face>(_face);

    int err = FT_Set_Char_Size(face,0,64*size,0,0);
    if(err)
    {
        dbg::error("Failed to load font at 'set_size'\n\terror: ",err);
    }

    int gl_mx_s = 600;
    //glGetIntegerv(GL_MAX_TEXTURE_SIZE,&gl_mx_s);

    int c_width = (face->bbox.xMax - face->bbox.xMin)*(size / float(face->units_per_EM));
    int width = dpp_chars.length() * c_width;
    int c_height = (face->bbox.yMax - face->bbox.yMin)*(size / float(face->units_per_EM))+1;
    int height = c_height;
    float c_height2 = c_height / 2.0f;
    float c_width2 = c_width / 2.0f;


    int chars_per_row = gl_mx_s / c_width;
    int lel = dpp_chars.length();

    if(chars_per_row < dpp_chars.length())
    {
        width = chars_per_row * c_width;
        height = ((dpp_chars.length() / chars_per_row) + (dpp_chars.length() % chars_per_row))*c_height;
    }

    uint8_t* bitmap = new uint8_t[width*height]();

    std::unordered_map<wchar_t,_DFont_impl::Char> data;

    int loaded_valid = 0;
    int missing_chars = 0;

    int cur_row = 0;
    int cur_col = 0;

    for(int i = 0; i < dpp_chars.length(); ++i,++cur_col)
    {
        wchar_t c = dpp_chars[i];
        int glyph_index = FT_Get_Char_Index(face,c);

        err = FT_Load_Glyph(face,glyph_index,FT_LOAD_DEFAULT);
        if(err)
        {
            dbg::error("Failed to load font at 'load_glyph'\n\terror: ",err);
            data[c].valid = false;
            ++missing_chars;
            --cur_col;
            continue;
        }
        
        err = FT_Render_Glyph(face->glyph,FT_RENDER_MODE_NORMAL);
        if(err)
        {
            dbg::error("Failed to load font at 'render_glyph'\n\terror: ",err);
            data[c].valid = false;
            ++missing_chars;
            --cur_col;
            continue;
        }

        if(cur_col > chars_per_row)
        {
            cur_col = 0;
            cur_row += 1;
        }

        int base_x = (cur_col * c_width) + c_width2 - (face->glyph->bitmap.width / 2.0f);
        int base_y = (cur_row * c_height) + c_height2 - (face->glyph->bitmap.rows / 2.0f);

        data[c].valid = true;
        data[c].tx_pos_x  = base_x;// / float(width);
        data[c].tx_pos_y = base_y;// / float(c_height);
        data[c].tx_width  = face->glyph->bitmap.width;// / float(width);
        data[c].tx_height = face->glyph->bitmap.rows;// / float(c_height);
        data[c].width     = face->glyph->bitmap.width;
        data[c].height    = face->glyph->bitmap.rows;
        data[c].bearing_x = face->glyph->bitmap_left;
        data[c].bearing_y = -face->glyph->bitmap_top;    //y coords inversed
        data[c].advance_x = face->glyph->advance.x;
        data[c].advance_y = face->glyph->advance.y;

        for(int y = 0; y < face->glyph->bitmap.rows; ++y)
        {
            for(int x = 0; x < face->glyph->bitmap.width; ++x)
            {
                bitmap[(y+base_y) * width + base_x + x] =
                    *(face->glyph->bitmap.buffer + y * face->glyph->bitmap.width + x);
            }
        }
    }

    if(missing_chars)
    {
        missing_chars += chars_per_row - (dpp_chars.length() % chars_per_row);
        int rows = missing_chars/chars_per_row;

        height -= rows*c_height;

        if(height == c_height)
        {
            missing_chars -= rows*chars_per_row;
            width -= c_width*missing_chars;
        }
        
        uint8_t* tmp = new uint8_t[width*height];
        if(!tmp)
        {
            dbg::error("Failed to resize font texture.");
            delete[] bitmap;
            return std::tuple<unsigned int,_DFont_impl::FontProperties,std::unordered_map<wchar_t,Char>>(0,{},std::unordered_map<wchar_t,Char>());
        }

        memcpy(tmp,bitmap,width*height);

        delete[] bitmap;
        bitmap = tmp;
    }
    
    for( auto& c : data)
    {
        Char& cc = c.second;

        cc.tx_pos_x /= width;
        cc.tx_width /= width;

        cc.tx_pos_y /= height;
        cc.tx_height /= height;
    }

    unsigned int t_id = 0;
    glGenTextures(1,&t_id);
    glBindTexture(GL_TEXTURE_2D,t_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //this is required so that the texture is correct in the shader
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap);
    
    glBindTexture(GL_TEXTURE_2D, 0);

    _DFont_impl::FontProperties prop;
    prop.char_height = c_height;
    prop.char_width = c_width;
    prop.loaded_chars = loaded_valid;
    prop.current_column = cur_col-1;
    prop.current_row = cur_row;
    prop.chars_per_row = chars_per_row;
    prop.bitmap = bitmap;

    return std::tuple<unsigned int,_DFont_impl::FontProperties,std::unordered_map<wchar_t,Char>>
        (t_id,prop,data);
}

_DFont_impl::_DFont_impl(unsigned int id,std::unordered_map<wchar_t,_DFont_impl::Char>&& cd)
{
    texture_id = id;
    chars = std::move(cd);
}

_DFont_impl::~_DFont_impl()
{
    FT_Done_Face(reinterpret_cast<FT_Face>(font_face));
    delete[] font_data;
    delete[] properties.bitmap;
    glDeleteTextures(1,&texture_id);
}

void _DFont_impl::load_additional_char(wchar_t c)
{
    FT_Face face = reinterpret_cast<FT_Face>(font_face);

    int glyph_index = FT_Get_Char_Index(face,c);

    int err = FT_Load_Glyph(face,glyph_index,FT_LOAD_DEFAULT);
    if(err)
    {
        dbg::error("Failed to load font at 'load_glyph'\n\terror: ",err);
        chars[c].valid = false;
        return;
    }
    
    err = FT_Render_Glyph(face->glyph,FT_RENDER_MODE_NORMAL);
    if(err)
    {
        dbg::error("Failed to load font at 'render_glyph'\n\terror: ",err);
        chars[c].valid = false;
        return;
    }

    ++properties.current_column;
    
    int width = properties.chars_per_row*properties.char_width;
    int height;

    if(properties.current_column > properties.chars_per_row)
    {
        properties.current_row += 1;

        height = (properties.current_row+1) * properties.char_height;

        uint8_t* tmp = new uint8_t[width*height]();

        if(!tmp)
        {
            dbg::error("Failed to reallocate font bitmap for new character: '",c,'\'');
            properties.current_row -= 1;
            return;
        }

        memcpy(tmp,properties.bitmap,width*height);

        delete[] properties.bitmap;

        properties.bitmap = tmp;
        properties.current_column = 0;

        float old_height = properties.current_row * properties.char_height;

        for(auto& c : chars)
        {
            Char& cc = c.second;
            cc.tx_pos_y *= old_height;
            cc.tx_height *= old_height;

            cc.tx_pos_y /= height;
            cc.tx_height /= height;
        }

    }
    else if (properties.current_column < properties.chars_per_row && properties.current_row == 0)
    {
        height = properties.char_height;
        width = (properties.current_column+1)*properties.char_width;

        uint8_t* tmp = new uint8_t[width*height]();

        if(!tmp)
        {
            dbg::error("Failed to reallocate font bitmap for new character: '",c,'\'');
            properties.current_row -= 1;
            return;
        }

        memcpy(tmp,properties.bitmap,width*height);

        delete[] properties.bitmap;

        properties.bitmap = tmp;

        float old_width = properties.current_column * properties.char_width;

        for(auto& c : chars)
        {
            Char& cc = c.second;
            cc.tx_pos_x *= old_width;
            cc.tx_width *= old_width;

            cc.tx_pos_x /= width;
            cc.tx_width /= width;
        }
    }
    else
    {
        height = (properties.current_row+1) * properties.char_height;
    }

    int base_x = ((properties.current_column+0.5f) * properties.char_width) - (face->glyph->bitmap.width / 2.0f);
    int base_y = ((properties.current_row+0.5f) * properties.char_height) - (face->glyph->bitmap.rows / 2.0f);

    chars[c].valid = true;
    chars[c].tx_pos_x  = base_x / float(width);
    chars[c].tx_pos_y = base_y / float(height);
    chars[c].tx_width  = face->glyph->bitmap.width / float(width);
    chars[c].tx_height = face->glyph->bitmap.rows / float(height);
    chars[c].width     = face->glyph->bitmap.width;
    chars[c].height    = face->glyph->bitmap.rows;
    chars[c].bearing_x = face->glyph->bitmap_left;
    chars[c].bearing_y = -face->glyph->bitmap_top;    //y coords inversed
    chars[c].advance_x = face->glyph->advance.x;
    chars[c].advance_y = face->glyph->advance.y;

    for(int y = 0; y < face->glyph->bitmap.rows; ++y)
    {
        for(int x = 0; x < face->glyph->bitmap.width; ++x)
        {
            properties.bitmap[(y+base_y) * width + base_x + x] =
                *(face->glyph->bitmap.buffer + y * face->glyph->bitmap.width + x);
        }
    }

    glDeleteTextures(1,&texture_id);

    glGenTextures(1,&texture_id);
    glBindTexture(GL_TEXTURE_2D,texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, properties.bitmap);
    
    glBindTexture(GL_TEXTURE_2D, 0);

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

DFont DFont::load(const std::string& fname, int size, float row_spacing, float char_spacing)
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


    if(err)
    {
        dbg::error("Failed to loaf font data '", fname, "', error: ", err);
        return DFont();
    }

    std::tuple<unsigned int,_DFont_impl::FontProperties, std::unordered_map<wchar_t, _DFont_impl::Char>> r = _DFont_impl::load_font_texture(face,size);

    //don't delete data, if you wanna keep the face stored, as it's only maps the data, not copy
    //delete[] data;

    unsigned int t = std::get<0>(r);
    std::unordered_map<wchar_t, _DFont_impl::Char>& m = std::get<2>(r);

    if(!t)
    {
        dbg::error("Failed to load font texture'", fname, "'");
        return DFont();
    }

    DFont result;
    result.impl = std::shared_ptr<_DFont_impl>(new _DFont_impl(t,std::move(m)));

    result.impl->properties = std::get<1>(r);
    result.impl->properties.row_spacing = row_spacing;
    result.impl->properties.char_spacing = char_spacing;
    result.impl->font_data = data;
    result.impl->font_face = face;

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