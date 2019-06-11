    #version 330 core
		
	layout (location = 4) out vec4 gLight;
	
	in Data 
    {
		vec3 normal;
		vec2 uvs;
		vec3 fragPosWorldSpace;
		vec3 lightPos;
		vec3 viewPos;
	} FSIn;
		
    void main() 
    {
		vec3 color = vec3(1, 0, 1);
		
		vec3 lightDir = normalize(FSIn.lightPos - FSIn.fragPosWorldSpace);
		vec3 normal = normalize(FSIn.normal);
		
		float diff = max(dot(lightDir, normal), 0.0);
		vec3 diffuse = diff * color;
		
		vec3 viewDir = normalize(FSIn.viewPos - FSIn.fragPosWorldSpace);
		
		vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
		
		vec3 specular = vec3(30) * spec;
	
		gLight = vec4(diffuse + specular, 1.0);
    }