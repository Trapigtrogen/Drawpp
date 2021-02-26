static const char* text_shader_f = R"(
    #version 100
    precision mediump float;
    uniform sampler2D texture;
    uniform vec4 fillColor;
    uniform vec4 offset;
    varying vec2 texc;

    void main()
    {
        gl_FragColor = vec4(texture2D(texture,texc));
    }
)";
