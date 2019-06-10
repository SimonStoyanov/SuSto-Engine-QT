    #version 330 core
    layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 normals;
    layout(location = 2) in vec2 uvs; 
    layout(location = 3) in vec3 tangents; 
    layout(location = 4) in vec3 bitangents;
    
    uniform mat4 Model; 
    uniform mat4 View; 
    uniform mat4 Projection; 
    
    uniform float ambientTerm; 
    
    uniform vec4 col; 
    uniform int hasDiffuse; 
    uniform int hasNormalMap; 
    
    out Data 
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
    } VSOut; 
    
    void main()
    {
        VSOut.worldViewMatrix = View * Model; 
        VSOut.tangentLocalspace = tangents; 
        VSOut.bitangentLocalspace = bitangents; 
        VSOut.normalLocalspace = normals; 
        VSOut.uvs = uvs; 
        VSOut.colour = col; 
        VSOut.hasDiffuse = hasDiffuse; 
        VSOut.hasNormalMap = hasNormalMap; 
        VSOut.ambientTerm = ambientTerm; 
        
        gl_Position = Projection * View * Model * vec4(vec3(position.x, position.y, position.z), 1);
    }