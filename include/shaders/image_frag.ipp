static const char* image_shader_f = R"(
    #version 100
    precision mediump float;
    uniform sampler2D tex;
    uniform bool useTint;
    uniform vec4 tint;
    varying vec2 texc;

    void main()
    {
        if(!useTint)
        {
            gl_FragColor = texture2D(tex,texc);
        }
        else
        {
            vec4 texcol = texture2D(tex,texc);
            gl_FragColor = tint*vec4(vec3((texcol.x+texcol.y+texcol.z)/3.0),texcol.w);
        }
    }
)";