#version 130

in vec2 position;
in vec3 color;
in vec2 texcoord;

out vec3 Color;
out vec2 Texcoord;
void main()
{
	Color = color;
	Texcoord = texcoord;
	gl_Position = vec4(position,0.0f, 1.0f);
	//if the last argument of gl_Position is 0.0f then the vertices will be transparent (invisible).
}