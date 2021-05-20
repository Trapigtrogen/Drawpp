static const char* line_shader_v = R"(
    #version 100
    precision mediump float;
    uniform mat4 transform;
    uniform mat4 view;
    uniform vec4 points;

    // x = strokeWeight, y = captype
    uniform vec2 strokeWeight;

    attribute vec2 pos;
    attribute vec2 texpos;
    varying vec2 texc;
    varying vec2 size;

    float atan2(float y, float x)
    {
        bool s = (abs(x) > abs(y));
        return mix(radians(180.0)/2.0 - atan(x,y), atan(y,x), float(s));
    }

    void main()
    {
        vec2 diff = -(points.xy-points.zw);
        vec2 ppos = mix(points.xy,points.zw,0.5);
        float angle = atan2(diff.x,diff.y);
        
        float height = distance(points.xy,points.zw);
        float width = strokeWeight.x;

        height = height + strokeWeight.x * strokeWeight.y;
        
        mat4 transl = mat4(1.0);
        transl[0][3] = ppos.x;
        transl[1][3] = -ppos.y;

        mat4 scale = mat4(1.0);
        scale[0][0] = width;
        scale[1][1] = height;

        mat4 rot = mat4(1.0);
        rot[0][0] = cos(angle);
        rot[0][1] = -sin(angle);
        rot[1][0] = sin(angle);
        rot[1][1] = cos(angle);

        mat4 mv = scale * rot * transl * transform * view;

        texc = texpos;
        size = vec2(width,height);

        gl_Position = vec4(pos,0.0,1.0) * mv;
    }
)";