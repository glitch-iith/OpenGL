#version 430

mat4 buildRotateZ(float rad) {
	mat4 zrot = mat4(cos(rad), -sin(rad), 0.0, 0.0,
		sin(rad), cos(rad), 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0 );
	return zrot;
}

mat4 buildTranslate(float x, float y, float z) {
	mat4 trans = mat4(1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		x, y, z, 1.0);
	return trans;
}

void main(void)
{
	mat4 rotMat = buildRotateZ(0.25);
	mat4 transMat = buildTranslate(-0.5, 0, 0);
	mat4 transformMat = rotMat * transMat;
	if(gl_VertexID == 0) {
		gl_Position = vec4(-0.25, 0, 0, 1);
		gl_Position =  transformMat * gl_Position;
	}
	else if (gl_VertexID == 1) {
		gl_Position = vec4(0.25, 0, 0, 1);
		gl_Position = transformMat * gl_Position;
	}
	else {
		gl_Position = vec4(0,0.7,0,1);
		gl_Position = transformMat * gl_Position;
	}
}