	#version 330 core    
    uniform sampler2D diffuse; 
    uniform sampler2D normalMap; 
    uniform sampler2D specular; 
    
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
		
		mat4 worldViewMatrix;
		
		vec3 fragPosWorldSpace;
		vec3 normalWorldSpace;
		vec2 uvsWorldSpace;
		
		flat int hasDiffuse; 
		flat int hasNormalMap; 
		flat int hasSpecular;
    } FSIn; 
    
    void main()
    {
        gPosition = FSIn.fragPosWorldSpace; 
        
        if(FSIn.hasNormalMap == 1) 
        { 		
			vec3 T = normalize(FSIn.tangents);
			vec3 B = normalize(FSIn.bitangents);
			vec3 N = normalize(FSIn.normals);
			mat3 TBN = mat3(T, B, N);
			
			vec3 texNormal = texture(normalMap, FSIn.uvs).xyz * 2.0 - vec3(1.0);
			vec3 localSpaceNormal = TBN * texNormal;
			vec3 viewSpaceNormal = normalize(FSIn.worldViewMatrix * vec4(localSpaceNormal, 0.0)).xyz;

            gNormal = viewSpaceNormal;
        }
		else
		{
			gNormal = FSIn.normals;
		}
		
		if(FSIn.hasDiffuse == 1)
        {
			gAlbedoSpec.rgb = texture(diffuse, FSIn.uvs).rgb; 
		}
		else
		{
			gAlbedoSpec.rgb = vec3(1, 1, 1);
		}
		
		if(FSIn.hasSpecular == 1) 
        { 
			gAlbedoSpec.a = texture(specular, FSIn.uvs).r; 
        }
        
        if(FSIn.hasNormalMap == 1) 
        {
			gAlbedoSpec.a = 1;
        }
    }