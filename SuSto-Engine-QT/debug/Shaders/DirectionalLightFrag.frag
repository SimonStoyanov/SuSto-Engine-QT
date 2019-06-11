    #version 330 core
		
	uniform sampler2D gPosition;
	uniform sampler2D gNormal;
	uniform sampler2D gAlbedoSpec;
	uniform sampler2D gAmbient;
		
	layout (location = 4) out vec4 gLight;
	
	in Data 
    {
		vec3 fragPosWorldSpace;
		vec2 uvs;
		vec3 lightPos;
		vec3 viewPos;
		vec3 lightDir;
	} FSIn;
		
    void main() 
    {	
		vec3 lightColour = vec3(1, 0, 1);
	
		vec3 gposition = texture(gPosition, FSIn.uvs).xyz;
		vec3 N = texture(gNormal, FSIn.uvs).xyz;
		vec3 gdiffuse = texture(gAmbient, FSIn.uvs).rgb;
		float gspecular = texture(gAlbedoSpec, FSIn.uvs).a;
		
		vec3 L = normalize(FSIn.lightPos - gposition);
		vec3 V = normalize(gposition - FSIn.viewPos);
		
		vec3 H = normalize(L + V);
		
		vec3 diffuse = gdiffuse * dot(L, N) * lightColour;
		vec3 specular = gspecular * dot(N, H) * gdiffuse;
	
		vec3 lightning = diffuse + specular;
	
		gLight = vec4(lightning, 1.0);
    }