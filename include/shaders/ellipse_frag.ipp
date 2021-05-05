static const char* ellipse_shader_f = R"(
    #version 100
    precision mediump float;
    uniform float strokeWeight;
    uniform vec4 strokeColor;
    uniform vec4 fillColor;
    uniform vec4 offset;
    varying vec2 texc;

    float atan2(in float y, in float x)
    {
        bool s = (abs(x) > abs(y));
        return mix(radians(180.0)/2.0 - atan(x,y), atan(y,x), float(s));
    }

    void main()
    {
/*
        vec2 tc = abs(texc*2.0 - 1.0);
        float l = length(tc);

        float ang = atan2(tc.x,tc.y);
        vec2 dir = vec2(cos(ang),sin(ang));

        //something wrong here, stroke len too large. mult by 0.66 to make better, but 
        //it's not accurate still. also skews if width != height, so maybe this is shit overall
        //float d2 = 1.0 - length(vec2(strokeWeight * 0.666) / (offset.wz / 2.0));

        //this one makes a correct stroke width, if width == height.
        //weird artefact will happen if width != height.
        //using this for now because it's the best we got
        vec2 p2 = (vec2(1.0) / (offset.wz / 2.0)) * vec2(strokeWeight);
        p2.x = p2.x * abs(cos(ang));
        p2.y = p2.y * abs(sin(ang));
        float d2 = length(dir-p2);

        if(l < 1.0 && l > d2)
        {
            gl_FragColor = strokeColor;
        }
        else if(l <= d2)
        {
            gl_FragColor = fillColor;
        }
        else
        {
            discard;
        }
*/


        // Other
        vec2 tc = abs(texc*2.0 - 1.0);

        float x = tc.x;
        float y = tc.y;
        float radius = x * x + y * y;
        if( radius > 1.0 ) discard;

        radius = sqrt( radius );

        float radiusH = 1.0 - (strokeWeight+1.0) / offset.z;
        float radiusV = 1.0 - (strokeWeight+1.0) / offset.w;
        float radiusAverage = (radiusH + radiusV) * 0.5;

        float minRadius = 0.0;
        x = abs( x );
        y = abs( y );
        if( x > y ) {
            minRadius = mix( radiusH, radiusAverage, y / x );
        }
        else {
            minRadius = mix( radiusV, radiusAverage, x / y );
        }

        if( radius < minRadius ) 
        {
            gl_FragColor = fillColor;
        }
        else
        {
            gl_FragColor = strokeColor;
        }
    }
)";