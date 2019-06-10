    #version 330 core
	
    uniform sampler2D tex; 
	
    in vec2 oUvs; 
    out vec4 finalColor; 
	
    void main() 
    {
        finalColor = texture(tex, oUvs);
    }