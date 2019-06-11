    #version 330 core
              
	layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 normals;
    layout(location = 2) in vec2 uvs; 
    layout(location = 3) in vec3 tangents; 
    layout(location = 4) in vec3 bitangents;
			 
    uniform mat4 Model; 
    uniform mat4 View; 
    uniform mat4 Projection;
			 
	uniform vec3 CameraPos;
	uniform vec3 LightPos;
			 
	out Data 
    {
		vec3 normal;
		vec2 uvs;
		vec3 fragPosWorldSpace;
		vec3 lightPos;
		vec3 viewPos;

	}VSOut; 
		  
    
    void main()
    {
		vec4 transformedPosition = Projection * View * Model * vec4(position, 1.0f);
	
		VSOut.fragPosWorldSpace = vec3(Model * vec4(position, 1.0));
		VSOut.normal = normals;
		VSOut.uvs = uvs;
		VSOut.lightPos = LightPos;
		VSOut.viewPos = CameraPos;
	
		gl_Position = transformedPosition;
    }