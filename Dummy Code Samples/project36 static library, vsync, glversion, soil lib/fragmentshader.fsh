#version 130

//in vec3 thecolor;
in vec2 textures;

out vec3 color;
//out vec2 texcoords;

uniform sampler2D ourtexture;
void main()
{
	color=texture(ourtexture, textures);
}