#version 130

in vec3 fragmentPosition;
in vec3 thecolor;
out vec3 color;

uniform float time;
void main()
{
	/*color=thecolor+vec3(1.0 * (cos(time+1.0)) * 0.5, 
						1.0 * (cos(time+2.0) +1.0) * 0.5,
						1.0 * (sin(time-1.0) * 0.5));*/
						
		color = vec3 (fragmentPosition.x * cos(time+1.0*4.0) *0.5, fragmentPosition.y * cos((time+2.0*8.0)+1.0) *0.5,
						(fragmentPosition.x-fragmentPosition.y+fragmentPosition.z) * sin (time-1.0*2.0)*0.5); 				
}