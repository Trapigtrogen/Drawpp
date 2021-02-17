const char* rect_shader_f = R"(
    #version 100
    precision mediump float;
    uniform float strokeWeight;
    uniform vec4 strokeColor;
    uniform vec4 fillColor;
    uniform vec4 offset;
    uniform vec4 radii;
    varying vec2 texc;

    float atan2(float y, float x)
    {
        bool s = (abs(x) > abs(y));
        return mix(radians(180.0)/2.0 - atan(x,y), atan(y,x), float(s));
    }

    void main()
    {
        vec2 off1 = vec2(1.0) / offset.zw;
        vec2 stroke = off1 * strokeWeight;
        
        vec4 radii2 = clamp(radii, vec4(0.0),vec4(min(offset.z,offset.w)/2.0));
        vec2 rad;
        vec2 tpos;
        bool corner = false;
        bool ystroke = false;
        bool xstroke = false;
        

        //topleft
        if(texc.x < 0.5 && texc.y > 0.5)
        {
            if(radii2.x != 0.0)
            {
                rad = vec2(radii2.x) * off1;
            }

            if(texc.x < rad.x && texc.y > 1.0-rad.y)
            {
                tpos = (texc - vec2(0.0,1.0-rad.y)) / rad;
                tpos = vec2(1.0-tpos.x,tpos.y);
                corner = true;
            }
            else
            {
                ystroke = (texc.y < 1.0 && texc.y > 1.0-stroke.y);
                xstroke = (texc.x > 0.0 && texc.x < stroke.x);  
            }
        }
        //topright
        else if(texc.x > 0.5 && texc.y > 0.5)
        {
            if(radii2.y != 0.0)
            {
                rad = vec2(radii2.y) * off1;
            }

            if(texc.x > 1.0-rad.x && texc.y > 1.0-rad.y)
            {
                tpos = (texc - vec2(1.0-rad.x,1.0-rad.y)) / rad;
                corner = true;
            }
            else
            {
                ystroke = (texc.y < 1.0 && texc.y > 1.0-stroke.y);
                xstroke = (texc.x < 1.0 && texc.x > 1.0-stroke.x);
            }
        }
        //bottomright
        else if(texc.x > 0.5 && texc.y < 0.5)
        {
            if(radii2.z != 0.0)
            {
                rad = vec2(radii2.z) * off1;
            }
            
            if(texc.x > 1.0-rad.x && texc.y < rad.y)
            {
                tpos = (texc - vec2(1.0-rad.x,0.0)) / rad;
                tpos = vec2(tpos.x,1.0-tpos.y);
                corner = true;
            }
            else
            {
                ystroke = (texc.y > 0.0 && texc.y < stroke.y);
                xstroke = (texc.x < 1.0 && texc.x > 1.0-stroke.x);
            }
        }
        //bottomleft
        else if(texc.x < 0.5 && texc.y < 0.5)
        {
            if(radii2.w != 0.0)
            {
                rad = vec2(radii2.w) * off1;
            }
            
            if(texc.x < rad.x && texc.y < rad.y)
            {
                tpos = vec2(1.0) - (texc / rad);
                corner = true;
            }
            else
            {
                ystroke = (texc.y > 0.0 && texc.y < stroke.y);
                xstroke = (texc.x > 0.0 && texc.x < stroke.x);
            }
        }

        if(corner)
        {
            vec2 str = stroke * (vec2(1.0) / rad);

            float l = length(tpos);

            float ang = atan2(tpos.x, tpos.y);
            vec2 dir = vec2(cos(ang),sin(ang));

            vec2 p2 = stroke / rad;
            p2.x = p2.x * abs(cos(ang));
            p2.y = p2.y * abs(sin(ang));
            float sl = length(p2);

            if(l <= 1.0 && l >= 1.0-sl)
            {
                gl_FragColor = strokeColor;
            }
            else if(l < 1.0-sl)
            {
                gl_FragColor = fillColor;
            }
            else
            {
                discard;
            }
        }
        else
        {
            if(ystroke || xstroke)
            {
                gl_FragColor = strokeColor;
            }
            else
            {
                gl_FragColor = fillColor;
            }
        }

        //simple rect, no rounded corners
        //bool ystroke = (texc.y > 0.0 && texc.y < stroke.y) || (texc.y < 1.0 && texc.y > 1.0-stroke.y);
        //bool xstroke = (texc.x > 0.0 && texc.x < stroke.x) || (texc.x < 1.0 && texc.x > 1.0-stroke.x);
        //
        //if(ystroke || xstroke)
        //{
        //    gl_FragColor = strokeColor;
        //}
        //else
        //{
        //    gl_FragColor = fillColor;
        //}
    }
)";
