@prism(type='fragment', name='Fast3D Vulkan Shader', version='1.0.0', description='Fast3D combiner shader for Vulkan', author='Ghostship')

#version 450

// Uniform layout mirrors the structs in gfx_vulkan.h (std140; everything is
// vec4-aligned on the C++ side). Set 0 = ring-buffer UBOs with dynamic
// offsets, set 1 = the 7 fast3d texture slots.
layout(std140, set = 0, binding = 0) uniform FrameUniforms {
    int frame_count;
    float noise_scale;
} frameU;

layout(std140, set = 0, binding = 1) uniform DrawUniforms {
    ivec4 tex_filter[2]; // slots 0..6, [0].xyzw = 0..3, [1].xyz = 4..6
    vec4 misc;           // x = prim_depth, y = lod_max
    vec4 inputs[6];
    vec4 fog_color;
    vec4 grayscale_color;
    vec4 uv_transform[2];
    vec4 tex_clamp[2];
    vec4 fog_params;
    vec4 palette_params[2];
    vec4 lod_params;     // x = res scale, y = prim_lod_min, z = G_TD mode
} drawU;

layout(std140, set = 0, binding = 2) uniform LightUniforms {
    vec4 lights[96]; // 32 lights x [color+kind, model dir+kc, world pos+kq]
    vec4 ambient;
    vec4 lookat_x;
    vec4 lookat_y;
    vec4 texgen[2];
    vec4 mv_rows[3];
    vec4 mv_cols[3];
    ivec4 num_lights;
} lightU;

layout(std140, set = 0, binding = 3) uniform TransformUniforms {
    vec4 mtx_palette[32]; // 8 slots x 4 vec4 rows
    vec4 y_scale;
} xformU;

@if(VERTEX_SHADER)
    layout(location = 0) in vec4 aVtxPos;
    layout(location = 1) in float aMtxSlot;

    @for(i in 0..2)
        @if(o_textures[i])
            @if(i == 0)
                layout(location = 2) in vec2 aTexCoord0;
            @else
                layout(location = 3) in vec2 aTexCoord1;
            @end
            layout(location = @{i}) out vec2 vTexCoord@{i};
        @end
    @end

    @if(o_fog)
        layout(location = 2) out float vFogFactor;
    @end

    @if(o_shade || o_lighting)
        @if(o_alpha)
            layout(location = 4) in vec4 aShade;
        @else
            layout(location = 4) in vec3 aShade;
        @end
    @end
    @if(o_shade)
        @if(o_alpha)
            layout(location = 3) out vec4 vShade;
        @else
            layout(location = 3) out vec3 vShade;
        @end
    @end

    void main() {
        // RSP position transform: matrix palette entry selected per vertex
        int mtxBase = int(aMtxSlot + 0.5) * 4;
        vec4 clipPos = aVtxPos.x * xformU.mtx_palette[mtxBase] + aVtxPos.y * xformU.mtx_palette[mtxBase + 1] +
                       aVtxPos.z * xformU.mtx_palette[mtxBase + 2] + aVtxPos.w * xformU.mtx_palette[mtxBase + 3];

        @for(i in 0..2)
            @if(o_textures[i])
                // Tile shift/origin/bilerp/size pipeline folded into one transform
                vTexCoord@{i} = vec2(aTexCoord@{i}.x * drawU.uv_transform[@{i}].x + drawU.uv_transform[@{i}].y,
                                     aTexCoord@{i}.y * drawU.uv_transform[@{i}].z + drawU.uv_transform[@{i}].w);
            @end
        @end
        @if(o_fog)
            // N64 RSP fog from clip-space z/w; fog_params.w selects the source
            // (0: computed, 1: constant register, 2: legacy vertex-alpha fallback)
            float fogW = abs(clipPos.w) < 0.001 ? 0.001 : clipPos.w;
            float fogWinv = 1.0 / fogW;
            if (fogWinv < 0.0) {
                fogWinv = 32767.0;
            }
            float fogCalc = clamp(clipPos.z * fogWinv * drawU.fog_params.x + drawU.fog_params.y, 0.0, 255.0) / 255.0;
            @if(o_shade && o_alpha)
                vFogFactor = drawU.fog_params.w > 1.5 ? aShade.a : (drawU.fog_params.w > 0.5 ? drawU.fog_params.z : fogCalc);
            @else
                vFogFactor = drawU.fog_params.w > 0.5 ? drawU.fog_params.z : fogCalc;
            @end
        @end
        @if(o_texgen)
            // N64 texgen: project the vertex normal onto the lookat vectors, then
            // run the result through the standard tile/scale UV pipeline (folded
            // into the per-draw texgen linear transforms).
            float texgenDotX = clamp(dot(aShade.xyz, lightU.lookat_x.xyz) / 127.0, -1.0, 1.0);
            float texgenDotY = clamp(dot(aShade.xyz, lightU.lookat_y.xyz) / 127.0, -1.0, 1.0);
            @if(o_texgen_linear)
                texgenDotX = acos(-texgenDotX) * 0.159155;
                texgenDotY = acos(-texgenDotY) * 0.159155;
            @else
                texgenDotX = (texgenDotX + 1.0) / 4.0;
                texgenDotY = (texgenDotY + 1.0) / 4.0;
            @end
            @if(o_textures[0])
                vTexCoord0 = vec2(texgenDotX * lightU.texgen[0].x + lightU.texgen[0].y, texgenDotY * lightU.texgen[0].z + lightU.texgen[0].w);
            @end
            @if(o_textures[1])
                vTexCoord1 = vec2(texgenDotX * lightU.texgen[1].x + lightU.texgen[1].y, texgenDotY * lightU.texgen[1].z + lightU.texgen[1].w);
            @end
        @end
        @if(o_shade && o_alpha)
            // Standard fog forces shade alpha to 1.0 (the factor rides vFogFactor);
            // blend-color mode (fog mode 1) preserves the vertex alpha.
            float shadeAlpha = aShade.a;
            @if(o_fog)
                if (drawU.fog_params.w < 0.5 || drawU.fog_params.w > 1.5) {
                    shadeAlpha = 1.0;
                }
            @end
        @end
        @if(o_point_lighting)
            // World-space position derived from the object-space vertex position
            vec3 worldPos = vec3(dot(aVtxPos, lightU.mv_cols[0]), dot(aVtxPos, lightU.mv_cols[1]), dot(aVtxPos, lightU.mv_cols[2]));
        @end
        @if(o_shade)
            @if(o_lighting)
                // N64 RSP lighting: aShade carries the raw signed vertex normal
                vec3 litColor = lightU.ambient.rgb;
                for (int i = 0; i < lightU.num_lights.x; i++) {
                    float intensity = 0.0;
                    @if(o_point_lighting)
                    if (lightU.lights[i * 3].w > 0.5) {
                        vec3 distVec = lightU.lights[i * 3 + 2].xyz - worldPos;
                        float distSq = distVec.x * distVec.x + distVec.y * distVec.y + distVec.z * distVec.z * 2.0;
                        float dist = sqrt(distSq);
                        vec3 lightModel = vec3(dot(distVec, lightU.mv_rows[0].xyz), dot(distVec, lightU.mv_rows[1].xyz), dot(distVec, lightU.mv_rows[2].xyz));
                        vec3 lightIntensity = clamp(4.0 * lightModel / distSq, -1.0, 1.0);
                        float totalIntensity = clamp(dot(lightIntensity, aShade.xyz), -1.0, 1.0);
                        float distF = floor(dist);
                        float attenuation = (distF * lightU.lights[i * 3 + 1].w * 2.0 + distF * distF * lightU.lights[i * 3 + 2].w / 8.0) / 65535.0 + 1.0;
                        intensity = totalIntensity / attenuation;
                    } else {
                        intensity = dot(aShade.xyz, lightU.lights[i * 3 + 1].xyz) / 127.0;
                    }
                    @else
                        intensity = dot(aShade.xyz, lightU.lights[i * 3 + 1].xyz) / 127.0;
                    @end
                    if (intensity > 0.0) {
                        litColor += intensity * lightU.lights[i * 3].rgb;
                    }
                }
                litColor = min(litColor, vec3(1.0));
                @if(o_alpha)
                    vShade = vec4(litColor, shadeAlpha);
                @else
                    vShade = litColor;
                @end
            @else
                @if(o_alpha)
                    vShade = vec4(aShade.rgb, shadeAlpha);
                @else
                    vShade = aShade;
                @end
            @end
        @end
        // Same clip conventions as Metal: z mapped to 0..w; y flip handled by
        // y_scale plus the negative viewport set by the backend.
        gl_Position = vec4(clipPos.x, clipPos.y * xformU.y_scale.x, (clipPos.z + clipPos.w) / 2.0, clipPos.w);
    }
@else
    layout(location = 0) out vec4 vOutColor;

    @for(i in 0..2)
        @if(o_textures[i])
            layout(location = @{i}) in vec2 vTexCoord@{i};
        @end
    @end

    @if(o_fog)
        layout(location = 2) in float vFogFactor;
    @end

    @if(o_shade)
        @if(o_alpha)
            layout(location = 3) in vec4 vShade;
        @else
            layout(location = 3) in vec3 vShade;
        @end
    @end

    @if(o_textures[0]) layout(set = 1, binding = 0) uniform sampler2D uTex0;
    @if(o_textures[1]) layout(set = 1, binding = 1) uniform sampler2D uTex1;

    @if(o_masks[0]) layout(set = 1, binding = 2) uniform sampler2D uTexMask0;
    @if(o_masks[1]) layout(set = 1, binding = 3) uniform sampler2D uTexMask1;

    @if(o_blend[0]) layout(set = 1, binding = 4) uniform sampler2D uTexBlend0;
    @if(o_blend[1]) layout(set = 1, binding = 5) uniform sampler2D uTexBlend1;

    #define TEX_OFFSET(off) texture(tex, texCoord - off / texSize)
    #define WRAP(x, low, high) mod((x)-(low), (high)-(low)) + (low)

    float random(in vec3 value) {
        float random = dot(sin(value), vec3(12.9898, 78.233, 37.719));
        return fract(sin(random) * 143758.5453);
    }

    vec4 fromLinear(vec4 linearRGB){
        bvec3 cutoff = lessThan(linearRGB.rgb, vec3(0.0031308));
        vec3 higher = vec3(1.055)*pow(linearRGB.rgb, vec3(1.0/2.4)) - vec3(0.055);
        vec3 lower = linearRGB.rgb * vec3(12.92);
        return vec4(mix(higher, lower, cutoff), linearRGB.a);
    }

    vec4 filter3point(in sampler2D tex, in vec2 texCoord, in vec2 texSize) {
        vec2 offset = fract(texCoord*texSize - vec2(0.5));
        offset -= step(1.0, offset.x + offset.y);
        vec4 c0 = TEX_OFFSET(offset);
        vec4 c1 = TEX_OFFSET(vec2(offset.x - sign(offset.x), offset.y));
        vec4 c2 = TEX_OFFSET(vec2(offset.x, offset.y - sign(offset.y)));
        return c0 + abs(offset.x)*(c1-c0) + abs(offset.y)*(c2-c0);
    }

    vec4 hookTexture2D(in int id, sampler2D tex, in vec2 uv, in vec2 texSize) {
    @if(o_three_point_filtering)
        if(drawU.tex_filter[0][id] == @{FILTER_THREE_POINT}) {
            return filter3point(tex, uv, texSize);
        }
    @end
        return texture(tex, uv);
    }

    @if(o_palette[0] || o_palette[1])
        layout(set = 1, binding = 6) uniform sampler2D uTexPal;

        // One CI tap: fetch the index (nearest sampler) and look it up in the
        // 256-entry palette texture. params.x is the CI4 bank entry offset.
        vec4 paletteTap(in sampler2D tex, in vec2 uv, in float bank) {
            float idx = texture(tex, uv).r;
            return texture(uTexPal, vec2((idx * 255.0 + bank + 0.5) / 256.0, 0.5));
        }

        // Filtering must happen after the palette lookup, like real hardware:
        // params.y selects nearest (0), bilinear (1) or N64 three-point (2).
        vec4 paletteSample(in sampler2D tex, in vec2 uv, in vec2 texSize, in vec4 params) {
            if (params.y > 1.5) {
                vec2 offset = fract(uv * texSize - vec2(0.5));
                offset -= step(1.0, offset.x + offset.y);
                vec4 c0 = paletteTap(tex, uv - offset / texSize, params.x);
                vec4 c1 = paletteTap(tex, uv - vec2(offset.x - sign(offset.x), offset.y) / texSize, params.x);
                vec4 c2 = paletteTap(tex, uv - vec2(offset.x, offset.y - sign(offset.y)) / texSize, params.x);
                return c0 + abs(offset.x) * (c1 - c0) + abs(offset.y) * (c2 - c0);
            } else if (params.y > 0.5) {
                vec2 t = uv * texSize - 0.5;
                vec2 f = fract(t);
                vec2 base = (floor(t) + 0.5) / texSize;
                vec2 px = vec2(1.0, 0.0) / texSize;
                vec2 py = vec2(0.0, 1.0) / texSize;
                vec4 c00 = paletteTap(tex, base, params.x);
                vec4 c10 = paletteTap(tex, base + px, params.x);
                vec4 c01 = paletteTap(tex, base + py, params.x);
                vec4 c11 = paletteTap(tex, base + px + py, params.x);
                return mix(mix(c00, c10, f.x), mix(c01, c11, f.x), f.y);
            } else {
                return paletteTap(tex, uv, params.x);
            }
        }
    @end

    void main() {
        @if(o_uses_lod)
            float lodFrac = 0.0;
        @end
        @for(i in 0..2)
            @if(o_textures[i])
                @{s = o_clamp[i][0]}
                @{t = o_clamp[i][1]}

                vec2 texSize@{i} = vec2(textureSize(uTex@{i}, 0));

                @if(!s && !t)
                    vec2 vTexCoordAdj@{i} = vTexCoord@{i};
                @else
                    @if(s && t)
                        vec2 vTexCoordAdj@{i} = clamp(vTexCoord@{i}, 0.5 / texSize@{i}, drawU.tex_clamp[@{i}].xy);
                    @elseif(s)
                        vec2 vTexCoordAdj@{i} = vec2(clamp(vTexCoord@{i}.s, 0.5 / texSize@{i}.s, drawU.tex_clamp[@{i}].x), vTexCoord@{i}.t);
                    @else
                        vec2 vTexCoordAdj@{i} = vec2(vTexCoord@{i}.s, clamp(vTexCoord@{i}.t, 0.5 / texSize@{i}.t, drawU.tex_clamp[@{i}].y));
                    @end
                @end

                @if(i == 0)
                    @if(o_uses_lod)
                        // N64 texture LOD (RDP-accurate): max absolute UV derivative,
                        // linear fraction between tiles, sharpen/detail handling
                        vec2 lodScaled = vTexCoordAdj0 * texSize0;
                        vec2 lodMaxD = max(abs(dFdx(lodScaled)), abs(dFdy(lodScaled)));
                        float lodMaxDst = max(max(lodMaxD.x, lodMaxD.y) * drawU.lod_params.x, 0.000001);
                        if (drawU.lod_params.z > 0.5) { // sharpen or detail
                            lodMaxDst = max(lodMaxDst, drawU.lod_params.y);
                        }
                        float lodTileBase = floor(log2(lodMaxDst));
                        lodFrac = lodMaxDst / exp2(max(lodTileBase, 0.0)) - 1.0;
                        if (drawU.lod_params.z > 0.5 && drawU.lod_params.z < 1.5 && lodMaxDst < 1.0) { // sharpen
                            lodFrac = lodMaxDst - 1.0;
                        }
                        if (drawU.lod_params.z > 1.5) { // detail: tile 0 is the detail texture
                            if (lodFrac < 0.0) {
                                lodFrac = lodMaxDst;
                            }
                            lodTileBase += 1.0;
                        } else if (lodTileBase >= drawU.misc.y) {
                            lodFrac = 1.0;
                        }
                        if (drawU.lod_params.z > 0.5) {
                            lodTileBase = max(lodTileBase, 0.0);
                        } else {
                            lodFrac = max(lodFrac, 0.0);
                        }
                        float lodTile0 = clamp(lodTileBase, 0.0, drawU.misc.y);
                        float lodTile1 = clamp(lodTileBase + 1.0, 0.0, drawU.misc.y);
                    @end
                @end

                @if(i == 0)
                    @if(o_mip_lod)
                        vec4 texVal0 = textureLod(uTex0, vTexCoordAdj0, lodTile0);
                    @elseif(o_palette[0])
                        vec4 texVal0 = paletteSample(uTex0, vTexCoordAdj0, texSize0, drawU.palette_params[0]);
                    @else
                        vec4 texVal@{i} = hookTexture2D(@{i}, uTex@{i}, vTexCoordAdj@{i}, texSize@{i});
                    @end
                @else
                    @if(o_palette[1])
                        vec4 texVal1 = paletteSample(uTex1, vTexCoordAdj1, texSize1, drawU.palette_params[1]);
                    @else
                        vec4 texVal@{i} = hookTexture2D(@{i}, uTex@{i}, vTexCoordAdj@{i}, texSize@{i});
                    @end
                @end

                @if(o_masks[i])
                    vec2 maskSize@{i} = vec2(textureSize(uTexMask@{i}, 0));

                    vec4 maskVal@{i} = hookTexture2D(@{i}, uTexMask@{i}, vTexCoordAdj@{i}, maskSize@{i});

                    @if(o_blend[i])
                        vec4 blendVal@{i} = hookTexture2D(@{i}, uTexBlend@{i}, vTexCoordAdj@{i}, texSize@{i});
                    @else
                        vec4 blendVal@{i} = vec4(0, 0, 0, 0);
                    @end

                    texVal@{i} = mix(texVal@{i}, blendVal@{i}, maskVal@{i}.a);
                @end
            @end
        @end

        @if(o_mip_lod)
            // TEXEL1 reads the next mip level of texture 0
            vec4 texVal1 = textureLod(uTex0, vTexCoordAdj0, lodTile1);
        @end

        @if(o_two_tile_lod)
            // N64 LOD tile selection: TEXEL0's tile is clamped to the max level,
            // but the hardware's second texel is always lod_tile + 1 — at
            // magnification TEXEL1 still reads the real tile 1 (Paper Mario's
            // sprite shading relies on this with a stale G_TL_LOD).
            texVal0 = lodTile0 < 0.5 ? texVal0 : texVal1;
        @end

        @if(o_alpha)
            vec4 texel;
        @else
            vec3 texel;
        @end

        @if(o_2cyc)
            @{f_range = 2}
        @else
            @{f_range = 1}
        @end

        @for(c in 0..f_range)
            @if(c == 1)
                @if(o_alpha)
                    @if(o_c[c][1][2] == SHADER_COMBINED)
                        texel.a = WRAP(texel.a, -1.01, 1.01);
                    @else
                        texel.a = WRAP(texel.a, -0.51, 1.51);
                    @end
                @end

                @if(o_c[c][0][2] == SHADER_COMBINED)
                    texel.rgb = WRAP(texel.rgb, -1.01, 1.01);
                @else
                    texel.rgb = WRAP(texel.rgb, -0.51, 1.51);
                @end
            @end

            @if(!o_color_alpha_same[c] && o_alpha)
                texel = vec4(@{
                append_formula(o_c[c], o_do_single[c][0],
                            o_do_multiply[c][0], o_do_mix[c][0], false, false, true, c == 0)
                }, @{append_formula(o_c[c], o_do_single[c][1],
                            o_do_multiply[c][1], o_do_mix[c][1], true, true, true, c == 0)
                });
            @else
                texel = @{append_formula(o_c[c], o_do_single[c][0],
                            o_do_multiply[c][0], o_do_mix[c][0], o_alpha, false,
                            o_alpha, c == 0)};
            @end
        @end

        texel = WRAP(texel, -0.51, 1.51);
        texel = clamp(texel, 0.0, 1.0);
        @if(o_fog)
            @if(o_alpha)
                texel = vec4(mix(texel.rgb, drawU.fog_color.rgb, vFogFactor), texel.a);
            @else
                texel = mix(texel, drawU.fog_color.rgb, vFogFactor);
            @end
        @end

        @if(o_texture_edge && o_alpha)
            if (texel.a > 0.19) texel.a = 1.0; else discard;
        @end

        @if(o_alpha && o_noise)
            texel.a *= floor(clamp(random(vec3(floor(gl_FragCoord.xy * frameU.noise_scale), float(frameU.frame_count))) + texel.a, 0.0, 1.0));
        @end

        @if(o_grayscale)
            float intensity = (texel.r + texel.g + texel.b) / 3.0;
            vec3 new_texel = drawU.grayscale_color.rgb * intensity;
            texel.rgb = mix(texel.rgb, new_texel, drawU.grayscale_color.a);
        @end

        @if(o_alpha)
            @if(o_alpha_threshold)
                if (texel.a < 8.0 / 256.0) discard;
            @end
            @if(o_invisible)
                texel.a = 0.0;
            @end
            vOutColor = texel;
        @else
            vOutColor = vec4(texel, 1.0);
        @end

        @if(srgb_mode)
            vOutColor = fromLinear(vOutColor);
        @end

        @if(o_prim_depth)
            gl_FragDepth = drawU.misc.x;
        @end
    }
@end
