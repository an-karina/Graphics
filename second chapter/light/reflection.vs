#version 330 core
layout (location = 0) in vec3	object_pos;
layout (location = 1) in vec3	object_normal;

out vec3						normal;
out vec3						position;

uniform mat4					model;
uniform mat4					view;
uniform mat4					projection;

void main()
{
	normal = mat3(transpose(inverse(model))) * object_normal;
	position = vec3(model * vec4(object_pos, 1.0));
	gl_Position = projection * view * model * vec4(object_pos, 1.0);
}
