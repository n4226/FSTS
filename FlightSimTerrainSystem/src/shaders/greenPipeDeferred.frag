#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_KHR_vulkan_glsl : enable

//https://www.reddit.com/r/vulkan/comments/4gvmus/best_way_for_textures_in_shaders/ - helpful
// be weary of combined imagesamples
layout(binding = 0) uniform sampler2D mainPassResults;

layout(location = 0) out vec4 outColor;

void main() {
	//TODO can calculate this in vertex to be more efficient
	vec2 uvs = gl_FragCoord.xy / vec2(textureSize(mainPassResults,0));
	outColor = texture(mainPassResults,uvs);

	// vec4(0.2,0.4,0.9,1);
}