#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_KHR_vulkan_glsl : enable

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 inUv;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec3 inTangent;
layout(location = 4) in vec3 inBitangent;

void main() {
    //outUvs = inUv;
    //outNormal = inNormal;
    //gl_Position = ubo.viewProjection * modelUniform.data[drawData.modelIndex].model * vec4(inPosition, 1.0);
}