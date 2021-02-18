static const char* triangle_shader_v = R"(
    #version 100
    precision mediump float;
    uniform mat4 view;
    attribute vec2 pos;
    varying vec2 vpos;

    void main()
    {
        vpos = pos;
        gl_Position = vec4(pos,0.0,1.0) * view;
    }
)";