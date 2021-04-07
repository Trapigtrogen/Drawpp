const char* generic_colored_shader_v = R"(
    #version 100
    precision mediump float;
    uniform mat4 view;
    uniform mat4 transform;
    attribute vec2 pos;
    
    void main()
    {
        gl_Position = vec4(pos,0.0,1.0) * (transform * view);
    }
)";