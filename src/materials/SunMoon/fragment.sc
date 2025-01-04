$input v_texcoord0, v_pos

#include <bgfx_shader.sh>

#ifndef INSTANCING
  #include <newb/config.h>
  #include <newb/functions/tonemap.h>

  uniform vec4 SunMoonColor;
  uniform vec4 ViewPositionAndTime;

  SAMPLER2D_AUTOREG(s_SunMoonTexture);
#endif

void main() {
  #ifndef INSTANCING
    #ifdef NLC_SUNMOON_BLOOM
      vec4 color = vec4_splat(0.0);

      float g = 1.0 - min(length(v_pos * 2.0), 1.0);
      g *= g * g * g;

      vec2 uv = v_texcoord0;
      ivec2 ts = textureSize(s_SunMoonTexture, 0);
      bool isMoon = ts.x > ts.y;
      if (isMoon) {
        g *= NLC_MOON_BLOOM;
        uv = vec2(0.25, 0.5) * (floor(uv * vec2(4.0, 2.0)) + 0.5 + 10.0 * v_pos.xz);
        color.rgb += g * NLC_MOON_BLOOM_COL;
      } else {
        g *= NLC_SUN_BLOOM;
        uv = 0.5 + 10.0 * v_pos.xz;
        color.rgb += g * NLC_SUN_BLOOM_COL;
      }

      if (max(abs(v_pos.x), abs(v_pos.z)) < 0.05) {
        color += texture2D(s_SunMoonTexture, uv);
      }

      color.rgb *= SunMoonColor.rgb;
      float tr = 1.0 - SunMoonColor.a;
      color.a = 1.0 - tr * tr * tr;
    #else
      vec4 color = texture2D(s_SunMoonTexture, v_texcoord0);
      color.rgb *= SunMoonColor.rgb;
      color.rgb *= 4.4 * color.rgb;
      float tr = 1.0 - SunMoonColor.a;
      color.a *= 1.0 - tr * tr * tr;

      color.rgb = colorCorrection(color.rgb);
    #endif


    gl_FragColor = color;
  #else
    gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
  #endif
}