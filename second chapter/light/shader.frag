#version 330 core

in vec3				FragPos;
in vec3				Normal;
in vec2				TexCoords;
in vec4				FragPosLightSpace;

out vec4			color;

uniform sampler2D	m_diffuse;
uniform sampler2D	m_specular;
uniform float		m_shininess;
uniform sampler2D	shadowMap;

uniform vec3		l_ambient;
uniform vec3		l_diffuse;
uniform vec3		l_specular;
uniform vec3		lightPos;
uniform vec3		viewPos;

float ShadowCalculation(vec4 fragPosLightSpace)
{
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;//normalization. we are in [-1;1]
	projCoords = projCoords * 0.5 + 0.5;//[0;5]
	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;
	float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;
	return shadow;
}

void	main()
{
	vec3	Ambient;
	vec3	norm;
	vec3	lightDir;
	float	diff;
	vec3	Diffuse;
	vec3	viewDir;
	vec3	reflectDir;
	float	spec;
	vec3	Specular;
	vec3	result;
	float	shadow;
	vec3 lighting;

    Ambient = l_ambient * vec3(texture(m_diffuse, TexCoords));
	norm = normalize(Normal);
	lightDir = normalize(lightPos - FragPos);
	diff = max(dot(norm, lightDir), 0.0);
	Diffuse = vec3(texture(m_diffuse, TexCoords)) * diff * l_diffuse;

	viewDir = normalize(viewPos - FragPos);
	reflectDir = reflect(-lightDir, norm);
	
	spec = pow(max(dot(viewDir, reflectDir), 0.0), m_shininess);
	Specular = vec3(texture(m_specular, TexCoords)) * spec * l_specular;

	shadow = ShadowCalculation(FragPosLightSpace);
	color = vec4(Ambient + (1.0 - shadow) + Diffuse + Specular, 1.0);
}