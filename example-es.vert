precision mediump float;

uniform mat4 perspective;
uniform mat4 view;
uniform mat4 model;
uniform mat3 view_rot_inv;

attribute vec4 vertex;
attribute vec3 normal;
attribute vec4 color;

varying vec4 frag_color;
varying vec3 world_normal;
varying vec4 world_pos;
varying vec3 world_view;

void main()
{
    world_pos = model * vertex;
    vec4 view_pos = view * world_pos;
    gl_Position = perspective * view_pos;

    world_normal = mat3(model) * normal;

    world_view = view_rot_inv*-normalize(view_pos.xyz);

    frag_color = color;
}
