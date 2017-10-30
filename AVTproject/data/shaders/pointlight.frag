#version 330

out vec4 colorOut;

uniform sampler2D texmap0;
uniform sampler2D texmap1;

uniform int texMode;

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
    vec4 diffuse, specular;
};

struct PointLight {
    bool status;
    vec4 position;
    vec4 diffuse, specular;
    float constant, linear, quadratic;
};

struct SpotLight {
    bool status;
    vec4 position;
    vec4 diffuse, specular;
    
    vec4 direction;
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


void main() {

    vec3 n = normalize(DataIn.normal);  // normal
    vec3 e = normalize(DataIn.eye);     // eye
    vec3 l;                             // light direction
    
    float attenuation;                  // attenuation
    
    vec4 scatteredLight = vec4(0.0);
    vec4 reflectedLight = vec4(0.0);
    
    // Directional Light contribution
    if (dirLight.status){
        attenuation = 1.0;
        l = normalize(vec3(dirLight.direction));
        
        float intensity = max(dot(n,l), 0.0);
        vec4 diff = dirLight.diffuse * intensity;
        vec4 spec = vec4(0.0);
        
        if (intensity > 0.0){
            vec3 h = normalize(l + e);
            float intSpec = max(dot(h,n), 0.0);
            spec = dirLight.specular * pow(intSpec, mat.shininess);
        }
        scatteredLight += diff * attenuation;
        reflectedLight += spec * attenuation;
    }
    
    // Point Light contribution
    for (int i = 0; i < 6; i++) {
        if (pointlights[i].status) {
            vec3 lightDir = vec3(pointlights[i].position - DataIn.position);
            float distance = length(lightDir);
            l = normalize(lightDir);
            
            attenuation = 1.0 / (pointlights[i].quadratic * (distance*distance));
            
            float intensity = max(dot(n,l), 0.0);
            vec4 diff = dirLight.diffuse * intensity;
            vec4 spec = vec4(0.0);
            
            if (intensity > 0.0){
                vec3 h = normalize(l + e);
                float intSpec = max(dot(h,n), 0.0);
                spec = dirLight.specular * pow(intSpec, mat.shininess);
            }
            scatteredLight += diff * attenuation;
            reflectedLight += spec * attenuation;
        }
    }
    
    // Spot light contribution
    for (int i = 0; i < 2; i++){
        if(spotlights[i].status){
            vec3 lightDir = vec3(spotlights[i].position - DataIn.position);
            float distance = length(lightDir);
            l = normalize(lightDir);
            
            attenuation = 1.0 / spotlights[i].constant + spotlights[i].linear * distance +  spotlights[i].quadratic * (distance*distance);
            
            vec3 spotDir = normalize(vec3(-spotlights[i].direction));
            float spotCosine = max(dot(spotDir, l), 0.0);
            
            if(spotCosine >= cos(radians(spotlights[i].cutoff)))
               attenuation += pow(spotCosine, spotlights[i].exponent);
            else
               attenuation = 0.0;
           
           float intensity = max(dot(n,l), 0.0);
           vec4 diff = dirLight.diffuse * intensity;
           vec4 spec = vec4(0.0);
               
           if (intensity > 0.0){
               vec3 h = normalize(l + e);
               float intSpec = max(dot(h,n), 0.0);
               spec = dirLight.specular * pow(intSpec, mat.shininess);
           }
           scatteredLight += diff * attenuation;
           reflectedLight += spec * attenuation;
        }
    }
   vec4 texel, texel1;
   
   // No textures
   if(texMode == 0){
       colorOut = max(scatteredLight * mat.diffuse + reflectedLight * mat.specular, mat.ambient);
   }
   // Diffuse color and texture
   else if (texMode == 1){
       texel = texture(texmap0, DataIn.texcoord);
       colorOut = max(scatteredLight * mat.diffuse * texel + reflectedLight * mat.specular, mat.ambient * texel);
   }
   else if (texMode == 2){
       texel = texture(texmap0, DataIn.texcoord);
       colorOut = max(scatteredLight * texel + reflectedLight * mat.specular, 0.1 * texel);
   }
   else if (texMode == 3){
       texel = texture(texmap0, DataIn.texcoord);
       texel1 = texture(texmap1, DataIn.texcoord);
       colorOut = max(scatteredLight * texel * texel1 + reflectedLight * mat.specular, 0.1 * texel * texel1);
   }
}
