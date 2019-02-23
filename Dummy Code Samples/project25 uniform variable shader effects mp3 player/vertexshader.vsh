#version 130

in vec3 vertexPosition;
attribute vec3 color;
out vec3 thecolor;

out vec3 fragmentPosition;

uniform float time;
void main()
{
	fragmentPosition=vertexPosition;
	gl_Position.xyz=vertexPosition;
	gl_Position.w=1.0;
	thecolor=color;
}