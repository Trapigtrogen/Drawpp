static const char* image_shader_f = R"(
    #version 100
    precision mediump float;
    uniform sampler2D tex;
    varying vec2 texc;

    void main()
    {
        gl_FragColor = texture2D(tex,texc);
        //gl_FragColor = vec4(1.0,0.0,0.0,1.0);
    }
)";