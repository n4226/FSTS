#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_KHR_vulkan_glsl : enable

//https://www.reddit.com/r/vulkan/comments/4gvmus/best_way_for_textures_in_shaders/ - helpful
// be weary of combined imagesamples
layout(binding = 0) uniform sampler2D mainPassResults;

layout(location = 0) out vec4 outColor;

void main() {
	outColor = texture(mainPassResults,vec2(0));
	// vec4(0.2,0.4,0.9,1);
}