#version 430

void main(void)
{
	if(gl_VertexID == 0) {
		gl_Position = vec4(-0.25, 0, 0, 1);
	}
	else if (gl_VertexID == 1) {
		gl_Position = vec4(0.25, 0, 0, 1);
	}
	else {
		gl_Position = vec4(0,0.5,0,1);
	}
}