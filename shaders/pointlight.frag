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

struct DirectionalLight {
    bool status;
    vec4 direction;
};

struct PointLight {
    bool status;
    vec4 position;
    float constant, linear, quadratic;
};

struct SpotLight {
    bool status;
    vec4 position;
    
    vec3 direction;
    float cutoff;
    float exponent;
    
    float constant;
    float linear;
    float quadratic;
};

uniform DirectionalLight dirLight;
uniform PointLight pointlights[6];
uniform SpotLight spotlights[2];
uniform Materials mat;

in Data {
    vec3 normal;
    vec3 eye;
    vec4 position;
    vec2 texcoord;
} DataIn;


vec4 CalcDirLight(DirectionalLight light, vec3 normal, vec3 eye){
    
    vec3 lightDir = normalize(vec3(-light.direction));
    float intDiff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float intSpec = pow(max(dot(eye, reflectDir), 0.0), mat.shininess);
    
    return max(mat.diffuse * intDiff + mat.specular * intSpec, mat.ambient);
}

vec4 CalcPointLight(PointLight light, vec3 normal, vec4 position, vec3 eye){
    vec3 lightDir = normalize(vec3(light.position - position));
    float distance = length(lightDir);
    float attenuation = 1.0/(light.constant + light.linear * distance + light.quadratic*(distance * distance));
    vec3 h = normalize(lightDir + eye);
    
    float intDiff = max(dot(normal, lightDir),0.0);
    float intSpec = max(dot(h, normal),0.0);
    
    vec4 spec = mat.specular * pow(intSpec, mat.shininess);
    
    return (mat.diffuse * intDiff * attenuation) + (spec * attenuation);
}

/*
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec4 position, vec3 eye){
    vec3 lightDir = normalize(vec3(light.position - position));
    float intDiff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float intSpec = pow(max(dot(eye, reflectDir), 0.0), mat.shininess);
    
    float distance = length(light.position - position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    
    float theta = dot(lightDir, normalize(-light.direction));
    
    if (theta < light.cutoff)
        attenuation = 0.0;
    else
        attenuation = pow(theta, light.exponent);
    
    vec4 spec = mat.specular * pow(intSpec, mat.shininess);
    
    return (mat.diffuse * intDiff * attenuation) + (spec * attenuation);
}
 */


void main() {
    vec4 result = vec4(0.0) ;

    vec3 n = normalize(DataIn.normal);
    vec3 e = normalize(DataIn.eye);
    
    
    if (dirLight.status) {
        result = CalcDirLight(dirLight, n, e);
    }
    
    for (int i = 0; i < 6; i++) {
        if (pointlights[i].status) {
            result += CalcPointLight(pointlights[i], n, DataIn.position, e);
        }
    }
    
    /*
    for (int i = 0; i < 2; i++) {
        if (spotlight[i].status) {
            result += CalcSpotLight(spotlights[i], n, DataIn.position, e);
        }
    }*/


    colorOut = result;
}
