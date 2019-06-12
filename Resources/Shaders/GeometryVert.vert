    #version 330 core
    layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 normals;
    layout(location = 2) in vec2 uvs; 
    layout(location = 3) in vec3 tangents; 
    layout(location = 4) in vec3 bitangents;
    
    uniform mat4 Model; 
    uniform mat4 View; 
    uniform mat4 Projection; 
    
    uniform vec4 col; 
    uniform int hasDiffuse; 
    uniform int hasNormalMap; 
	uniform int hasSpecular; 
    
    out Data 
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
    } VSOut; 
    
    void main()
    {
		vec4 transformedPosition = Projection * View * Model * vec4(position, 1.0f);
	
		VSOut.worldViewMatrix = View * Model;
	
		VSOut.fragPosWorldSpace = vec3(Model * vec4(position, 1.0));
		VSOut.normalWorldSpace = mat3(transpose(inverse(Model))) * normals;
		VSOut.uvsWorldSpace = uvs;
	
        VSOut.tangents = tangents; 
        VSOut.bitangents = bitangents; 
        VSOut.normals = normals; 
        VSOut.uvs = uvs; 
        VSOut.colour = col; 
        VSOut.hasDiffuse = hasDiffuse; 
        VSOut.hasNormalMap = hasNormalMap; 
		VSOut.hasSpecular = hasSpecular; 
        
        gl_Position = transformedPosition;
    }