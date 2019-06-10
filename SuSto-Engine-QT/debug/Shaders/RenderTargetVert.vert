    #version 330 core
    layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 normals; 
    layout(location = 2) in vec2 uvs; 
   
    uniform mat4 Model; 
    uniform mat4 View; 
    uniform mat4 Projection; 
            
    out vec2 oUvs; 
    
    void main()
    {
        oUvs = uvs; 
        gl_Position = vec4(vec3(position.x, position.y, position.z), 1);
    }