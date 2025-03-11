#ifndef GLOW_H
#define GLOW_H

#include "sky.h"

vec3 glowDetect(vec4 diffuse) {
  // Texture alpha: diffuse.a
  // 252/255 = max glow
  // 253/255 = partial glow
  if (diffuse.a > 0.988 && diffuse.a < 0.993) {
    vec3 glow = diffuse.rgb * diffuse.rgb;
    if (diffuse.a > 0.989) {
      return 0.4 * glow;
    }
    return glow;
  }
  return vec3(0.0,0.0,0.0);
}

vec3 glowDetectC(sampler2D tex, vec2 uv) {
  return glowDetect(texture2DLod(tex, uv, 0.0));
}

vec3 nlGlow(sampler2D tex, vec2 uv, float shimmer) {
  vec3 glow = glowDetectC(tex, uv);
  #ifdef NL_GLOW_LEAK
    // glow leak is done by interpolating 8 surrounding pixels
    // c3 c4 c5
    // c2    c6
    // c1 c8 c7
    vec2 texSize = vec2(textureSize(tex, 0));
    vec2 offset = 1.0 / texSize;

    vec3 c1 = glowDetectC(tex, uv - offset);
    vec3 c2 = glowDetectC(tex, uv + offset*vec2(-1, 0));
    vec3 c3 = glowDetectC(tex, uv + offset*vec2(-1, 1));
    vec3 c4 = glowDetectC(tex, uv + offset*vec2( 0, 1));
    vec3 c5 = glowDetectC(tex, uv + offset);
    vec3 c6 = glowDetectC(tex, uv + offset*vec2( 1, 0));
    vec3 c7 = glowDetectC(tex, uv + offset*vec2( 1,-1));
    vec3 c8 = glowDetectC(tex, uv + offset*vec2( 0,-1));

    vec2 p = uv * texSize;
    vec2 u = fract(p);
    //u *= u*(3.0 - 2.0*u);
    vec2 v = 1.0 - u;

    // corners
    vec3 g = mix(mix(c1, c3, u.y), mix(c7, c5, u.y), u.x);

    /*
    g = max(
      max(c1*min(v.x,v.y), c3*min(v.x,u.y)),
      max(c5*min(u.x,u.y), c7*min(u.x,v.y))
    );*/

    // sides
    g = max(g, max(max(c2*v.x, c4*u.y), max(c6*u.x, c8*v.y)));

    // apply attuenation and add to glow
    g = ((g*0.7 + 0.2)*g + 0.1)*g;
    glow = max(glow, g*NL_GLOW_LEAK);
  #endif

  #ifdef NL_GLOW_SHIMMER
    glow *= shimmer;
  #endif

  return glow * NL_GLOW_TEX;
}

#ifdef NL_GLOW_SHIMMER
float nlGlowShimmer(vec3 cPos, float t) {
  float shimmer = sin(0.7*dot(cPos, vec3(1.0, 1.0, 1.0)) - NL_GLOW_SHIMMER_SPEED*t);
  shimmer = sin(1.2*shimmer + 0.7*dot(cPos, vec3(-1.0, -1.0, 1.0)));
  shimmer *= shimmer;
  return mix(1.0, shimmer*shimmer, NL_GLOW_SHIMMER);
}
#endif

vec4 nlGlint(vec4 light, vec4 layerUV, sampler2D glintTexture, vec4 glintColor, vec4 tileLightColor, vec4 albedo) {
  float d = fract(dot(albedo.rgb, vec3_splat(4.0)));

  vec4 tex1 = texture2D(glintTexture, fract(layerUV.xy+0.1*d)).rgbr;
  vec4 tex2 = texture2D(glintTexture, fract(layerUV.zw+0.1*d)).rgbr;

  vec4 glint = (tex1*tex1 + tex2*tex2) * tileLightColor * glintColor;

  light.rgb = light.rgb*(1.0-0.4*glint.a) + 80.0*glint.rgb;
  light.rgb += vec3(0.1,0.0,0.1) + 0.2*spectrum(sin(layerUV.x*9.42477 + 2.0*glint.a + d));

  return light;
}

#endif