static const char* quad_shader_f = R"(
    #version 100
    precision mediump float;
    uniform float strokeWeight;
    uniform vec4 strokeColor;
    uniform vec4 fillColor;
    uniform float bpos[12];
    varying vec2 vpos;

    float pointLineSegDist(vec2 point, vec2 l1, vec2 l2) {
        vec2 c = (l1 + l2) * 0.5;
        float l = length(l2 - l1);
        vec2 d = (l2 - l1) / l;
        vec2 r = point - c;
        return max(abs(dot(r, vec2(d.y, -d.x))), abs(dot(r, d)) - 0.5*l);
    }

    void main()
    {
        if(pointLineSegDist(vpos.xy,vec2(bpos[0],bpos[1]),vec2(bpos[2],bpos[3])) <= strokeWeight ||
            pointLineSegDist(vpos.xy,vec2(bpos[0],bpos[1]),vec2(bpos[4],bpos[5])) <= strokeWeight ||

            pointLineSegDist(vpos.xy,vec2(bpos[6],bpos[7]),vec2(bpos[8],bpos[9])) <= strokeWeight ||
            pointLineSegDist(vpos.xy,vec2(bpos[6],bpos[7]),vec2(bpos[10],bpos[11])) <= strokeWeight )
        {
            gl_FragColor = strokeColor;
        }
        else
        {
            gl_FragColor = fillColor;
        }

    }
)";