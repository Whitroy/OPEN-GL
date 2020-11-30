#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCord;

out vec2 v_TextCord;
uniform mat4 mvp;

void main()
{
   gl_Position = mvp *position;
   v_TextCord = texCord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_color;
uniform sampler2D u_Texture;

in vec2 v_TextCord;

void main()
{
    vec4 textColor = texture(u_Texture, v_TextCord);
    color = textColor;
}