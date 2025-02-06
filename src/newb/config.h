/* NEWB CONSTELLATION: GEMINI CONFIG */

#ifndef NL_CONFIG_H
#define NL_CONFIG_H

/*
  NEWB SHADER MAIN CONFIG
  This part contains base configuration options for the shader.

  TOGGLES
  - If [toggle] is mentioned, then
    options can be commented to disable (by adding '//')
  - eg: #define PLANTS_WAVE    -> this is ON
        //#define PLANTS_WAVE  -> this is OFF

  COLOR VALUES
  - Color format: vec3(red,green,blue)
  - 1.0 means 100%, 0.0 means 0%
  - eg: vec3(1.0,1.0,0.0) = yellow

  VALUES
  - Values must be decimal
  - eg. 32 is wrong, 32.0 is correct

  TYPES
  - Should be integer. options to choose will be mentioned there
  - eg: #define NL_CLOUD_TYPE 2

  Remember to rebuild the shader after making changes.
*/


/* Color correction */
// 1:Exponential, 2:Reinhard, 3:Extended Reinhard, 4:ACES
#define NL_TONEMAP_TYPE 4
#define NL_GAMMA        0.95
#define NL_EXPOSURE     1.70
#define NL_SATURATION   0.90
//#define NL_TINT       
#define NL_TINT_LOW     vec3(0.3, 0.5, 1.4)   // color tint for dark tone
#define NL_TINT_HIGH    vec3(1.4, 0.7, 0.3)   // color tint for light tone

/* Terrain lighting */
#define NL_SUN_INTENSITY    1.30    // 0.5 weak ~ 5.0 bright
#define NL_TORCH_INTENSITY  0.24    // 0.5 weak ~ 3.0 bright
#define NL_NIGHT_BRIGHTNESS 2.00    // 0.0 dark ~ 2.0 bright
#define NL_CAVE_BRIGHTNESS  1.25    // 0.0 dark ~ 2.0 bright
#define NL_SHADOW_INTENSITY 1.00    // 0.0 no shadow ~ 1.0 strong shadow
//#define NL_BLINKING_TORCH   // [toggle] flickering light
//#define NL_CLOUD_SHADOW     // [toggle] cloud shadow (simple clouds only)

/* Sun/moon light color on terrain */
#define NL_MORNING_SUN_COL vec3(1.0, 0.45, 0.14)
#define NL_NOON_SUN_COL    vec3(1.0, 0.74, 0.53)
#define NL_NIGHT_SUN_COL   vec3(0.5, 0.61, 0.92)

/* Ambient light on terrain (light that is added everywhere) */
#define NL_NETHER_AMBIENT vec3(2.40, 1.88, 1.22)
#define NL_END_AMBIENT    vec3(2.22, 1.49, 2.82)

/* Torch colors */
#define NL_OVERWORLD_TORCH_COL  vec3(1.35, 0.73, 0.55)
#define NL_UNDERWATER_TORCH_COL vec3(1.35, 0.73, 0.55)
#define NL_NETHER_TORCH_COL     vec3(1.25, 0.64, 0.15)
#define NL_END_TORCH_COL        vec3(0.88, 0.40, 1.20)

/* Fog */
#define NL_FOG               1.0     // [toggle] 0.1 subtle ~ 1.0 blend with sky completely
#define NL_MIST_DENSITY      0.68    // 0.0 no mist ~ 1.0 misty
#define NL_RAIN_MIST_OPACITY 0.12    // [toggle] 0.04 very subtle ~ 0.5 thick rain mist blow
//#define NL_CLOUDY_FOG        0.22    // [toggle] 0.0 subtle ~ 0.8 dense fog clouds

/* Sky colors - zenith=top, horizon=bottom */
#define NL_DAY_ZENITH_COL    vec3(0.140, 0.360, 1.000)
#define NL_DAY_HORIZON_COL   vec3(0.420, 0.845, 1.000)
#define NL_NIGHT_ZENITH_COL  vec3(0.000, 0.002, 0.010)
#define NL_NIGHT_HORIZON_COL vec3(0.005, 0.100, 0.185)
#define NL_DAWN_ZENITH_COL   vec3(0.240, 0.320, 1.000)
#define NL_DAWN_HORIZON_COL  vec3(0.900, 0.455, 1.000)
#define NL_DAWN_EDGE_COL     vec3(0.800, 0.325, 1.000)
#define NL_RAIN_ZENITH_COL   vec3(0.380, 0.420, 0.620)
#define NL_RAIN_HORIZON_COL  vec3(0.360, 0.420, 0.600)

/* End Sky */
#define NL_END_SKY_TYPE    2
#define NL_END_ZENITH_COL  vec3(0.002, 0.000, 0.008)
#define NL_END_HORIZON_COL vec3(0.080, 0.031, 0.200)

/* End Blackhole */
#define NL_BLACKHOLE    // [toggle] blackhole in the end sky
#define NL_BH_COL_LOW  vec3(0.1, 0.1, 1.0)
#define NL_BH_COL_HIGH vec3(0.6, 0.2, 0.8)
#define NL_BH_DIST     1.4 // distance 
#define NL_BH_SPEED    1.3 // animation speed 

/* Rainbow */
//#define NL_RAINBOW // [toggle] enable rainbow in sky
#define NL_RAINBOW_CLEAR 1.0     // 0.3 subtle ~ 1.7 bright during clear
#define NL_RAINBOW_RAIN  0.0     // 0.5 subtle ~ 2.0 bright during rain

/* Ore glow intensity */
#define NL_GLOW_TEX 4.4           // 0.4 weak ~ 8.0 bright
//#define NL_GLOW_SHIMMER 0.8       // [toggle] 0.1 subtle ~ 1.0 100% shimmer
#define NL_GLOW_SHIMMER_SPEED 0.9 // 0.5 slow ~ 2.0 fast
//#define NL_GLOW_LEAK 0.6          // [toggle] 0.08 subtle ~ 1.0 100% brightness of NL_GLOW_TEX

/* Waving */
#define NL_PLANTS_WAVE  0.06    // [toggle] 0.02 gentle ~ 0.4 violent
#define NL_LANTERN_WAVE 0.12    // [toggle] 0.05 subtle ~ 0.4 large swing
#define NL_WAVE_SPEED   1.80    // 0.5 slow wave ~ 5.0 very fast wave
//#define NL_EXTRA_PLANTS_WAVE    // [toggle] !dont use! wave using texture coords (1.21.0 vanilla 2048x1024)

/* Water */
#define NL_WATER_TRANSPARENCY   0.35    // 0.0 transparent ~ 1.0 normal
#define NL_WATER_BUMP           0.04    // 0.001 plain ~ 0.2 bumpy water
#define NL_WATER_WAVE_SPEED     0.26    // 0.2 calm ~ 2.0 turbulent
#define NL_WATER_TEX_OPACITY    1.88    // 0.0 plain water ~ 1.0 vanilla water texture
#define NL_WATER_WAVE                   // [toggle] wave effect
//#define NL_WATER_CLOUD_REFLECTION       // [toggle] clouds/aurora reflection
//#define NL_WATER_REFL_MASK              // [toggle] fake water reflection mask
#define NL_WATER_TINT           vec3(0.53, 0.85, 1.0)

/* Underwater */
#define NL_UNDERWATER_BRIGHTNESS 2.55    // 0.0 dark ~ 3.0 bright
#define NL_CAUSTIC_INTENSITY     3.70     // 0.5 weak ~ 5.0 bright
#define NL_UNDERWATER_WAVE       0.03    // [toggle] 0.02 subtle ~ 0.6 trippy
#define NL_UNDERWATER_STREAKS    2.20    // [toggle] 0.8 subtle ~ 2.0 bright streaks from top
#define NL_UNDERWATER_TINT       vec3(0.75, 1.00, 0.90) // fog tint color when underwater

/* Cloud type */
#define NL_CLOUD_TYPE 2 // 0:vanilla, 1:soft, 2:rounded

/* Vanilla cloud settings - make sure to remove clouds.png when using this */
#define NL_CLOUD0_THICKNESS      2.4     // 0.5 slim ~ 8.0 fat
#define NL_CLOUD0_RAIN_THICKNESS 4.0     // 0.5 slim ~ 8.0 fat
#define NL_CLOUD0_OPACITY        1.0     // 0.0 invisible ~ 1.0 opaque
//#define NL_CLOUD0_MULTILAYER

/* Soft cloud settings */
#define NL_CLOUD1_SCALE   vec2(0.06, 0.009)  // 0.003 large ~ 0.2 tiny
#define NL_CLOUD1_DEPTH   2.6     // 0.0 no bump ~ 10.0 large bumps
#define NL_CLOUD1_SPEED   0.04    // 0.0 static ~ 0.4 fast moving
#define NL_CLOUD1_DENSITY 0.8    // 0.1 less clouds ~ 0.8 more clouds
#define NL_CLOUD1_OPACITY 0.9    // 0.0 invisible ~ 1.0 opaque

/* Rounded cloud Settings */
#define NL_CLOUD2_THICKNESS      2.2     // 0.5 slim ~ 5.0 fat
#define NL_CLOUD2_RAIN_THICKNESS 2.4     // 0.5 slim ~ 5.0 fat
#define NL_CLOUD2_STEPS          5       // 3 low quality ~ 16 high quality
#define NL_CLOUD2_SCALE          vec2(0.024, 0.024)  // 0.003 large ~ 0.3 tiny
#define NL_CLOUD2_SHAPE          vec2(0.65, 1.0)     // 0.0 round ~ 1.0 box vec2(horizontal shape, vertical shape)
#define NL_CLOUD2_DENSITY        100.0   // 1.0 blurry ~ 100.0 sharp
#define NL_CLOUD2_VELOCITY       0.8     // 0.0 static ~ 4.0 very fast
//#define NL_CLOUD2_LAYER2 // [toggle] extra cloud layer
#define NL_CLOUD2_LAYER2_OFFSET         143.0   // 30.0 near ~ 300.0 very high
#define NL_CLOUD2_LAYER2_THICKNESS      2.2     // 0.7 slim ~ 5.0 fat
#define NL_CLOUD2_LAYER2_RAIN_THICKNESS 2.4     // 0.7 slim ~ 5.0 fat
#define NL_CLOUD2_LAYER2_STEPS          3       // 3 low quality ~ 16 high quality
#define NL_CLOUD2_LAYER2_SCALE          vec2(0.02, 0.02)  // 0.003 large ~ 0.3 tiny
#define NL_CLOUD2_LAYER2_SHAPE          vec2(0.65, 1.0)     // 0.0 round ~ 1.0 box vec2(horizontal shape, vertical shape)
#define NL_CLOUD2_LAYER2_DENSITY        50.0    // 1.0 blurry ~ 100.0 sharp
#define NL_CLOUD2_LAYER2_VELOCITY       0.8     // 0.0 static ~ 4.0 very fast

//#define NL_CLOUD2_EDGE 1.504 // experimental

/* Aurora settings */
//#define NL_AURORA          4.4
#define NL_AURORA_VELOCITY 0.04    // 0.0 static ~ 0.3 very fast
#define NL_AURORA_SCALE    0.08    // 0.002 large ~ 0.4 tiny
#define NL_AURORA_WIDTH    0.12    // 0.04 thin line ~ 0.4 thick lines
#define NL_AURORA_COL1     vec3(0.00, 0.60, 1.00)
#define NL_AURORA_COL2     vec3(0.12, 0.90, 0.99)

/* Shooting star */
#define NL_SHOOTING_STAR        1.0     // [toggle] 0.2 dim ~ 1.0 bright
#define NL_SHOOTING_STAR_PERIOD 8.0     // 0.4 fast ~ 12.0 slow (12 secs)
#define NL_SHOOTING_STAR_DELAY  60.0    // 0.0 no delay ~ 100.0 long time (100 secs)
#define NL_END_SHOOTING_STAR    1.0     // [toggle] 0.2 dim ~ 1.0 bright

/* Twinkling star */
//#define NL_TWINKLING_STARS      1.6     // [toggle] 0.1 dim ~ 4.0 bright 
#define NL_STARS_DAY_VISIBILITY 0.0     // 0.0 invisible ~ 1.0 visible
//#define NL_END_TWINKLING_STARS  1.8     // [toggle] 0.1 dim ~ 4.0 bright

/* Galaxy */
#define NL_GALAXY_STARS          1.4     // [toggle] 0.1 dim ~ 4.0 bright
#define NL_GALAXY_VIBRANCE       0.47    // 0.0 white ~ 1.0 colorful
#define NL_GALAXY_SPEED          0.06    // 0.01 slow motion ~ 0.2 fast motion
#define NL_GALAXY_DAY_VISIBILITY 0.0     // 0.0 invisible ~ 1.0 visible
#define NL_END_GALAXY_STARS      1.6     // [toggle] 0.1 dim ~ 4.0 bright

/* Chunk loading slide in animation */
//#define NL_CHUNK_LOAD_ANIM 20.0 // [toggle] -600.0 fall from top ~ 600.0 rise from bottom

/* Sun/Moon */
//#define NL_SUNMOON_ANGLE 45.0    // [toggle] 0.0 no tilt ~ 90.0 tilt of 90 degrees
#define NL_SUNMOON_SIZE   1.15     // 0.3 tiny ~ 4.0 massive
#define NL_SUNBLOOM       0.25     // [toggle] 0.1 dim ~ 2.0 bright 
#define NL_MOONBLOOM      0.40     // [toggle] 0.1 dim ~ 2.0 bright
#define NL_SUNBLOOM_COL   vec3(1.00, 0.50, 0.20)
#define NL_MOONBLOOM_COL  vec3(0.75, 0.75, 1.00)

/* Fake godrays during sunrise/sunset */
#define NL_GODRAY 0.8 // [toggle] 0.1 subtle ~ 0.8 strong

/* Sky reflection */
#define NL_GROUND_REFL          1.0     // [toggle] 0.2 slightly reflective ~ 1.0 fully reflect sky 
#define NL_GROUND_RAIN_WETNESS  1.0     // 0.0 no wetness ~ 1.0 fully wet blocks when raining
#define NL_GROUND_RAIN_PUDDLES  0.8     // 0.0 no genangan air ~ 1.0 puddles
//#define NL_GROUND_AURORA_REFL           // [toggle] aurora reflection on ground
#define NL_FORCE_ONLY_END_REFL         // [toggle] force ground reflection only appear in the end

/* Entity (Actor, ItemInHand) */
#define NL_ENTITY_BRIGHTNESS     0.64    // 0.1 dark ~ 1.6 bright
#define NL_ENTITY_EDGE_HIGHLIGHT 1.30    // 0.0 no highlight ~ 1.6 bright highlight

/* Weather particles */
#define NL_WEATHER_SPECK         0.15     // [toggle] 0.0 vanilla texture ~ 1.0 soft speck
#define NL_WEATHER_RAIN_SLANT    1.05     // 1.0 minimal ~ 8.0 violent
#define NL_WEATHER_PARTICLE_SIZE 1.80     // 0.5 tiny ~ 4.0 large


/*
  NEWB SHADER SUBPACK CONFIG
  This part contains custom configuration options for each subpack.

  If a value is already defined,
  then you must undefine it before modifying:
  eg: #undef OPTION_NAME

  Subpack names and flags are inside `pack_config.toml`.
  Build tool will enable corresponding flags when compiling. 
*/

#ifdef LOWEST
  #undef NL_PLANTS_WAVE
  #undef NL_LANTERN_WAVE
  #undef NL_WATER_WAVE
  #undef NL_UNDERWATER_WAVE
  #undef NL_GALAXY_STARS
  #undef NL_END_GALAXY_STARS
  #undef NL_BLACKHOLE
  #undef NL_CLOUD_TYPE
  #define NL_CLOUD_TYPE 0
#endif

#ifdef LOW
  #undef NL_PLANTS_WAVE
  #undef NL_LANTERN_WAVE
  #undef NL_WATER_WAVE
  #undef NL_UNDERWATER_WAVE
  #undef NL_GALAXY_STARS
  #undef NL_END_GALAXY_STARS
  #undef NL_BLACKHOLE
  #undef NL_CLOUD_TYPE
  #define NL_CLOUD_TYPE 1
#endif

#ifdef SMED
  #undef NL_PLANTS_WAVE
  #undef NL_LANTERN_WAVE
  #undef NL_WATER_WAVE
  #undef NL_UNDERWATER_WAVE
  #undef NL_GALAXY_STARS
  #undef NL_END_GALAXY_STARS
  #undef NL_CLOUD_TYPE
  #define NL_CLOUD_TYPE 1
  #define NL_TWINKLING_STARS 1.4
  #define NL_END_TWINKLING_STARS 1.6
#endif

#ifdef MED
  #undef NL_PLANTS_WAVE
  #undef NL_LANTERN_WAVE
  #undef NL_WATER_WAVE
  #undef NL_UNDERWATER_WAVE
  #undef NL_GALAXY_STARS
  #undef NL_END_GALAXY_STARS
  #define NL_TWINKLING_STARS 1.4
  #define NL_END_TWINKLING_STARS 1.6
#endif

#ifdef OPT
  #undef NL_PLANTS_WAVE
  #undef NL_LANTERN_WAVE
  #undef NL_WATER_WAVE
  #undef NL_UNDERWATER_WAVE
#endif


#endif