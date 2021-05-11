#ifndef DPP_FONT_H
#define DPP_FONT_H

#include <string>
#include <memory>

///\brief This class contains more detailed options for font loading
///
///Current implementation might break if the font size is too large,
///and / or if the character set is too large. Keep this is mind especially
///if you set #load_all to true.
struct FontOptions
{
    ///Font size in pixels.
    float size = 20.0f;

    ///Spacing between rows of text in pixels.   
    float row_spacing = 0.0f;

    ///Spacing between characters in pixels.
    float char_spacing = 0.0f;

    ///Characters to load initially.
    std::wstring charset = L"";

    ///Should all available characters be loaded.
    bool load_all = false;
};

struct DFont_impl;

///Font class
class DFont
{
    friend class Application;
    friend class DGraphics;
public:

    DFont() = default;
    DFont(const DFont&) = default;
    DFont(DFont&&) = default;
    ~DFont() = default;


    ///\brief Load a font from a file
    ///
    ///\p size is the font size in pixels. \n
    ///\p row_spacing is the spacing between rows of text in pixels. \n
    ///\p char_spacing is the spacing between characters in pixels. \n
    ///Default character set is loaded initially.
    static DFont load(const std::string& filename, float size, float row_spacing = 0.0f, float char_spacing = 0.0f);


    ///\brief Load a font from a file
    static DFont load(const std::string& filename, const FontOptions& options);


    ///\brief Unload all previously loaded characters, and load a new character set
    void ClearCharset(const std::wstring& new_charset);


    ///\brief Check if this font can be used for drawing text
    bool valid() const;


    ///\copydoc valid() const
    operator bool() const;
    
    DFont& operator=(const DFont&) = default;
    DFont& operator=(DFont&&) = default;

private:
    static void init_lib();
    static void cleanup_lib();
    
    std::shared_ptr<DFont_impl> impl;
};


#endif