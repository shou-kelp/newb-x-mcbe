$input a_color0, a_position
$output v_color0

#include <bgfx_shader.sh>

uniform vec4 StarsColor;

void main() {
#ifndef INSTANCING
  vec3 pos = a_position;
  vec3 worldPos = mul(u_model[0], vec4(pos, 1.0)).xyz;

  // vec4 color = a_color0;
  // color.rgb *= 0.6 + 0.4*sin(2.0*pos);
  vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
  color.rgb *= StarsColor.rgb;

  v_color0 = color;
  gl_Position = mul(u_viewProj, vec4(worldPos, 1.0));
#else
  gl_Position = vec4(0.0,0.0,0.0,0.0);
#endif
}