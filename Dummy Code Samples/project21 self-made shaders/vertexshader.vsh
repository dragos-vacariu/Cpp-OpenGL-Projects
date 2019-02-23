#version 130

in vec2 vertexPosition;
attribute vec3 color;
out vec3 thecolor;

void main()
{
	gl_Position.xy=vertexPosition;
	gl_Position.z=-1.0; 
	gl_Position.w=1.0;
	thecolor=color;

}