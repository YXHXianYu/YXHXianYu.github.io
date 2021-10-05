// Frame from the Book of Shaders

#ifdef GL_ES
precision mediump float;
#endif

#define PI 3.1415926

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

// 坐标为内正方形
// 正方形边0.0; 正方形内部0.5; 正方形外部1.0;
float drawRectangle_line(vec2 st, float width, float x1, float y1, float x2, float y2) {
	if(step(x1 - width, st.x) == 0.0) return 1.0;
	if(step(y1 - width, st.y) == 0.0) return 1.0;
	if(step(x2 + width, st.x) == 1.0) return 1.0;
	if(step(y2 + width, st.y) == 1.0) return 1.0;
	if(step(x1, st.x) == 0.0) return 0.0;
	if(step(y1, st.y) == 0.0) return 0.0;
	if(step(x2, st.x) == 1.0) return 0.0;
	if(step(y2, st.y) == 1.0) return 0.0;
	return 0.5;
}

vec3 drawRectangle_fill(vec2 st, float width, float x1, float y1, float x2, float y2, vec3 color) {
    float a = drawRectangle_line(st, width, x1, y1, x2, y2);
    if(a == 1.0) return vec3(1.0);
    else if(a == 0.0) return vec3(0.0); 
    else return color;
}

vec3 distanceFieldDraw(vec2 st, int type, vec3 color, vec2 center) {
	// add, times, min, max, pow
	float v1 = distance(st,  vec2(sin(u_time)/2.0+center.x,cos(u_time)/2.0+center.y)),
		  v2 = distance(st, vec2(sin(u_time+PI)/2.0+center.x,cos(u_time+PI)/2.0+center.y));
	if(type == 1) return (v1 * v2) * color;
	if(type == 2) return min(v1, v2) * color;
	if(type == 3) return max(v1, v2) * color;
	if(type == 4) return pow(v1, v2) * color;
	return color;
}

vec3 distanceFieldDraw_DEMO(vec2 st) {
	vec3 color1 = distanceFieldDraw(st, 2, vec3(0.218,1.000,0.284), vec2(0.340,0.540)),
    	 color2 = distanceFieldDraw(st, 4, vec3(1.000,0.473,0.170), vec2(0.930,0.360));
	return color1 + color2;
}

// from tbos
vec3 hsb2rgb( in vec3 c ){
    vec3 rgb = clamp(abs(mod(c.x*6.0+vec3(0.0,4.0,2.0),
                             6.0)-3.0)-1.0,
                     0.0,
                     1.0 );
    rgb = rgb*rgb*(3.0-2.0*rgb);
    return c.z * mix( vec3(1.0), rgb, c.y);
}

void main(){
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    
    vec3 color = distanceFieldDraw_DEMO(st);

    gl_FragColor = vec4(color,1.0);
}
