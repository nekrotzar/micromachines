#version 330

out vec4 colorOut;

struct Materials {
    vec4 diffuse;
    vec4 ambient;
    vec4 specular;
    vec4 emissive;
    float shininess;
    int texCount;
};

struct PointLight {
    bool status;
    vec4 position;
    float constant, linear, quadratic;
    vec4 ambient, diffuse, specular;
};

uniform PointLight pointlights[6];
uniform Materials mat;

in Data {
    vec3 normal;
    vec3 eye;
    vec4 position;
    vec2 texcoord;
} DataIn;


void main() {
    vec4 result;
    vec4 spec = vec4(0.0);
    
    vec4 scatterLight = vec4(0.0);
    vec4 reflectLight = vec4(0.0);
    
    vec3 n = normalize(DataIn.normal);
    vec3 e = normalize(DataIn.eye);
    
    for (int i = 0; i < 6; ++i) {
        
        if (!pointlights[i].status) {
            continue;
        }
        
        vec3 lightDir = normalize(vec3(pointlights[i].position - DataIn.position));
        float distance = length(lightDir);
        float attenuation = 1.0/ (pointlights[i].constant + pointlights[i].linear * distance + pointlights[i].quadratic*(distance * distance));; // Quadratic attenuation

        
        vec3 h = normalize(lightDir + e);
        
        float intDiff = max(dot(n, lightDir),0.0);
        float intSpec = max(dot(h, n),0.0);
        

            
            spec = mat.specular * pow(intSpec, mat.shininess);
            
            scatterLight += mat.diffuse * intDiff * attenuation;
            reflectLight += spec * attenuation;
    }
    
    colorOut = scatterLight + reflectLight;

}
