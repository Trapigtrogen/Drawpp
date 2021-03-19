static const char* generic_shader_v = R"(
    #version 100
    precision mediump float;
    uniform mat4 transform;
    uniform mat4 view;
    uniform vec4 offset;
    uniform int posmode;
    attribute vec2 pos;
    attribute vec2 texpos;
    varying vec2 texc;

    void main()
    {
        texc = texpos;

        mat4 scale = mat4(1.0);
        scale[0][0] = offset.z;
        scale[1][1] = offset.w;

        mat4 transl = mat4(1.0);

        if(posmode == 0)
        {
            transl[0][3] = (offset.x-(offset.z/2.0));
            transl[1][3] = -(offset.y-(offset.w/2.0));
        }
        else if(posmode == 1)
        {
            transl[0][3] = offset.x;
            transl[1][3] = -offset.y;
        }

        //mat4 mv = scale * transform * transl * view;
        mat4 mv = scale * transl * transform * view;

        gl_Position = vec4(pos,0.0,1.0) * mv;
    }
)";