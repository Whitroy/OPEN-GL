#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 TexCord;
layout(location = 3) in float texIndex;

out vec4 u_color;
out vec2 v_TextCord;
out float v_TexIndex;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * position;
	u_color = color;
	v_TextCord = TexCord;
	v_TexIndex = texIndex;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 u_color;
in vec2 v_TextCord;
in float v_TexIndex;

uniform sampler2D u_textArr[2];

void main()
{
	int index = int(v_TexIndex);
	color = texture(u_textArr[index], v_TextCord);
}