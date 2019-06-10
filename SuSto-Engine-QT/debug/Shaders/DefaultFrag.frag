	#version 330 core    
    uniform sampler2D diffuse; 
    uniform sampler2D normalMap; 
    uniform sampler2D specularMap; 
    
    in vec3 FragPos;
    
    out vec4 finalColor; 
    
    in Data 
    {
     mat4 worldViewMatrix; 
     vec3 tangentLocalspace; 
     vec3 bitangentLocalspace; 
     vec3 normalLocalspace; 
     vec2 uvs; 
     vec4 colour; 
     flat int hasDiffuse; 
     flat int hasNormalMap; 
     float ambientTerm; 
    } FSIn; 
    
    void main()
    {
        //finalPos = FragPos; 
        
        //if(FSIn.hasNormalMap == 1) 
        //{ 
            //finalNormal = normalize(FSIn.normalLocalspace); 
        //} 
        //finalAlbedo.rgb = texture(diffuse, FSIn.uvs).rgb; 
        //finalAlbedo.a = texture(specularMap, TexCoords).r; 
        
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
        
        finalColor.a = diffuse_col.a; 
        finalColor.rgb = diffuse_col.rgb * FSIn.ambientTerm;
        
    }