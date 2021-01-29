#ifndef DPP_GRAPHICS_H
#define DPP_GRAPHICS_H

class DGraphics
{
public:

    DGraphics(int width, int height);

    ///\brief Set this DGraphics object to be the current render target
    void beginDraw();

    ///\brief Explicitly end drawing to this buffer
    ///
    ///This does not need to be called if you call beginDraw() on another DGraphics object.
    void endDraw();

private:

    void set_current();

    unsigned int buffer_id = -1;
    unsigned int texture_id = -1;
    unsigned int buffer_width = 0;
    unsigned int buffer_height = 0;

    //static unsigned int current_bound_buffer;
    //static unsigned int previous_bound_buffer;
};

#endif