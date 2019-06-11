    #version 330 core
              
	layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 normals; 
    layout(location = 2) in vec2 uvs; 
	
	uniform mat4 Model;
    uniform mat4 View; 
    uniform mat4 Projection;
			 
	uniform vec3 CameraPos;
	uniform vec3 LightPos;
	uniform vec3 LightDir;
			 
	out Data 
    {
		vec3 fragPosWorldSpace;
		vec2 uvs;
		vec3 lightPos;
		vec3 viewPos;
		vec3 lightDir;

	}VSOut; 
		  
    
    void main()
    {	
		VSOut.fragPosWorldSpace = vec3(Model * vec4(position, 1.0));
		VSOut.uvs = uvs;
		VSOut.lightPos = LightPos;
		VSOut.viewPos = CameraPos;
		VSOut.lightDir = LightDir;
	
		gl_Position = vec4(vec3(position.x, position.y, position.z), 1);
    }