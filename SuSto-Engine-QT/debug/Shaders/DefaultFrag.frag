	#version 330 core    
    uniform sampler2D diffuse; 
    uniform sampler2D normalMap; 
    uniform sampler2D albedo; 
    
	layout (location = 0) out vec3 gPosition;
	layout (location = 1) out vec3 gNormal;
	layout (location = 2) out vec4 gAlbedoSpec;
	        
    in Data 
    {
	 vec3 tangents; 
     vec3 bitangents; 
     vec3 normals; 
     vec2 uvs; 
     vec4 colour; 
	
	 vec3 fragPosWorldSpace;
	 vec3 normalWorldSpace;
	 vec2 uvsWorldSpace;
	 
     flat int hasDiffuse; 
     flat int hasNormalMap; 
	 flat int hasAlbedo;
    } FSIn; 
    
    void main()
    {
        gPosition = FSIn.fragPosWorldSpace; 
        
        if(FSIn.hasNormalMap == 1) 
        { 
            gNormal = normalize(FSIn.normals); 
        } 
		
		if(FSIn.hasAlbedo == 1) 
        { 
            gAlbedoSpec.rgb = texture(diffuse, FSIn.uvs).rgb; 
			gAlbedoSpec.a = texture(albedo, FSIn.uvs).r; 
        } 
        
        if(FSIn.hasNormalMap == 1) 
        {
        
        }
        
        vec4 diffuse_col; 
        
        if(FSIn.hasDiffuse == 1)
        {
            diffuse_col = texture(diffuse, FSIn.uvs);
        }
        else
        {
            diffuse_col = FSIn.colour;
        }
        
        //finalColor = diffuse_col;
        
    }