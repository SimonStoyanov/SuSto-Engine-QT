    #version 330 core
              
	layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 normals; 
    layout(location = 2) in vec2 uvs; 
			  
	uniform float ambient_intensity;
		   
	out Data 
    {
		vec2 uvs;
		float ambient_intensity;

	}VSOut; 
		  
    
    void main()
    {
        VSOut.uvs = uvs; 
		VSOut.ambient_intensity = ambient_intensity;
		
        gl_Position = vec4(vec3(position.x, position.y, position.z), 1);
    }