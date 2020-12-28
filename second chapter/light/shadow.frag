

#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;// perform perspective divide
    projCoords = projCoords * 0.5 + 0.5;// transform to [0,1] range
    float closestDepth = texture(shadowMap, projCoords.xy).r;//get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float currentDepth = projCoords.z;// get depth of current fragment from light's perspective
	vec3 normal = normalize(fs_in.Normal);// check whether current frag pos is in shadow
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);//we gets the size of a texel
    for(int x = -2; x <= 2; ++x)//the offset is one texel
    {
        for(int y = -2; y <= 2; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 18.0;
    
    if(projCoords.z > 1.0)// keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
        shadow = 0.0;

    return (shadow);
}

void main()
{           
	vec3 color;
	vec3 normal;
	vec3 lightColor;
	vec3 ambient;
	vec3 lightDir;
	float diff;
	vec3 diffuse;
	vec3 viewDir;
	vec3 reflectDir;
	float spec;
	vec3 halfwayDir;
	vec3 specular;
	float shadow;
	vec3 lighting;

	color = texture(diffuseTexture, fs_in.TexCoords).rgb;
	normal = normalize(fs_in.Normal);
	lightColor = vec3(0.3);
    ambient = 0.3 * color;//ambient
    lightDir = normalize(lightPos - fs_in.FragPos);//diffuse
    diff = max(dot(lightDir, normal), 0.0);
    diffuse = diff * lightColor;
    viewDir = normalize(viewPos - fs_in.FragPos);//specular
    reflectDir = reflect(-lightDir, normal);
    spec = 0.0;
    halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    specular = spec * lightColor;    
    shadow = ShadowCalculation(fs_in.FragPosLightSpace);// calculate shadow                    
    lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;
    FragColor = vec4(lighting, 1.0);
}

