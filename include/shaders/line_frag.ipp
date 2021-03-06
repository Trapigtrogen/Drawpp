static const char* line_shader_f = R"(
    #version 100
    precision mediump float;

    // x = strokeWeight, y = captype
    uniform vec2 strokeWeight;

    uniform vec4 strokeColor;
    varying vec2 texc;
    varying vec2 size;

    void main()
    {
        if(strokeWeight.y > 0.5)
        {
            vec2 px = vec2(1.0) / size;

            vec2 stroke = strokeWeight.xx * px / 2.0;

            vec2 pos = texc;

            bool ed = false;

            if(1.0 - texc.y < stroke.y)
            {
                pos.y = 1.0 - texc.y;
                ed = true;
            }

            if(texc.y < stroke.y || ed)
            {
                pos.y = 1.0 - (pos.y / stroke.y);
                pos.x = pos.x * 2.0 - 1.0;

                if(length(pos) > 1.0)
                {
                    discard;
                }
            }
        }
        gl_FragColor = strokeColor;
    }
)";