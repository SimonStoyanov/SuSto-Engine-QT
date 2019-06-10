    #version 330 core
	
    uniform sampler2D gPosition; 
	uniform sampler2D gNormal;
	uniform sampler2D gAlbedoSpec;
	
	out vec4 finalColor; 
	
	in Data 
    {
		vec2 uvs; 
		flat int mode; 
		vec3 view_pos;
	} FSIn;
	
	struct Light 
	{
		vec3 Position;
		vec3 Color;
		
		float Linear;
		float Quadratic;
		float Radius;
	};
	
	const int NR_LIGHTS = 1;
	Light lights[NR_LIGHTS];
	
    void main() 
    {
		if(FSIn.mode == 1)
		{
			finalColor = texture(gPosition, FSIn.uvs);
		}
		if (FSIn.mode == 2)
		{
			finalColor = texture(gNormal, FSIn.uvs);
		}
		if(FSIn.mode == 3)
		{
			finalColor = texture(gAlbedoSpec, FSIn.uvs);
		}
		if(FSIn.mode == 0)
		{
			vec3 FragPos = texture(gPosition, FSIn.uvs).rgb;
			vec3 Normal = texture(gNormal, FSIn.uvs).rgb;
			vec3 Diffuse = texture(gAlbedoSpec, FSIn.uvs).rgb;
			float Specular = texture(gAlbedoSpec, FSIn.uvs).a;
			
			vec3 lighting = Diffuse * 0.2; // hard-coded ambient component
			
			vec3 viewDir = normalize(FSIn.view_pos - FragPos);
		
			lights[0].Position = vec3(0, 0.5, 0);
			lights[0].Color = vec3(1, 1, 1);
			lights[0].Linear = 0.7;
			lights[0].Quadratic = 1.8;
			lights[0].Radius = 1.3;
		
		
		   for(int i = 0; i < NR_LIGHTS; ++i)
			{
				// diffuse
				vec3 lightDir = normalize(lights[i].Position - FragPos);
				vec3 diffuse = max(dot(Normal, lightDir), 0.0) * Diffuse * lights[i].Color;
				lighting += diffuse;
			}
    
			finalColor = vec4(lighting, 1.0);
		}
	
    }