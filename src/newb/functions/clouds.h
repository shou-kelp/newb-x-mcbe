#ifndef CLOUDS_H
#define CLOUDS_H

#include "noise.h"
#include "sky.h"

// simple clouds 2D noise
float cloudNoise2D(vec2 p, highp float t, float rain) {
  t *= NL_CLOUD1_SPEED;
  p += t;
  p.y += 3.0*sin(0.3*p.x + 0.1*t);

  vec2 p0 = floor(p);
  vec2 u = p-p0;
  u *= u*(3.0-2.0*u);
  vec2 v = 1.0-u;

  float n = mix(
    mix(rand(p0),rand(p0+vec2(1.0,0.0)), u.x),
    mix(rand(p0+vec2(0.0,1.0)),rand(p0+vec2(1.0,1.0)), u.x),
    u.y
  );
  n *= 0.5 + 0.5*sin(p.x*0.6 - 0.5*t)*sin(p.y*0.6 + 0.8*t);
  n = min(n*(1.0+rain), 1.0);
  return n*n;
}

// simple clouds
vec4 renderCloudsSimple(nl_skycolor skycol, vec3 pos, highp float t, float rain) {
  pos.xz *= NL_CLOUD1_SCALE;
  float d = cloudNoise2D(pos.xz, t, rain);
  vec4 col = vec4(skycol.horizonEdge + skycol.zenith, smoothstep(0.1,0.6,d));
  col.rgb += 1.5*dot(col.rgb, vec3(0.3,0.4,0.3))*smoothstep(0.6,0.2,d)*col.a;
  col.rgb *= 1.0 - 0.8*rain;
  return col;
}

// rounded clouds

// rounded clouds 3D density map
float cloudDf(vec3 pos, float rain, vec2 boxiness) {
  boxiness *= 0.999;
  vec2 p0 = floor(pos.xz);
  vec2 u = max((pos.xz-p0-boxiness.x)/(1.0-boxiness.x), 0.0);
  u *= u*(3.0 - 2.0*u);

  vec4 r = vec4(rand(p0), rand(p0+vec2(1.0,0.0)), rand(p0+vec2(1.0,1.0)), rand(p0+vec2(0.0,1.0)));
  r = smoothstep(0.1001+0.2*rain, 0.1+0.2*rain*rain, r); // rain transition

  float n = mix(mix(r.x,r.y,u.x), mix(r.w,r.z,u.x), u.y);

  // round y
  n *= 1.0 - 1.5*smoothstep(boxiness.y, 2.0 - boxiness.y, 2.0*abs(pos.y-0.5));

  n = max(1.25*(n-0.2), 0.0); // smoothstep(0.2, 1.0, n)
  n *= n*(3.0 - 2.0*n);
  return n;
}

vec4 renderClouds(
    vec3 vDir, vec3 vPos, float rain, float time, vec3 horizonCol, vec3 zenithCol,
    int steps, float thickness, float thickness_rain, float speed, vec2 scale, float density, vec2 boxiness
) {
  float height = 7.0 * mix(thickness, thickness_rain, rain);
  float stepsf = float(steps);

  // Offset ray
  vec3 deltaP;
  deltaP.y = 1.0;
  deltaP.xz = height * scale * vDir.xz / (0.02 + 0.98 * abs(vDir.y));

  // Cloud pos
  vec3 pos;
  pos.y = 0.0;
  pos.xz = scale * (vPos.xz + vec2(1.0, 0.5) * (time * speed));
  pos += deltaP;

  deltaP /= -stepsf;

  vec2 d = vec2(0.0, 1.0);
  for (int i = 1; i <= steps; i++) {
    float m = cloudDf(pos, rain, boxiness);
    d.x += m;
    d.y = mix(d.y, pos.y, m);
    pos += deltaP;
  }

  // Smooth step for cloud distribution
  d.x *= smoothstep(0.12, 0.14, d.x);
  d.x /= (stepsf / density) + d.x;

  if (vPos.y < 0.0) {
    d.y = 1.0 - d.y;
  }
  //d.y = 1.0 - NL_CLOUD2_EDGE * d.y * d.y;

  // detection
  float night = max(1.1 - 3.0 * max(horizonCol.b, horizonCol.g), 0.0);
  // float dusk = max(0.0, max(horizonCol.r, horizonCol.g) - 0.5);

  vec4 col = vec4(zenithCol + horizonCol, d.x);
  col.rgb += dot(col.rgb, vec3(0.3, 0.4, 0.3)) * d.y * d.y;
  col.rgb *= 1.0 - 0.8 * rain;
  col.rgb *= 1.0 - 0.8 * night;

  /*
  if (dusk > 0.0) {
    vec3 duskColor = vec3(0.8, 0.2, 0.4);
    col.rgb = mix(col.rgb, duskColor, dusk);
  }
  */

  return col;
}

// Aurora is rendered on clouds layer
#ifdef NL_AURORA
vec4 renderAurora(vec3 p, float t, float rain, vec3 FOG_COLOR) {
  t *= NL_AURORA_VELOCITY;
  p.xz *= NL_AURORA_SCALE;
  p.xz += 0.03*sin(p.x*4.0 + 30.0*t);

  float d0 = sin(p.x*0.1 + t + sin(p.z*0.1));
  float d1 = sin(p.z*0.1 - t + sin(p.x*0.2));
  float d2 = cos(p.z*0.1 + 1.0*sin(d0 + d1*2.0) + d1*2.0 + d0*1.0);
  float d3 = cos(p.z*0.2 + 1.0*cos(d0 + d2*2.0) + d1*2.0 + d0*1.0);
  d0 *= d0; d1 *= d1; d2 *= d2; d3 *= d3;
  d2 = d0/(1.0 + d2/NL_AURORA_WIDTH);

  vec3 auroraColor = mix(NL_AURORA_COL1, NL_AURORA_COL2, d1);
  auroraColor = mix(auroraColor, NL_AURORA_COL1 * vec3(0.6, 0.8, 1.2), d3);

  // average luminance
  float lumi = dot(auroraColor, NL_AURORA_COL1);
  auroraColor = mix(vec3(lumi, lumi, lumi), auroraColor, 1.0);

  float mask = (1.0-0.8 * rain) * max(1.0-4.0 * max(FOG_COLOR.b, FOG_COLOR.g), 0.0);
  auroraColor *= NL_AURORA;

  return vec4(auroraColor, 1.0) * d2 * mask;
}
#endif

#endif
