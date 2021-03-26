static const char* text_shader_v = R"(
    #version 100
    precision mediump float;
    uniform mat4 transform;
    uniform mat4 view;
    attribute vec2 pos;
    attribute vec2 texpos;
    varying vec2 texc;

    void main()
    {
        texc = texpos;
        gl_Position = vec4(pos,0.0,1.0) * (transform * view);
    }
)";