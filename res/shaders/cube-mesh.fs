

#version 450 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform vec3 viewPos;

void main()
{    
	vec3 light_ambient = vec3(0.20);
	vec3 light_diffuse = vec3(1.0);
	vec3 light_specular = vec3(0.20);
	vec3 light_position = vec3(10.0);
    vec3 ambient = texture2D(texture_diffuse1, TexCoords).rgb * light_ambient;

	// Diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light_position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * texture2D(texture_diffuse1, TexCoords).rgb) * light_diffuse ;

	// Specular
	float specularStrength = 1.0;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
	vec3 specular = (texture2D(texture_specular1, TexCoords).rgb * spec) * light_specular;  

	vec3 result = (ambient + diffuse + specular);
	FragColor = vec4(result, 1.0);
}

