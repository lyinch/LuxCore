#include <string>
namespace slg { namespace ocl {
std::string KernelSource_light_types = 
"#line 2 \"light_types.cl\"\n"
"\n"
"/***************************************************************************\n"
" * Copyright 1998-2013 by authors (see AUTHORS.txt)                        *\n"
" *                                                                         *\n"
" *   This file is part of LuxRender.                                       *\n"
" *                                                                         *\n"
" * Licensed under the Apache License, Version 2.0 (the \"License\");         *\n"
" * you may not use this file except in compliance with the License.        *\n"
" * You may obtain a copy of the License at                                 *\n"
" *                                                                         *\n"
" *     http://www.apache.org/licenses/LICENSE-2.0                          *\n"
" *                                                                         *\n"
" * Unless required by applicable law or agreed to in writing, software     *\n"
" * distributed under the License is distributed on an \"AS IS\" BASIS,       *\n"
" * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*\n"
" * See the License for the specific language governing permissions and     *\n"
" * limitations under the License.                                          *\n"
" ***************************************************************************/\n"
"\n"
"typedef enum {\n"
"	TYPE_IL, TYPE_IL_SKY, TYPE_SUN, TYPE_TRIANGLE, TYPE_POINT,\n"
"	LIGHT_SOURCE_TYPE_COUNT\n"
"} LightSourceType;\n"
"\n"
"typedef struct {\n"
"	TextureMapping2D mapping;\n"
"	unsigned int imageMapIndex;\n"
"	unsigned int distributionOffset;\n"
"} InfiniteLightParam;\n"
"\n"
"typedef struct {\n"
"	float thetaS;\n"
"	float phiS;\n"
"	float zenith_Y, zenith_x, zenith_y;\n"
"	float perez_Y[6], perez_x[6], perez_y[6];\n"
"} SkyLightParam;\n"
"\n"
"typedef struct {\n"
"	Vector sunDir;\n"
"	float turbidity, relSize;\n"
"	// XY Vectors for cone sampling\n"
"	Vector x, y;\n"
"	float cosThetaMax;\n"
"	Spectrum sunColor;\n"
"} SunLightParam;\n"
"\n"
"typedef struct {\n"
"	Vector absolutePos;\n"
"	Spectrum emittedFactor;\n"
"} PointLightParam;\n"
"\n"
"typedef struct {\n"
"	Transform light2World;\n"
"	Spectrum gain;\n"
"\n"
"	union {\n"
"		SunLightParam sun;\n"
"		SkyLightParam sky;\n"
"		InfiniteLightParam infinite;\n"
"		PointLightParam point;\n"
"	};\n"
"} NotIntersecableLightSource;\n"
"\n"
"typedef struct {\n"
"	Vector v0, v1, v2;\n"
"	UV uv0, uv1, uv2;\n"
"	float invArea;\n"
"\n"
"	unsigned int materialIndex;\n"
"	unsigned int lightSceneIndex;\n"
"} TriangleLightParam;\n"
"\n"
"typedef struct {\n"
"	LightSourceType type;\n"
"	unsigned int lightSceneIndex;\n"
"	unsigned int lightID;\n"
"	int samples;\n"
"	// Type of indirect paths where a light source is visible with a direct hit. It is\n"
"	// an OR of DIFFUSE, GLOSSY and SPECULAR.\n"
"	BSDFEvent visibility;\n"
"	\n"
"	union {\n"
"		NotIntersecableLightSource notIntersecable;\n"
"		TriangleLightParam triangle;\n"
"	};\n"
"} LightSource;\n"
"\n"
"\n"
"//------------------------------------------------------------------------------\n"
"// Some macro trick in order to have more readable code\n"
"//------------------------------------------------------------------------------\n"
"\n"
"#if defined(SLG_OPENCL_KERNEL)\n"
"\n"
"#if defined(PARAM_HAS_INFINITELIGHT)\n"
"#define LIGHTS_PARAM_DECL , __global LightSource *lights, __global uint *envLightIndices, const uint envLightCount, __global uint *meshTriLightDefsOffset, __global float *infiniteLightDistribution, __global float *lightsDistribution MATERIALS_PARAM_DECL\n"
"#define LIGHTS_PARAM , lights, envLightIndices, envLightCount, meshTriLightDefsOffset, infiniteLightDistribution, lightsDistribution MATERIALS_PARAM\n"
"#elif defined(PARAM_HAS_SUNLIGHT) || defined(PARAM_HAS_SKYLIGHT)\n"
"#define LIGHTS_PARAM_DECL , __global LightSource *lights, __global uint *envLightIndices, const uint envLightCount, __global uint *meshTriLightDefsOffset, __global float *lightsDistribution MATERIALS_PARAM_DECL\n"
"#define LIGHTS_PARAM , lights, envLightIndices, envLightCount, meshTriLightDefsOffset, lightsDistribution MATERIALS_PARAM\n"
"#else\n"
"#define LIGHTS_PARAM_DECL , __global LightSource *lights, __global uint *meshTriLightDefsOffset, __global float *lightsDistribution MATERIALS_PARAM_DECL\n"
"#define LIGHTS_PARAM , lights, meshTriLightDefsOffset, lightsDistribution MATERIALS_PARAM\n"
"#endif\n"
"\n"
"#endif\n"
; } }
