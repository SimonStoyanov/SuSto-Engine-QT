    #version 330 core
	
    uniform sampler2D gPosition; 
	uniform sampler2D gNormal;
	uniform sampler2D gAlbedoSpec;
	uniform sampler2D gAmbient;
	uniform sampler2D gLight;
	
	out vec4 finalColor; 
	
	in Data 
    {
		vec2 uvs; 
		flat int mode; 
		vec3 view_pos;
	} FSIn;
	
	struct Light 
	{
		vec3 Position;
		vec3 Color;
	};
		
    void main() 
    {
		if(FSIn.mode == 1)
		{
			finalColor = texture(gPosition, FSIn.uvs);
		}
		if (FSIn.mode == 2)
		{
			finalColor = texture(gNormal, FSIn.uvs);
		}
		if(FSIn.mode == 3)
		{
			finalColor = vec4(texture(gAlbedoSpec, FSIn.uvs).rgb, 1);
		}
		if(FSIn.mode == 0)
		{
			finalColor = vec4(texture(gLight, FSIn.uvs).rgb, 1);
		}
	
    }