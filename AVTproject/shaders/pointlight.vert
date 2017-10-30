#version 330

uniform mat4 m_pvm;
uniform mat4 m_viewModel;
uniform mat3 m_normal;

in vec4 position;
in vec4 normal;    //por causa do gerador de geometria
in vec4 texCoord;

out Data {
    vec3 normal;
    vec3 eye;
    vec4 position;
    vec2 texcoord;
} DataOut;

void main () {
    DataOut.position = m_viewModel * position;
    DataOut.normal = normalize(m_normal * normal.xyz);
    DataOut.eye = vec3(-DataOut.position);
    DataOut.texcoord = texCoord.st;
    
    gl_Position = m_pvm * position;
}

