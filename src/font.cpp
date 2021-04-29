#include <ft2build.h>
#include FT_FREETYPE_H

#include <font.hpp>
#include <font_impl.h>
#include <debug.hpp>
#include <glad.h>
#include <string>
#include <algorithm>

static const std::wstring default_charset = L" aAbBcCdDeEfFgGhHiIjJkKlLmMnNoOpPqQrRsStTuUvVwWxXy"
"YzZ1234567890!\"@#$%&/{([)]=}?\\+^'*-_.:,;<>|";

DFont_impl* DFont_impl::load_font(void* _face, const FontOptions& options)
{
    std::wstring charset = options.charset;
    charset.insert(charset.begin(),L'\0');

    auto ed = charset.end();
    for(auto it = charset.begin(); it != ed; ++it)
    {
        ed = std::remove(std::next(it),ed,*it);
    }
    charset.erase(ed,charset.end());

    int charset_len = int(charset.length());

    FT_Face face = reinterpret_cast<FT_Face>(_face);

    int gl_mx_s;// = 2000;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE,&gl_mx_s);

    float size = options.size;

    int err = FT_Set_Char_Size(face,0,64*size,0,0);
    if(err)
    {
        dbg::error("Failed to load font at 'set_size'\n\terror: ",err);
    }

    float mul = size / face->units_per_EM;
    int c_width = (face->bbox.xMax - face->bbox.xMin)*mul;
    int width = charset_len * c_width;
    int c_height = (face->bbox.yMax - face->bbox.yMin)*mul+1;
    int height = c_height;
    float c_height2 = c_height / 2.0f;
    float c_width2 = c_width / 2.0f;

    float baseline = std::abs(face->descender) * mul;

    if (c_height > gl_mx_s || c_width > gl_mx_s)
    {
        dbg::error("Not enough texture space: font size = ", c_width,'x',c_height, ", max size = ", gl_mx_s);
        return nullptr;
    }

    int chars_per_row = gl_mx_s / c_width;
    int chars_per_col = gl_mx_s / c_height;

    if(chars_per_row < charset_len)
    {
        width = chars_per_row * c_width;
        height = ((charset_len / chars_per_row) + (1 && (charset_len % chars_per_row)));

        if(height > chars_per_col)
        {
            height = chars_per_col;
        }

        height *= c_height;
        
    }

    uint8_t* bitmap = new uint8_t[width*height]();

    std::unordered_map<wchar_t,DFont_impl::Char> data;

    int loaded_valid = 0;

    int cur_row = 0;
    int cur_col = 0;

    for(int i = 0; i < charset_len; ++i,++cur_col)
    {
        wchar_t c = charset[i];
        int glyph_index = FT_Get_Char_Index(face,c);

        if(FT_Load_Glyph(face,glyph_index,FT_LOAD_DEFAULT) || 
            FT_Render_Glyph(face->glyph,FT_RENDER_MODE_NORMAL))
        {
            dbg::error("Failed to load or render character: ",c);
            if(c == L'\0')
            {
                delete[] bitmap;
                return nullptr;
            }
            data[c] = data[L'\0'];
            --cur_col;
            continue;
        }

        if(cur_col >= chars_per_row)
        {
            cur_col = 0;
            cur_row += 1;
        }

        if(cur_row >= chars_per_col)
        {
            dbg::error("Ran out of texture space for font at ", c,"\n\t",i,"(",loaded_valid,") characters loaded.");
            
            for(;i<charset_len; ++i)
            {
                c = charset[i];
                data[c] = data[L'\0'];
            }
            cur_col = chars_per_row-1;
            --cur_row;
            goto no_space;
        }

        int base_x = (cur_col * c_width) + c_width2 - (face->glyph->bitmap.width / 2.0f);
        int base_y = (cur_row * c_height) + c_height2 - (face->glyph->bitmap.rows / 2.0f);

        data[c].tx_pos_x  = base_x;
        data[c].tx_pos_y = base_y;
        data[c].tx_width  = face->glyph->bitmap.width;
        data[c].tx_height = face->glyph->bitmap.rows;
        data[c].width     = face->glyph->bitmap.width;
        data[c].height    = face->glyph->bitmap.rows;
        data[c].bearing_x = face->glyph->bitmap_left;
        data[c].bearing_y = -face->glyph->bitmap_top;    //y coords inversed
        data[c].advance_x = face->glyph->advance.x;
        data[c].advance_y = face->glyph->advance.y;

        for(unsigned int y = 0; y < face->glyph->bitmap.rows; ++y)
        {
            for(unsigned int x = 0; x < face->glyph->bitmap.width; ++x)
            {
                bitmap[(y+base_y) * width + base_x + x] =
                    *(face->glyph->bitmap.buffer + y * face->glyph->bitmap.width + x);
            }
        }
        ++loaded_valid;
    }

    --cur_col;

    no_space:

    //divide texture coordinates to 0..1 range
    for( auto& c : data)
    {
        Char& cc = c.second;

        cc.tx_pos_x /= width;
        cc.tx_width /= width;

        cc.tx_pos_y /= height;
        cc.tx_height /= height;
    }

    DFont_impl* result = new DFont_impl;

    result->chars = std::move(data);
    result->font_face = _face;
    result->font_size = options.size;
    result->row_spacing = options.row_spacing;
    result->char_spacing = options.char_spacing;
    result->char_height = c_height;
    result->char_width = c_width;
    result->baseline = baseline;
    result->loaded_chars = loaded_valid;
    result->current_column = cur_col;
    result->current_row = cur_row;
    result->chars_per_row = chars_per_row;
    result->chars_per_col = chars_per_col;
    result->bitmap = bitmap;

    return result;
}

DFont_impl::~DFont_impl()
{
    FT_Done_Face(reinterpret_cast<FT_Face>(font_face));
    delete[] font_data;
    delete[] bitmap;
    glDeleteTextures(1,&texture_id);
}

bool DFont_impl::load_additional_char(wchar_t c)
{
    FT_Face face = reinterpret_cast<FT_Face>(font_face);

    int glyph_index = FT_Get_Char_Index(face,c);

    if(FT_Load_Glyph(face,glyph_index,FT_LOAD_DEFAULT) || 
        FT_Render_Glyph(face->glyph,FT_RENDER_MODE_NORMAL))
    {
        dbg::error("Failed to load or render additional character: ",c);
        chars[c] = chars[L'\0'];
        return false;
    }

    ++current_column;
    
    int width = chars_per_row*char_width;
    int height;

    if(current_column >= chars_per_row)
    {
        if(current_row+1 >= chars_per_col)
        {
            dbg::error("Ran out of texture space for font when trying to load additional character: ",c);
            chars[c] = chars[L'\0'];
            --current_column;
            return false;
        }

        ++current_row;

        height = (current_row+1) * char_height;

        uint8_t* tmp = new uint8_t[width*height]();

        if(!tmp)
        {
            dbg::error("Failed to reallocate font bitmap for additional character: '",c,'\'');
            --current_row;
            --current_column;
            return false;
        }

        memcpy(tmp,bitmap,width*height);

        delete[] bitmap;

        bitmap = tmp;
        current_column = 0;

        float old_height = current_row * char_height;

        for(auto& c : chars)
        {
            Char& cc = c.second;
            cc.tx_pos_y *= old_height;
            cc.tx_height *= old_height;

            cc.tx_pos_y /= height;
            cc.tx_height /= height;
        }

    }
    else if (current_column < chars_per_row && current_row == 0)
    {
        height = char_height;
        width = (current_column+1)*char_width;

        uint8_t* tmp = new uint8_t[width*height]();

        if(!tmp)
        {
            dbg::error("Failed to reallocate font bitmap for additional character: '",c,'\'');
            --current_column;
            return false;
        }

        int old_width = current_column * char_width;

        for(int i = 0; i < height; ++i)
        {
            memcpy(tmp + width * i, bitmap + old_width * i, old_width);
        }

        delete[] bitmap;

        bitmap = tmp;

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
        height = (current_row+1) * char_height;
    }

    int base_x = ((current_column+0.5f) * char_width) - (face->glyph->bitmap.width / 2.0f);
    int base_y = ((current_row+0.5f) * char_height) - (face->glyph->bitmap.rows / 2.0f);

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

    for(unsigned int y = 0; y < face->glyph->bitmap.rows; ++y)
    {
        for(unsigned int x = 0; x < face->glyph->bitmap.width; ++x)
        {
            bitmap[(y+base_y) * width + base_x + x] =
                *(face->glyph->bitmap.buffer + y * face->glyph->bitmap.width + x);
        }
    }

    ++loaded_chars;

    return true;
}

void DFont_impl::load_all_chars()
{
    FT_Face face = reinterpret_cast<FT_Face>(font_face);

    int num_glyphs = 0;

    if(FT_IS_CID_KEYED(face))
    {
        unsigned int ix = 0;
        unsigned long i = FT_Get_First_Char(face,&ix);

        if(ix == 0)
        {
            return;
        }

        ++num_glyphs;

        while(1)
        {
            i = FT_Get_Next_Char(face,i,&ix);

            if(ix == 0)
            {
                break;
            }
            ++num_glyphs;
        }
    }
    else
    {
        num_glyphs = face->num_glyphs;
    }
    ++num_glyphs;

    int width;
    int old_w;

    if(num_glyphs > chars_per_row)
    {
        width = chars_per_row;
        
        if(current_row > 0)
        {
            old_w = width;
        }
        else
        {
            old_w = (current_column+1);
        }
    }
    else
    {
        width = num_glyphs;
        old_w = (current_column+1);
    }

    int height = (num_glyphs / chars_per_row) + (1 && (num_glyphs % chars_per_row));
    int old_h = (current_row+1);
    
    float mul_height = (current_row+1) * char_height;
    float mul_width = old_w * char_width;

    width *= char_width;
    old_w *= char_width;

    if(height > chars_per_col)
    {
        height = chars_per_row;
    }

    height *= char_height;
    old_h  *= char_height;

    uint8_t* tmp = new uint8_t[width*height]();

    if(!tmp)
    {
        dbg::error("Failed to reallocate font bitmap for all characters");
        return;
    }

    for(auto& c : chars)
    {
        Char& cc = c.second;
        cc.tx_pos_y *= mul_height;
        cc.tx_height *= mul_height;
        cc.tx_pos_x *= mul_width;
        cc.tx_width *= mul_width;
    }

    if(current_column >= chars_per_row || current_row > 0)
    {
        memcpy(tmp,bitmap,old_w*old_h);
        current_column = 0;
    }
    else if (current_column < chars_per_row && current_row == 0)
    {
        for(int i = 0; i < old_h; ++i)
        {
            memcpy(tmp + width * i, bitmap + old_w * i, old_w);
        }
    }

    delete[] bitmap;
    bitmap = tmp;

    int loaded_valid = 0;
    float c_width2 = char_width/2;
    float c_height2 = char_height/2;
    
    unsigned int glyph_index = 0;
    unsigned long c = FT_Get_First_Char(face,&glyph_index);
    goto initial;

    while(true)
    {
        c = FT_Get_Next_Char(face,c,&glyph_index);

        initial:

        if(glyph_index == 0)
        {
            break;
        }

        if(chars.find(c) != chars.end())
        {
            continue;
        }

        if(FT_Load_Glyph(face,glyph_index,FT_LOAD_DEFAULT) || 
            FT_Render_Glyph(face->glyph,FT_RENDER_MODE_NORMAL))
        {
            dbg::error("Failed to load or render character: ",c);
            chars[c] = chars[L'\0'];
            --current_column;
            continue;
        }

        if(current_column >= chars_per_row)
        {
            current_column = 0;
            current_row += 1;
        }

        if(current_row >= chars_per_col)
        {
            dbg::error("Ran out of texture space for font at ", c,"\n\t",
            chars_per_col*current_row + current_column,",",loaded_valid,
            "(",loaded_chars+loaded_valid,") characters loaded.");
            
            while(glyph_index)
            {
                c = FT_Get_Next_Char(face,c,&glyph_index);
                chars[c] = chars[L'\0'];
            }
            current_column = chars_per_row-1;
            --current_row;
            goto no_space;
        }

        int base_x = (current_column * char_width) + c_width2 - (face->glyph->bitmap.width / 2.0f);
        int base_y = (current_row * char_height) + c_height2 - (face->glyph->bitmap.rows / 2.0f);

        chars[c].tx_pos_x  = base_x;
        chars[c].tx_pos_y = base_y;
        chars[c].tx_width  = face->glyph->bitmap.width;
        chars[c].tx_height = face->glyph->bitmap.rows;
        chars[c].width     = face->glyph->bitmap.width;
        chars[c].height    = face->glyph->bitmap.rows;
        chars[c].bearing_x = face->glyph->bitmap_left;
        chars[c].bearing_y = -face->glyph->bitmap_top;    //y coords inversed
        chars[c].advance_x = face->glyph->advance.x;
        chars[c].advance_y = face->glyph->advance.y;

        for(unsigned int y = 0; y < face->glyph->bitmap.rows; ++y)
        {
            for(unsigned int x = 0; x < face->glyph->bitmap.width; ++x)
            {
                bitmap[(y+base_y) * width + base_x + x] =
                    *(face->glyph->bitmap.buffer + y * face->glyph->bitmap.width + x);
            }
        }
        ++loaded_valid;
        ++current_column;
    }

    --current_column;

    no_space:

    for( auto& c : chars)
    {
        Char& cc = c.second;

        cc.tx_pos_x /= width;
        cc.tx_width /= width;

        cc.tx_pos_y /= height;
        cc.tx_height /= height;
    }

    loaded_chars += loaded_valid;
}

void DFont_impl::apply_texture()
{
    if(texture_id != 0)
    {
        glDeleteTextures(1,&texture_id);
    }

    glGenTextures(1,&texture_id);

    glBindTexture(GL_TEXTURE_2D,texture_id);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //this is required so that the texture is correct in the shader
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    int width = chars_per_row * char_width;

    if(current_row > 0)
    {
        width = chars_per_row * char_width;
    }
    else
    {
        width = (current_column+1) * char_width;
    }

    int height = (current_row+1) * char_height;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap);
    
    glBindTexture(GL_TEXTURE_2D, 0);
}

void DFont_impl::init_lib()
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

DFont DFont::load(const std::string& filename, float size, float row_spacing, float char_spacing)
{
    static FontOptions opt;
    opt.size = size;
    opt.char_spacing = char_spacing;
    opt.row_spacing = row_spacing;
    opt.charset = default_charset;
    opt.load_all = false;
    
    return load(filename,opt);
}

DFont DFont::load(const std::string& filename, const FontOptions& options)
{
    if(options.size <= 0) return DFont();

    FILE* f = std::fopen(filename.data(),"rb");

    if(f == nullptr)
    {
        dbg::error("Failed to load font file: ", filename);
        return DFont();
    }

    fseek(f,0,SEEK_END);
    unsigned int l = ftell(f);
    fseek(f,0,SEEK_SET);

    unsigned char* data = new unsigned char[l+1];
    data[l] = 0;

    fread(data,1,l,f);
    fclose(f);

    FT_Face face;

    int err = FT_New_Memory_Face(reinterpret_cast<FT_Library>(DFont_impl::lib_ptr),data,l,0,&face);

    if(err)
    {
        dbg::error("Failed to loaf font data '", filename, "', error: ", err);
        delete[] data;
        return DFont();
    }

    if(data == nullptr)
    {
        return DFont();
    }

    std::shared_ptr<DFont_impl> font_impl = std::shared_ptr<DFont_impl>(DFont_impl::load_font(face,options));
    
    if(!font_impl)
    {
        dbg::error("Failed to load font texture'", filename, "'");
        FT_Done_Face(face);
        delete[] data;
        return DFont();
    }

    DFont result;
    result.impl = font_impl;
    result.impl->font_data = data;

    if(options.load_all)
    {
        result.impl->load_all_chars();
    }

    result.impl->apply_texture();

    return result;
}

void DFont::init_lib()
{
    DFont_impl::init_lib();
}

void DFont::ClearCharset(const std::wstring& new_charset)
{
    if(!valid())
    {
        dbg::error("Could not clear charset: the font is not in a valid state");
        return;
    }

    FontOptions opt;

    opt.char_spacing = impl->char_spacing;
    opt.row_spacing = impl->row_spacing;
    opt.size = impl->font_size;
    opt.load_all = false;
    opt.charset = new_charset;

    DFont_impl* nfont = DFont_impl::load_font(impl->font_face,opt);

    if(!nfont)
    {
        dbg::error("Could not clear charset");
        return;
    }

    nfont->font_data = impl->font_data;
    impl->font_data = nullptr;
    impl->font_face = nullptr;

    impl = std::shared_ptr<DFont_impl>(nfont);
}

bool DFont::valid() const
{
    return bool(impl);
}

DFont::operator bool() const
{
    return valid();
}

void* DFont_impl::lib_ptr = nullptr;