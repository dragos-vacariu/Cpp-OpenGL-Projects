#version 130

in vec2 vertexPosition;
out vec4 thecolor;
void main()
{
	gl_Position.xy=vertexPosition;
	gl_Position.z=-1.0;
	gl_Position.w=1.0;
	thecolor =vec4(gl_Position.x+0.2, gl_Position.y-0.2, 0.0, 1.0);
}