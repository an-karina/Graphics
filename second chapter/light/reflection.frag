#version 330 core
out vec4 			FragColor;

in vec3 			normal;
in vec3 			position;

uniform vec3 		camera_position;
uniform samplerCube	skybox;

void main()
{             
    vec3 direction = normalize(position - camera_position);
    vec3 reflection = reflect(direction, normalize(normal));
    FragColor = vec4(texture(skybox, reflection).rgb, 1.0);
}