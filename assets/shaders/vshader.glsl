#version 330 core

layout (location=0) in vec3 m_position;
layout (location=1) in vec3 m_color;
layout (location=2) in vec2 m_texCoord;

out vec3 m_fColor;
out vec2 m_fTexCoord;

void main(){
    gl_Position = vec4(m_position, 1.0);
    m_fColor = m_color;
    m_fTexCoord = m_texCoord;
}
