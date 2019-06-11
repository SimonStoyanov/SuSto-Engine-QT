    #version 330 core
    layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 normals; 
    layout(location = 2) in vec2 uvs; 
   
    uniform mat4 Model; 
    uniform mat4 View; 
    uniform mat4 Projection; 
           
	uniform int mode; 
	uniform vec3 view_pos;
		   
	out Data 
    {
		vec2 uvs; 
		flat int mode; 
		vec3 view_pos;
	}VSOut; 
		  
    
    void main()
    {
        VSOut.uvs = uvs; 
		VSOut.mode = mode;
		VSOut.view_pos = view_pos;
		
        gl_Position = vec4(vec3(position.x, position.y, position.z), 1);
    }