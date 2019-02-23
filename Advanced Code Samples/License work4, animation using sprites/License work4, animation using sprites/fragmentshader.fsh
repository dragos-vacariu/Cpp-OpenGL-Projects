#version 130

in vec3 Color;
in vec2 Texcoord;
out vec4 outColor;
uniform sampler2D texKitten;
void main()
{
    vec4 color2 = texture2D(texKitten, Texcoord) * vec4(Color, 1.0);
    gl_FragColor = color2;
	//color = Color;
	//color=vec3(1.0,1.0,0.0);
}