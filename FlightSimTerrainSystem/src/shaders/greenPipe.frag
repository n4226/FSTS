#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_KHR_vulkan_glsl : enable

layout(location = 0) out vec4 outColor;

void main() {
	outColor = vec4(0,0.8,0.2,1);

}