#version 130

in vec3 vertexPosition;
attribute vec3 color;
out vec3 thecolor;

void main()
{
	gl_Position.xyz=vertexPosition;
	gl_Position.w=1.0;
	thecolor=color;

}