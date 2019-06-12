    #version 330 core
	
	uniform sampler2D gAlbedoSpec;
	
	layout (location = 3) out vec4 gAmbient;
	
	in Data 
    {
		vec2 uvs;
		float ambient_intensity;
	} FSIn;
		
    void main() 
    {
		vec3 Albedo = texture(gAlbedoSpec, FSIn.uvs).rgb;
	
		vec3 lighting = Albedo * FSIn.ambient_intensity; 
		gAmbient = vec4(lighting, 1.0);
    }