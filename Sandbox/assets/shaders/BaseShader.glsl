#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Colour;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in int a_TexIndex;

uniform mat4 u_ViewProjection;

out vec4 v_Colour;
out vec2 v_TexCoord;
flat out int v_TexIndex;

void main()
{
	v_Colour = a_Colour;
	v_TexCoord = a_TexCoord;
	v_TexIndex = a_TexIndex;
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 colour;

in vec4 v_Colour;
in vec2 v_TexCoord;
flat in int v_TexIndex;

uniform sampler2D u_Textures[32];

void main()
{
	colour = v_Colour * texture(u_Textures[v_TexIndex], v_TexCoord);
}