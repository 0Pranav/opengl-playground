#version 450 core
		
	struct Material {
		sampler2D diffuse1;
		sampler2D specular1;
		float shininess;
	}; 
  
	struct Light {
		vec3 position;
  
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;
	};

	in vec3 Normal;
	in vec3 FragPos;
	in vec2 TexCoords;
  
	uniform Light light;  
	uniform Material material;
	uniform vec3 viewPos;

	out vec4 FragColor;

	void main()
	{
		vec3 ambient = texture2D(material.diffuse1, TexCoords).rgb * light.ambient;

		// Diffuse
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(light.position - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = (diff * texture2D(material.diffuse1, TexCoords).rgb) * light.diffuse ;

		// Specular
		float specularStrength = 0.5;
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = (texture2D(material.specular1, TexCoords).rgb * spec) * light.specular;  

		vec3 result = (ambient + diffuse + specular);
		FragColor = vec4(result, 1.0);
	}