#ifndef INSTANCING
$input v_texcoord0, v_posTime
#endif

#include <bgfx_shader.sh>

#ifndef INSTANCING
  #include <newb/main.sh>

  SAMPLER2D_AUTOREG(s_SkyTexture);
#endif

void main() {
  #ifndef INSTANCING
    vec3 viewDir = normalize(v_posTime.xyz);
    vec4 diffuse = texture2D(s_SkyTexture, v_texcoord0);

    nl_environment env;
    env.end = true;
    env.underwater = v_posTime.w < 1.0;
    env.rainFactor = 0.0;

    vec3 color = renderEndSky(getEndHorizonCol(), getEndZenithCol(), viewDir, v_posTime.w);
    //color += 0.2 * diffuse.rgb;

    #ifdef NL_END_SHOOTING_STAR
      color.rgb += NL_END_SHOOTING_STAR*nlRenderShootingStar(viewDir, color, v_posTime.w);
    #endif
    #ifdef NL_END_TWINKLING_STARS
      color.rgb += NL_END_TWINKLING_STARS*nlRenderStars(viewDir, color, env, v_posTime.w);
    #endif
    #ifdef NL_END_GALAXY_STARS
      color.rgb += NL_END_GALAXY_STARS*nlRenderGalaxy(viewDir, color, env, v_posTime.w);
    #endif
    #ifdef NL_BLACKHOLE
      vec4 bh = renderBlackhole(viewDir, v_posTime.w);
      color *= bh.a;
      color += bh.rgb;
    #endif

    color = colorCorrection(color);

    gl_FragColor = vec4(color, 1.0);
  #else
    gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
  #endif
}