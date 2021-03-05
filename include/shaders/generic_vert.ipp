static const char* generic_shader_v = R"(
    #version 100
    precision mediump float;
    //uniform mat4 transform;
    uniform mat4 view;
    uniform vec4 offset;
    uniform int posmode;
    attribute vec2 pos;
    attribute vec2 texpos;
    varying vec2 texc;

    void main()
    {
        texc = texpos;

        mat4 transf = mat4(1.0);
        transf[0][0] = transf[0][0] + offset.z;
        transf[1][1] = transf[1][1] + offset.w;

        if(posmode == 0)
        {
            transf[0][3] = transf[0][3] + (offset.x-(offset.z/2.0));
            transf[1][3] = transf[1][3] - (offset.y-(offset.w/2.0));
        }
        else if(posmode == 1)
        {
            transf[0][3] = transf[0][3] + offset.x;
            transf[1][3] = transf[1][3] - offset.y;
        }

        mat4 mv = transf * view;

        gl_Position = vec4(pos,0.0,1.0) * mv;
    }
)";