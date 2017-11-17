#version 330

uniform sampler2D texmap;

uniform int texMode;
out vec4 colorOut;

struct Materials {
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
	vec4 emissive;
	float shininess;
	int texCount;
};
uniform Materials mat;


in Data {
	vec3 normal;
	vec3 eye;
	vec3 lightDir;
	vec2 tex_coord;
} DataIn;

void main() {

	vec3 spec = vec3(0.0);
    vec4 texel;

	vec3 n = normalize(DataIn.normal);
	vec3 l = normalize(DataIn.lightDir);
	vec3 e = normalize(DataIn.eye);

	float intensity = max(dot(n,l), 0.0);
	if (intensity > 0.0) {
		vec3 h = normalize(l + e);
		float intSpec = max(dot(h,n), 0.0);
		spec = mat.specular.rgb * pow(intSpec, mat.shininess);
	}

	if(texMode == 0) // just phong color
		colorOut = max(intensity * mat.diffuse + vec4(spec, 1.0),mat.ambient);
	
	else if (texMode == 1)  {  // tree texture for billboard
		texel = texture(texmap, DataIn.tex_coord);  		if(texel.a == 0.0) discard;
		else
			colorOut = vec4(max(intensity*texel.rgb + spec, 0.1*texel.rgb), texel.a);
		}
	else  {	// modulated texture for particle
		texel = texture(texmap, DataIn.tex_coord);
		colorOut = mat.diffuse * texel;
	}
}