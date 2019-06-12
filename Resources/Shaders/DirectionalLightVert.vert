    #version 330 core
              
	layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 normals; 
    layout(location = 2) in vec2 uvs; 
	
	uniform mat4 Model;
    uniform mat4 View; 
    uniform mat4 Projection;
			 
	uniform vec3 CameraPos;
	uniform vec3 LightDir;
	uniform vec3 LightColour;
	uniform float LightIntensity;
			 
	out Data 
    {
		vec3 fragPosWorldSpace;
		vec2 uvs;
		vec3 viewPos;
		vec3 lightDir;
		vec3 lightColour;
		float lightIntensity;

	}VSOut; 
		  
    
    void main()
    {	
		VSOut.fragPosWorldSpace = vec3(Model * vec4(position, 1.0));
		VSOut.uvs = uvs;
		VSOut.viewPos = CameraPos;
		VSOut.lightDir = LightDir;
		VSOut.lightColour = LightColour;
		VSOut.lightIntensity = LightIntensity;
	
		gl_Position = vec4(vec3(position.x, position.y, position.z), 1);
    }