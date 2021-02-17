const char* triangle_shader_f = R"(
    #version 100
    precision mediump float;
    uniform float strokeWeight;
    uniform vec4 strokeColor;
    uniform vec4 fillColor;
    uniform float bpos[6];
    varying vec2 vpos;

    float pointLineDist(vec2 point, vec2 l1, vec2 l2)
    {
        vec2 cd = l2 - l1;
        vec2 ef = vec2(-cd.y,cd.x);
        return abs(dot(point - l1,ef)) / length(ef);
    }

    void main()
    {
        if(pointLineDist(vpos.xy,vec2(bpos[0],bpos[1]),vec2(bpos[2],bpos[3])) <= strokeWeight ||
            pointLineDist(vpos.xy,vec2(bpos[2],bpos[3]),vec2(bpos[4],bpos[5])) <= strokeWeight ||
            pointLineDist(vpos.xy,vec2(bpos[4],bpos[5]),vec2(bpos[0],bpos[1])) <= strokeWeight )
        {
            gl_FragColor = strokeColor;
        }
        else
        {
            gl_FragColor = fillColor;
        }

    }
)";