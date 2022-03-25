#version 330 core

out vec4 FragDataColor;

uniform sampler2D m_fTexture;
in vec3 m_fColor;
in vec2 m_fTexCoord;

void main(){
    FragDataColor = texture(m_fTexture, m_fTexCoord) * vec4(m_fColor, 1.0);
}
