////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Header File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   glX.h
//  Version:     v1.00
//  Created:     by GlSpecLoader
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef VE_GLX

extern "C"
{

#ifndef GLX_VERSION_1_1
#define GLX_VERSION_1_1 1
#endif

#ifndef GLX_VERSION_1_2
#define GLX_VERSION_1_2 1
#endif

#ifndef GLX_VERSION_1_3
#define GLX_VERSION_1_3 1
#endif

#ifndef GLX_VERSION_1_4
#define GLX_VERSION_1_4 1
#endif

#ifndef GLX_SGIS_multisample
#define GLX_SGIS_multisample 1
#endif

#ifndef GLX_EXT_visual_info
#define GLX_EXT_visual_info 1
#endif

#ifndef GLX_SGI_swap_control
#define GLX_SGI_swap_control 1
#endif

#ifndef GLX_SGI_video_sync
#define GLX_SGI_video_sync 1
#endif

#ifndef GLX_SGI_make_current_read
#define GLX_SGI_make_current_read 1
#endif

#ifndef GLX_SGIX_video_source
#define GLX_SGIX_video_source 1
#endif

#ifndef GLX_EXT_visual_rating
#define GLX_EXT_visual_rating 1
#endif

#ifndef GLX_EXT_import_context
#define GLX_EXT_import_context 1
#endif

#ifndef GLX_SGIX_fbconfig
#define GLX_SGIX_fbconfig 1
#endif

#ifndef GLX_SGIX_pbuffer
#define GLX_SGIX_pbuffer 1
#endif

#ifndef GLX_SGI_cushion
#define GLX_SGI_cushion 1
#endif

#ifndef GLX_SGIX_video_resize
#define GLX_SGIX_video_resize 1
#endif

#ifndef GLX_SGIX_dmbuffer
#define GLX_SGIX_dmbuffer 1
#endif

#ifndef GLX_SGIX_swap_group
#define GLX_SGIX_swap_group 1
#endif

#ifndef GLX_SGIX_swap_barrier
#define GLX_SGIX_swap_barrier 1
#endif

#ifndef GLX_SGIS_blended_overlay
#define GLX_SGIS_blended_overlay 1
#endif

#ifndef GLX_SGIS_shared_multisample
#define GLX_SGIS_shared_multisample 1
#endif

#ifndef GLX_SUN_get_transparent_index
#define GLX_SUN_get_transparent_index 1
#endif

#ifndef GLX_3DFX_multisample
#define GLX_3DFX_multisample 1
#endif

#ifndef GLX_MESA_copy_sub_buffer
#define GLX_MESA_copy_sub_buffer 1
#endif

#ifndef GLX_MESA_pixmap_colormap
#define GLX_MESA_pixmap_colormap 1
#endif

#ifndef GLX_MESA_release_buffers
#define GLX_MESA_release_buffers 1
#endif

#ifndef GLX_MESA_set_3dfx_mode
#define GLX_MESA_set_3dfx_mode 1
#endif

#ifndef GLX_SGIX_visual_select_group
#define GLX_SGIX_visual_select_group 1
#endif

#ifndef GLX_SGIX_hyperpipe
#define GLX_SGIX_hyperpipe 1
#endif

#ifndef GLX_VENDOR
#define GLX_VENDOR 0x1
#endif

#ifndef GLX_VERSION
#define GLX_VERSION 0x2
#endif

#ifndef GLX_EXTENSIONS
#define GLX_EXTENSIONS 0x3
#endif

#ifndef GLX_BAD_SCREEN
#define GLX_BAD_SCREEN 1
#endif

#ifndef GLX_BAD_ATTRIBUTE
#define GLX_BAD_ATTRIBUTE 2
#endif

#ifndef GLX_NO_EXTENSION
#define GLX_NO_EXTENSION 3
#endif

#ifndef GLX_BAD_VISUAL
#define GLX_BAD_VISUAL 4
#endif

#ifndef GLX_BAD_CONTEXT
#define GLX_BAD_CONTEXT 5
#endif

#ifndef GLX_BAD_VALUE
#define GLX_BAD_VALUE 6
#endif

#ifndef GLX_BAD_ENUM
#define GLX_BAD_ENUM 7
#endif

#ifndef GLX_BAD_HYPERPIPE_CONFIG_SGIX
#define GLX_BAD_HYPERPIPE_CONFIG_SGIX 91
#endif

#ifndef GLX_BAD_HYPERPIPE_SGIX
#define GLX_BAD_HYPERPIPE_SGIX 92
#endif

#ifndef GLX_WINDOW_BIT
#define GLX_WINDOW_BIT 0x00000001
#endif

#ifndef GLX_PIXMAP_BIT
#define GLX_PIXMAP_BIT 0x00000002
#endif

#ifndef GLX_PBUFFER_BIT
#define GLX_PBUFFER_BIT 0x00000004
#endif

#ifndef GLX_WINDOW_BIT_SGIX
#define GLX_WINDOW_BIT_SGIX 0x00000001
#endif

#ifndef GLX_PIXMAP_BIT_SGIX
#define GLX_PIXMAP_BIT_SGIX 0x00000002
#endif

#ifndef GLX_PBUFFER_BIT_SGIX
#define GLX_PBUFFER_BIT_SGIX 0x00000004
#endif

#ifndef GLX_RGBA_BIT
#define GLX_RGBA_BIT 0x00000001
#endif

#ifndef GLX_COLOR_INDEX_BIT
#define GLX_COLOR_INDEX_BIT 0x00000002
#endif

#ifndef GLX_RGBA_BIT_SGIX
#define GLX_RGBA_BIT_SGIX 0x00000001
#endif

#ifndef GLX_COLOR_INDEX_BIT_SGIX
#define GLX_COLOR_INDEX_BIT_SGIX 0x00000002
#endif

#ifndef GLX_RGBA_FLOAT_BIT_ARB
#define GLX_RGBA_FLOAT_BIT_ARB 0x00000004
#endif

#ifndef GLX_RGBA_UNSIGNED_FLOAT_BIT_EXT
#define GLX_RGBA_UNSIGNED_FLOAT_BIT_EXT 0x00000008
#endif

#ifndef GLX_SYNC_FRAME_SGIX
#define GLX_SYNC_FRAME_SGIX 0x00000000
#endif

#ifndef GLX_SYNC_SWAP_SGIX
#define GLX_SYNC_SWAP_SGIX 0x00000001
#endif

#ifndef GLX_PBUFFER_CLOBBER_MASK
#define GLX_PBUFFER_CLOBBER_MASK 0x08000000
#endif

#ifndef GLX_BUFFER_CLOBBER_MASK_SGIX
#define GLX_BUFFER_CLOBBER_MASK_SGIX 0x08000000
#endif

#ifndef GLX_BUFFER_SWAP_COMPLETE_INTEL_MASK
#define GLX_BUFFER_SWAP_COMPLETE_INTEL_MASK 0x04000000
#endif

#ifndef GLX_FRONT_LEFT_BUFFER_BIT
#define GLX_FRONT_LEFT_BUFFER_BIT 0x00000001
#endif

#ifndef GLX_FRONT_RIGHT_BUFFER_BIT
#define GLX_FRONT_RIGHT_BUFFER_BIT 0x00000002
#endif

#ifndef GLX_BACK_LEFT_BUFFER_BIT
#define GLX_BACK_LEFT_BUFFER_BIT 0x00000004
#endif

#ifndef GLX_BACK_RIGHT_BUFFER_BIT
#define GLX_BACK_RIGHT_BUFFER_BIT 0x00000008
#endif

#ifndef GLX_AUX_BUFFERS_BIT
#define GLX_AUX_BUFFERS_BIT 0x00000010
#endif

#ifndef GLX_DEPTH_BUFFER_BIT
#define GLX_DEPTH_BUFFER_BIT 0x00000020
#endif

#ifndef GLX_STENCIL_BUFFER_BIT
#define GLX_STENCIL_BUFFER_BIT 0x00000040
#endif

#ifndef GLX_ACCUM_BUFFER_BIT
#define GLX_ACCUM_BUFFER_BIT 0x00000080
#endif

#ifndef GLX_FRONT_LEFT_BUFFER_BIT_SGIX
#define GLX_FRONT_LEFT_BUFFER_BIT_SGIX 0x00000001
#endif

#ifndef GLX_FRONT_RIGHT_BUFFER_BIT_SGIX
#define GLX_FRONT_RIGHT_BUFFER_BIT_SGIX 0x00000002
#endif

#ifndef GLX_BACK_LEFT_BUFFER_BIT_SGIX
#define GLX_BACK_LEFT_BUFFER_BIT_SGIX 0x00000004
#endif

#ifndef GLX_BACK_RIGHT_BUFFER_BIT_SGIX
#define GLX_BACK_RIGHT_BUFFER_BIT_SGIX 0x00000008
#endif

#ifndef GLX_AUX_BUFFERS_BIT_SGIX
#define GLX_AUX_BUFFERS_BIT_SGIX 0x00000010
#endif

#ifndef GLX_DEPTH_BUFFER_BIT_SGIX
#define GLX_DEPTH_BUFFER_BIT_SGIX 0x00000020
#endif

#ifndef GLX_STENCIL_BUFFER_BIT_SGIX
#define GLX_STENCIL_BUFFER_BIT_SGIX 0x00000040
#endif

#ifndef GLX_ACCUM_BUFFER_BIT_SGIX
#define GLX_ACCUM_BUFFER_BIT_SGIX 0x00000080
#endif

#ifndef GLX_SAMPLE_BUFFERS_BIT_SGIX
#define GLX_SAMPLE_BUFFERS_BIT_SGIX 0x00000100
#endif

#ifndef GLX_HYPERPIPE_DISPLAY_PIPE_SGIX
#define GLX_HYPERPIPE_DISPLAY_PIPE_SGIX 0x00000001
#endif

#ifndef GLX_HYPERPIPE_RENDER_PIPE_SGIX
#define GLX_HYPERPIPE_RENDER_PIPE_SGIX 0x00000002
#endif

#ifndef GLX_PIPE_RECT_SGIX
#define GLX_PIPE_RECT_SGIX 0x00000001
#endif

#ifndef GLX_PIPE_RECT_LIMITS_SGIX
#define GLX_PIPE_RECT_LIMITS_SGIX 0x00000002
#endif

#ifndef GLX_HYPERPIPE_STEREO_SGIX
#define GLX_HYPERPIPE_STEREO_SGIX 0x00000003
#endif

#ifndef GLX_HYPERPIPE_PIXEL_AVERAGE_SGIX
#define GLX_HYPERPIPE_PIXEL_AVERAGE_SGIX 0x00000004
#endif

#ifndef GLX_HYPERPIPE_PIPE_NAME_LENGTH_SGIX
#define GLX_HYPERPIPE_PIPE_NAME_LENGTH_SGIX 80
#endif

#ifndef GLX_TEXTURE_1D_BIT_EXT
#define GLX_TEXTURE_1D_BIT_EXT 0x00000001
#endif

#ifndef GLX_TEXTURE_2D_BIT_EXT
#define GLX_TEXTURE_2D_BIT_EXT 0x00000002
#endif

#ifndef GLX_TEXTURE_RECTANGLE_BIT_EXT
#define GLX_TEXTURE_RECTANGLE_BIT_EXT 0x00000004
#endif

#ifndef GLX_CONTEXT_DEBUG_BIT_ARB
#define GLX_CONTEXT_DEBUG_BIT_ARB 0x00000001
#endif

#ifndef GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB
#define GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x00000002
#endif

#ifndef GLX_CONTEXT_ROBUST_ACCESS_BIT_ARB
#define GLX_CONTEXT_ROBUST_ACCESS_BIT_ARB 0x00000004
#endif

#ifndef GLX_CONTEXT_RESET_ISOLATION_BIT_ARB
#define GLX_CONTEXT_RESET_ISOLATION_BIT_ARB 0x00000008
#endif

#ifndef GLX_CONTEXT_CORE_PROFILE_BIT_ARB
#define GLX_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#endif

#ifndef GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
#define GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#endif

#ifndef GLX_CONTEXT_ES2_PROFILE_BIT_EXT
#define GLX_CONTEXT_ES2_PROFILE_BIT_EXT 0x00000004
#endif

#ifndef GLX_USE_GL
#define GLX_USE_GL 1
#endif

#ifndef GLX_BUFFER_SIZE
#define GLX_BUFFER_SIZE 2
#endif

#ifndef GLX_LEVEL
#define GLX_LEVEL 3
#endif

#ifndef GLX_RGBA
#define GLX_RGBA 4
#endif

#ifndef GLX_DOUBLEBUFFER
#define GLX_DOUBLEBUFFER 5
#endif

#ifndef GLX_STEREO
#define GLX_STEREO 6
#endif

#ifndef GLX_AUX_BUFFERS
#define GLX_AUX_BUFFERS 7
#endif

#ifndef GLX_RED_SIZE
#define GLX_RED_SIZE 8
#endif

#ifndef GLX_GREEN_SIZE
#define GLX_GREEN_SIZE 9
#endif

#ifndef GLX_BLUE_SIZE
#define GLX_BLUE_SIZE 10
#endif

#ifndef GLX_ALPHA_SIZE
#define GLX_ALPHA_SIZE 11
#endif

#ifndef GLX_DEPTH_SIZE
#define GLX_DEPTH_SIZE 12
#endif

#ifndef GLX_STENCIL_SIZE
#define GLX_STENCIL_SIZE 13
#endif

#ifndef GLX_ACCUM_RED_SIZE
#define GLX_ACCUM_RED_SIZE 14
#endif

#ifndef GLX_ACCUM_GREEN_SIZE
#define GLX_ACCUM_GREEN_SIZE 15
#endif

#ifndef GLX_ACCUM_BLUE_SIZE
#define GLX_ACCUM_BLUE_SIZE 16
#endif

#ifndef GLX_ACCUM_ALPHA_SIZE
#define GLX_ACCUM_ALPHA_SIZE 17
#endif

#ifndef GLX_CONFIG_CAVEAT
#define GLX_CONFIG_CAVEAT 0x20
#endif

#ifndef GLX_X_VISUAL_TYPE
#define GLX_X_VISUAL_TYPE 0x22
#endif

#ifndef GLX_TRANSPARENT_TYPE
#define GLX_TRANSPARENT_TYPE 0x23
#endif

#ifndef GLX_TRANSPARENT_INDEX_VALUE
#define GLX_TRANSPARENT_INDEX_VALUE 0x24
#endif

#ifndef GLX_TRANSPARENT_RED_VALUE
#define GLX_TRANSPARENT_RED_VALUE 0x25
#endif

#ifndef GLX_TRANSPARENT_GREEN_VALUE
#define GLX_TRANSPARENT_GREEN_VALUE 0x26
#endif

#ifndef GLX_TRANSPARENT_BLUE_VALUE
#define GLX_TRANSPARENT_BLUE_VALUE 0x27
#endif

#ifndef GLX_TRANSPARENT_ALPHA_VALUE
#define GLX_TRANSPARENT_ALPHA_VALUE 0x28
#endif

#ifndef GLX_DONT_CARE
#define GLX_DONT_CARE 0xFFFFFFFF
#endif

#ifndef GLX_NONE
#define GLX_NONE 0x8000
#endif

#ifndef GLX_SLOW_CONFIG
#define GLX_SLOW_CONFIG 0x8001
#endif

#ifndef GLX_TRUE_COLOR
#define GLX_TRUE_COLOR 0x8002
#endif

#ifndef GLX_DIRECT_COLOR
#define GLX_DIRECT_COLOR 0x8003
#endif

#ifndef GLX_PSEUDO_COLOR
#define GLX_PSEUDO_COLOR 0x8004
#endif

#ifndef GLX_STATIC_COLOR
#define GLX_STATIC_COLOR 0x8005
#endif

#ifndef GLX_GRAY_SCALE
#define GLX_GRAY_SCALE 0x8006
#endif

#ifndef GLX_STATIC_GRAY
#define GLX_STATIC_GRAY 0x8007
#endif

#ifndef GLX_TRANSPARENT_RGB
#define GLX_TRANSPARENT_RGB 0x8008
#endif

#ifndef GLX_TRANSPARENT_INDEX
#define GLX_TRANSPARENT_INDEX 0x8009
#endif

#ifndef GLX_VISUAL_ID
#define GLX_VISUAL_ID 0x800B
#endif

#ifndef GLX_SCREEN
#define GLX_SCREEN 0x800C
#endif

#ifndef GLX_NON_CONFORMANT_CONFIG
#define GLX_NON_CONFORMANT_CONFIG 0x800D
#endif

#ifndef GLX_DRAWABLE_TYPE
#define GLX_DRAWABLE_TYPE 0x8010
#endif

#ifndef GLX_RENDER_TYPE
#define GLX_RENDER_TYPE 0x8011
#endif

#ifndef GLX_X_RENDERABLE
#define GLX_X_RENDERABLE 0x8012
#endif

#ifndef GLX_FBCONFIG_ID
#define GLX_FBCONFIG_ID 0x8013
#endif

#ifndef GLX_RGBA_TYPE
#define GLX_RGBA_TYPE 0x8014
#endif

#ifndef GLX_COLOR_INDEX_TYPE
#define GLX_COLOR_INDEX_TYPE 0x8015
#endif

#ifndef GLX_MAX_PBUFFER_WIDTH
#define GLX_MAX_PBUFFER_WIDTH 0x8016
#endif

#ifndef GLX_MAX_PBUFFER_HEIGHT
#define GLX_MAX_PBUFFER_HEIGHT 0x8017
#endif

#ifndef GLX_MAX_PBUFFER_PIXELS
#define GLX_MAX_PBUFFER_PIXELS 0x8018
#endif

#ifndef GLX_PRESERVED_CONTENTS
#define GLX_PRESERVED_CONTENTS 0x801B
#endif

#ifndef GLX_LARGEST_PBUFFER
#define GLX_LARGEST_PBUFFER 0x801C
#endif

#ifndef GLX_WIDTH
#define GLX_WIDTH 0x801D
#endif

#ifndef GLX_HEIGHT
#define GLX_HEIGHT 0x801E
#endif

#ifndef GLX_EVENT_MASK
#define GLX_EVENT_MASK 0x801F
#endif

#ifndef GLX_DAMAGED
#define GLX_DAMAGED 0x8020
#endif

#ifndef GLX_SAVED
#define GLX_SAVED 0x8021
#endif

#ifndef GLX_WINDOW
#define GLX_WINDOW 0x8022
#endif

#ifndef GLX_PBUFFER
#define GLX_PBUFFER 0x8023
#endif

#ifndef GLX_PBUFFER_HEIGHT
#define GLX_PBUFFER_HEIGHT 0x8040
#endif

#ifndef GLX_PBUFFER_WIDTH
#define GLX_PBUFFER_WIDTH 0x8041
#endif

#ifndef GLX_VISUAL_CAVEAT_EXT
#define GLX_VISUAL_CAVEAT_EXT 0x20
#endif

#ifndef GLX_X_VISUAL_TYPE_EXT
#define GLX_X_VISUAL_TYPE_EXT 0x22
#endif

#ifndef GLX_TRANSPARENT_TYPE_EXT
#define GLX_TRANSPARENT_TYPE_EXT 0x23
#endif

#ifndef GLX_TRANSPARENT_INDEX_VALUE_EXT
#define GLX_TRANSPARENT_INDEX_VALUE_EXT 0x24
#endif

#ifndef GLX_TRANSPARENT_RED_VALUE_EXT
#define GLX_TRANSPARENT_RED_VALUE_EXT 0x25
#endif

#ifndef GLX_TRANSPARENT_GREEN_VALUE_EXT
#define GLX_TRANSPARENT_GREEN_VALUE_EXT 0x26
#endif

#ifndef GLX_TRANSPARENT_BLUE_VALUE_EXT
#define GLX_TRANSPARENT_BLUE_VALUE_EXT 0x27
#endif

#ifndef GLX_TRANSPARENT_ALPHA_VALUE_EXT
#define GLX_TRANSPARENT_ALPHA_VALUE_EXT 0x28
#endif

#ifndef GLX_NONE_EXT
#define GLX_NONE_EXT 0x8000
#endif

#ifndef GLX_SLOW_VISUAL_EXT
#define GLX_SLOW_VISUAL_EXT 0x8001
#endif

#ifndef GLX_TRUE_COLOR_EXT
#define GLX_TRUE_COLOR_EXT 0x8002
#endif

#ifndef GLX_DIRECT_COLOR_EXT
#define GLX_DIRECT_COLOR_EXT 0x8003
#endif

#ifndef GLX_PSEUDO_COLOR_EXT
#define GLX_PSEUDO_COLOR_EXT 0x8004
#endif

#ifndef GLX_STATIC_COLOR_EXT
#define GLX_STATIC_COLOR_EXT 0x8005
#endif

#ifndef GLX_GRAY_SCALE_EXT
#define GLX_GRAY_SCALE_EXT 0x8006
#endif

#ifndef GLX_STATIC_GRAY_EXT
#define GLX_STATIC_GRAY_EXT 0x8007
#endif

#ifndef GLX_TRANSPARENT_RGB_EXT
#define GLX_TRANSPARENT_RGB_EXT 0x8008
#endif

#ifndef GLX_TRANSPARENT_INDEX_EXT
#define GLX_TRANSPARENT_INDEX_EXT 0x8009
#endif

#ifndef GLX_SHARE_CONTEXT_EXT
#define GLX_SHARE_CONTEXT_EXT 0x800A
#endif

#ifndef GLX_VISUAL_ID_EXT
#define GLX_VISUAL_ID_EXT 0x800B
#endif

#ifndef GLX_SCREEN_EXT
#define GLX_SCREEN_EXT 0x800C
#endif

#ifndef GLX_NON_CONFORMANT_VISUAL_EXT
#define GLX_NON_CONFORMANT_VISUAL_EXT 0x800D
#endif

#ifndef GLX_DRAWABLE_TYPE_SGIX
#define GLX_DRAWABLE_TYPE_SGIX 0x8010
#endif

#ifndef GLX_RENDER_TYPE_SGIX
#define GLX_RENDER_TYPE_SGIX 0x8011
#endif

#ifndef GLX_X_RENDERABLE_SGIX
#define GLX_X_RENDERABLE_SGIX 0x8012
#endif

#ifndef GLX_FBCONFIG_ID_SGIX
#define GLX_FBCONFIG_ID_SGIX 0x8013
#endif

#ifndef GLX_RGBA_TYPE_SGIX
#define GLX_RGBA_TYPE_SGIX 0x8014
#endif

#ifndef GLX_COLOR_INDEX_TYPE_SGIX
#define GLX_COLOR_INDEX_TYPE_SGIX 0x8015
#endif

#ifndef GLX_MAX_PBUFFER_WIDTH_SGIX
#define GLX_MAX_PBUFFER_WIDTH_SGIX 0x8016
#endif

#ifndef GLX_MAX_PBUFFER_HEIGHT_SGIX
#define GLX_MAX_PBUFFER_HEIGHT_SGIX 0x8017
#endif

#ifndef GLX_MAX_PBUFFER_PIXELS_SGIX
#define GLX_MAX_PBUFFER_PIXELS_SGIX 0x8018
#endif

#ifndef GLX_OPTIMAL_PBUFFER_WIDTH_SGIX
#define GLX_OPTIMAL_PBUFFER_WIDTH_SGIX 0x8019
#endif

#ifndef GLX_OPTIMAL_PBUFFER_HEIGHT_SGIX
#define GLX_OPTIMAL_PBUFFER_HEIGHT_SGIX 0x801A
#endif

#ifndef GLX_PRESERVED_CONTENTS_SGIX
#define GLX_PRESERVED_CONTENTS_SGIX 0x801B
#endif

#ifndef GLX_LARGEST_PBUFFER_SGIX
#define GLX_LARGEST_PBUFFER_SGIX 0x801C
#endif

#ifndef GLX_WIDTH_SGIX
#define GLX_WIDTH_SGIX 0x801D
#endif

#ifndef GLX_HEIGHT_SGIX
#define GLX_HEIGHT_SGIX 0x801E
#endif

#ifndef GLX_EVENT_MASK_SGIX
#define GLX_EVENT_MASK_SGIX 0x801F
#endif

#ifndef GLX_DAMAGED_SGIX
#define GLX_DAMAGED_SGIX 0x8020
#endif

#ifndef GLX_SAVED_SGIX
#define GLX_SAVED_SGIX 0x8021
#endif

#ifndef GLX_WINDOW_SGIX
#define GLX_WINDOW_SGIX 0x8022
#endif

#ifndef GLX_PBUFFER_SGIX
#define GLX_PBUFFER_SGIX 0x8023
#endif

#ifndef GLX_DIGITAL_MEDIA_PBUFFER_SGIX
#define GLX_DIGITAL_MEDIA_PBUFFER_SGIX 0x8024
#endif

#ifndef GLX_BLENDED_RGBA_SGIS
#define GLX_BLENDED_RGBA_SGIS 0x8025
#endif

#ifndef GLX_MULTISAMPLE_SUB_RECT_WIDTH_SGIS
#define GLX_MULTISAMPLE_SUB_RECT_WIDTH_SGIS 0x8026
#endif

#ifndef GLX_MULTISAMPLE_SUB_RECT_HEIGHT_SGIS
#define GLX_MULTISAMPLE_SUB_RECT_HEIGHT_SGIS 0x8027
#endif

#ifndef GLX_VISUAL_SELECT_GROUP_SGIX
#define GLX_VISUAL_SELECT_GROUP_SGIX 0x8028
#endif

#ifndef GLX_HYPERPIPE_ID_SGIX
#define GLX_HYPERPIPE_ID_SGIX 0x8030
#endif

#ifndef GLX_SAMPLE_BUFFERS_SGIS
#define GLX_SAMPLE_BUFFERS_SGIS 100000
#endif

#ifndef GLX_SAMPLES_SGIS
#define GLX_SAMPLES_SGIS 100001
#endif

#ifndef GLX_SAMPLE_BUFFERS_ARB
#define GLX_SAMPLE_BUFFERS_ARB 100000
#endif

#ifndef GLX_SAMPLES_ARB
#define GLX_SAMPLES_ARB 100001
#endif

#ifndef GLX_SAMPLE_BUFFERS
#define GLX_SAMPLE_BUFFERS 100000
#endif

#ifndef GLX_SAMPLES
#define GLX_SAMPLES 100001
#endif

#ifndef GLX_COVERAGE_SAMPLES_NV
#define GLX_COVERAGE_SAMPLES_NV 100001
#endif

#ifndef GLX_NUM_VIDEO_SLOTS_NV
#define GLX_NUM_VIDEO_SLOTS_NV 0x20F0
#endif

#ifndef GLX_SWAP_INTERVAL_EXT
#define GLX_SWAP_INTERVAL_EXT 0x20F1
#endif

#ifndef GLX_MAX_SWAP_INTERVAL_EXT
#define GLX_MAX_SWAP_INTERVAL_EXT 0x20F2
#endif

#ifndef GLX_LATE_SWAPS_TEAR_EXT
#define GLX_LATE_SWAPS_TEAR_EXT 0x20F3
#endif

#ifndef GLX_BACK_BUFFER_AGE_EXT
#define GLX_BACK_BUFFER_AGE_EXT 0x20F4
#endif

#ifndef GLX_GPU_VENDOR_AMD
#define GLX_GPU_VENDOR_AMD 0x1F00
#endif

#ifndef GLX_GPU_RENDERER_STRING_AMD
#define GLX_GPU_RENDERER_STRING_AMD 0x1F01
#endif

#ifndef GLX_GPU_OPENGL_VERSION_STRING_AMD
#define GLX_GPU_OPENGL_VERSION_STRING_AMD 0x1F02
#endif

#ifndef GLX_GPU_FASTEST_TARGET_GPUS_AMD
#define GLX_GPU_FASTEST_TARGET_GPUS_AMD 0x21A2
#endif

#ifndef GLX_GPU_RAM_AMD
#define GLX_GPU_RAM_AMD 0x21A3
#endif

#ifndef GLX_GPU_CLOCK_AMD
#define GLX_GPU_CLOCK_AMD 0x21A4
#endif

#ifndef GLX_GPU_NUM_PIPES_AMD
#define GLX_GPU_NUM_PIPES_AMD 0x21A5
#endif

#ifndef GLX_GPU_NUM_SIMD_AMD
#define GLX_GPU_NUM_SIMD_AMD 0x21A6
#endif

#ifndef GLX_GPU_NUM_RB_AMD
#define GLX_GPU_NUM_RB_AMD 0x21A7
#endif

#ifndef GLX_GPU_NUM_SPI_AMD
#define GLX_GPU_NUM_SPI_AMD 0x21A8
#endif

#ifndef GLX_LOSE_CONTEXT_ON_RESET_ARB
#define GLX_LOSE_CONTEXT_ON_RESET_ARB 0x8252
#endif

#ifndef GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB
#define GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#endif

#ifndef GLX_NO_RESET_NOTIFICATION_ARB
#define GLX_NO_RESET_NOTIFICATION_ARB 0x8261
#endif

#ifndef GLX_CONTEXT_PROFILE_MASK_ARB
#define GLX_CONTEXT_PROFILE_MASK_ARB 0x9126
#endif


/* Header file version number, required by OpenGL ABI for Linux */
/* glxext.h last updated 2012/02/29 */
/* Current version at http://www.opengl.org/registry/ */
#define GLX_GLXEXT_VERSION 33
#ifndef GLX_WINDOW_BIT
#define GLX_WINDOW_BIT 0x00000001
#endif

#ifndef GLX_PIXMAP_BIT
#define GLX_PIXMAP_BIT 0x00000002
#endif

#ifndef GLX_PBUFFER_BIT
#define GLX_PBUFFER_BIT 0x00000004
#endif

#ifndef GLX_RGBA_BIT
#define GLX_RGBA_BIT 0x00000001
#endif

#ifndef GLX_COLOR_INDEX_BIT
#define GLX_COLOR_INDEX_BIT 0x00000002
#endif

#ifndef GLX_PBUFFER_CLOBBER_MASK
#define GLX_PBUFFER_CLOBBER_MASK 0x08000000
#endif

#ifndef GLX_FRONT_LEFT_BUFFER_BIT
#define GLX_FRONT_LEFT_BUFFER_BIT 0x00000001
#endif

#ifndef GLX_FRONT_RIGHT_BUFFER_BIT
#define GLX_FRONT_RIGHT_BUFFER_BIT 0x00000002
#endif

#ifndef GLX_BACK_LEFT_BUFFER_BIT
#define GLX_BACK_LEFT_BUFFER_BIT 0x00000004
#endif

#ifndef GLX_BACK_RIGHT_BUFFER_BIT
#define GLX_BACK_RIGHT_BUFFER_BIT 0x00000008
#endif

#ifndef GLX_AUX_BUFFERS_BIT
#define GLX_AUX_BUFFERS_BIT 0x00000010
#endif

#ifndef GLX_DEPTH_BUFFER_BIT
#define GLX_DEPTH_BUFFER_BIT 0x00000020
#endif

#ifndef GLX_STENCIL_BUFFER_BIT
#define GLX_STENCIL_BUFFER_BIT 0x00000040
#endif

#ifndef GLX_ACCUM_BUFFER_BIT
#define GLX_ACCUM_BUFFER_BIT 0x00000080
#endif

#ifndef GLX_CONFIG_CAVEAT
#define GLX_CONFIG_CAVEAT 0x20
#endif

#ifndef GLX_X_VISUAL_TYPE
#define GLX_X_VISUAL_TYPE 0x22
#endif

#ifndef GLX_TRANSPARENT_TYPE
#define GLX_TRANSPARENT_TYPE 0x23
#endif

#ifndef GLX_TRANSPARENT_INDEX_VALUE
#define GLX_TRANSPARENT_INDEX_VALUE 0x24
#endif

#ifndef GLX_TRANSPARENT_RED_VALUE
#define GLX_TRANSPARENT_RED_VALUE 0x25
#endif

#ifndef GLX_TRANSPARENT_GREEN_VALUE
#define GLX_TRANSPARENT_GREEN_VALUE 0x26
#endif

#ifndef GLX_TRANSPARENT_BLUE_VALUE
#define GLX_TRANSPARENT_BLUE_VALUE 0x27
#endif

#ifndef GLX_TRANSPARENT_ALPHA_VALUE
#define GLX_TRANSPARENT_ALPHA_VALUE 0x28
#endif

#ifndef GLX_DONT_CARE
#define GLX_DONT_CARE 0xFFFFFFFF
#endif

#ifndef GLX_NONE
#define GLX_NONE 0x8000
#endif

#ifndef GLX_SLOW_CONFIG
#define GLX_SLOW_CONFIG 0x8001
#endif

#ifndef GLX_TRUE_COLOR
#define GLX_TRUE_COLOR 0x8002
#endif

#ifndef GLX_DIRECT_COLOR
#define GLX_DIRECT_COLOR 0x8003
#endif

#ifndef GLX_PSEUDO_COLOR
#define GLX_PSEUDO_COLOR 0x8004
#endif

#ifndef GLX_STATIC_COLOR
#define GLX_STATIC_COLOR 0x8005
#endif

#ifndef GLX_GRAY_SCALE
#define GLX_GRAY_SCALE 0x8006
#endif

#ifndef GLX_STATIC_GRAY
#define GLX_STATIC_GRAY 0x8007
#endif

#ifndef GLX_TRANSPARENT_RGB
#define GLX_TRANSPARENT_RGB 0x8008
#endif

#ifndef GLX_TRANSPARENT_INDEX
#define GLX_TRANSPARENT_INDEX 0x8009
#endif

#ifndef GLX_VISUAL_ID
#define GLX_VISUAL_ID 0x800B
#endif

#ifndef GLX_SCREEN
#define GLX_SCREEN 0x800C
#endif

#ifndef GLX_NON_CONFORMANT_CONFIG
#define GLX_NON_CONFORMANT_CONFIG 0x800D
#endif

#ifndef GLX_DRAWABLE_TYPE
#define GLX_DRAWABLE_TYPE 0x8010
#endif

#ifndef GLX_RENDER_TYPE
#define GLX_RENDER_TYPE 0x8011
#endif

#ifndef GLX_X_RENDERABLE
#define GLX_X_RENDERABLE 0x8012
#endif

#ifndef GLX_FBCONFIG_ID
#define GLX_FBCONFIG_ID 0x8013
#endif

#ifndef GLX_RGBA_TYPE
#define GLX_RGBA_TYPE 0x8014
#endif

#ifndef GLX_COLOR_INDEX_TYPE
#define GLX_COLOR_INDEX_TYPE 0x8015
#endif

#ifndef GLX_MAX_PBUFFER_WIDTH
#define GLX_MAX_PBUFFER_WIDTH 0x8016
#endif

#ifndef GLX_MAX_PBUFFER_HEIGHT
#define GLX_MAX_PBUFFER_HEIGHT 0x8017
#endif

#ifndef GLX_MAX_PBUFFER_PIXELS
#define GLX_MAX_PBUFFER_PIXELS 0x8018
#endif

#ifndef GLX_PRESERVED_CONTENTS
#define GLX_PRESERVED_CONTENTS 0x801B
#endif

#ifndef GLX_LARGEST_PBUFFER
#define GLX_LARGEST_PBUFFER 0x801C
#endif

#ifndef GLX_WIDTH
#define GLX_WIDTH 0x801D
#endif

#ifndef GLX_HEIGHT
#define GLX_HEIGHT 0x801E
#endif

#ifndef GLX_EVENT_MASK
#define GLX_EVENT_MASK 0x801F
#endif

#ifndef GLX_DAMAGED
#define GLX_DAMAGED 0x8020
#endif

#ifndef GLX_SAVED
#define GLX_SAVED 0x8021
#endif

#ifndef GLX_WINDOW
#define GLX_WINDOW 0x8022
#endif

#ifndef GLX_PBUFFER
#define GLX_PBUFFER 0x8023
#endif

#ifndef GLX_PBUFFER_HEIGHT
#define GLX_PBUFFER_HEIGHT 0x8040
#endif

#ifndef GLX_PBUFFER_WIDTH
#define GLX_PBUFFER_WIDTH 0x8041
#endif

#ifndef GLX_SAMPLE_BUFFERS
#define GLX_SAMPLE_BUFFERS 100000
#endif

#ifndef GLX_SAMPLES
#define GLX_SAMPLES 100001
#endif

#ifndef GLX_SAMPLE_BUFFERS_ARB
#define GLX_SAMPLE_BUFFERS_ARB 100000
#endif

#ifndef GLX_SAMPLES_ARB
#define GLX_SAMPLES_ARB 100001
#endif

#ifndef GLX_CONTEXT_ALLOW_BUFFER_BYTE_ORDER_MISMATCH_ARB
#define GLX_CONTEXT_ALLOW_BUFFER_BYTE_ORDER_MISMATCH_ARB 0x2095
#endif

#ifndef GLX_RGBA_FLOAT_TYPE_ARB
#define GLX_RGBA_FLOAT_TYPE_ARB 0x20B9
#endif

#ifndef GLX_RGBA_FLOAT_BIT_ARB
#define GLX_RGBA_FLOAT_BIT_ARB 0x00000004
#endif

#ifndef GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB
#define GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB 0x20B2
#endif

#ifndef GLX_CONTEXT_DEBUG_BIT_ARB
#define GLX_CONTEXT_DEBUG_BIT_ARB 0x00000001
#endif

#ifndef GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB
#define GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB 0x00000002
#endif

#ifndef GLX_CONTEXT_MAJOR_VERSION_ARB
#define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#endif

#ifndef GLX_CONTEXT_MINOR_VERSION_ARB
#define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092
#endif

#ifndef GLX_CONTEXT_FLAGS_ARB
#define GLX_CONTEXT_FLAGS_ARB 0x2094
#endif

#ifndef GLX_CONTEXT_CORE_PROFILE_BIT_ARB
#define GLX_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#endif

#ifndef GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB
#define GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#endif

#ifndef GLX_CONTEXT_PROFILE_MASK_ARB
#define GLX_CONTEXT_PROFILE_MASK_ARB 0x9126
#endif

#ifndef GLX_CONTEXT_ROBUST_ACCESS_BIT_ARB
#define GLX_CONTEXT_ROBUST_ACCESS_BIT_ARB 0x00000004
#endif

#ifndef GLX_LOSE_CONTEXT_ON_RESET_ARB
#define GLX_LOSE_CONTEXT_ON_RESET_ARB 0x8252
#endif

#ifndef GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB
#define GLX_CONTEXT_RESET_NOTIFICATION_STRATEGY_ARB 0x8256
#endif

#ifndef GLX_NO_RESET_NOTIFICATION_ARB
#define GLX_NO_RESET_NOTIFICATION_ARB 0x8261
#endif

#ifndef GLX_SAMPLE_BUFFERS_SGIS
#define GLX_SAMPLE_BUFFERS_SGIS 100000
#endif

#ifndef GLX_SAMPLES_SGIS
#define GLX_SAMPLES_SGIS 100001
#endif

#ifndef GLX_X_VISUAL_TYPE_EXT
#define GLX_X_VISUAL_TYPE_EXT 0x22
#endif

#ifndef GLX_TRANSPARENT_TYPE_EXT
#define GLX_TRANSPARENT_TYPE_EXT 0x23
#endif

#ifndef GLX_TRANSPARENT_INDEX_VALUE_EXT
#define GLX_TRANSPARENT_INDEX_VALUE_EXT 0x24
#endif

#ifndef GLX_TRANSPARENT_RED_VALUE_EXT
#define GLX_TRANSPARENT_RED_VALUE_EXT 0x25
#endif

#ifndef GLX_TRANSPARENT_GREEN_VALUE_EXT
#define GLX_TRANSPARENT_GREEN_VALUE_EXT 0x26
#endif

#ifndef GLX_TRANSPARENT_BLUE_VALUE_EXT
#define GLX_TRANSPARENT_BLUE_VALUE_EXT 0x27
#endif

#ifndef GLX_TRANSPARENT_ALPHA_VALUE_EXT
#define GLX_TRANSPARENT_ALPHA_VALUE_EXT 0x28
#endif

#ifndef GLX_NONE_EXT
#define GLX_NONE_EXT 0x8000
#endif

#ifndef GLX_TRUE_COLOR_EXT
#define GLX_TRUE_COLOR_EXT 0x8002
#endif

#ifndef GLX_DIRECT_COLOR_EXT
#define GLX_DIRECT_COLOR_EXT 0x8003
#endif

#ifndef GLX_PSEUDO_COLOR_EXT
#define GLX_PSEUDO_COLOR_EXT 0x8004
#endif

#ifndef GLX_STATIC_COLOR_EXT
#define GLX_STATIC_COLOR_EXT 0x8005
#endif

#ifndef GLX_GRAY_SCALE_EXT
#define GLX_GRAY_SCALE_EXT 0x8006
#endif

#ifndef GLX_STATIC_GRAY_EXT
#define GLX_STATIC_GRAY_EXT 0x8007
#endif

#ifndef GLX_TRANSPARENT_RGB_EXT
#define GLX_TRANSPARENT_RGB_EXT 0x8008
#endif

#ifndef GLX_TRANSPARENT_INDEX_EXT
#define GLX_TRANSPARENT_INDEX_EXT 0x8009
#endif

#ifndef GLX_VISUAL_CAVEAT_EXT
#define GLX_VISUAL_CAVEAT_EXT 0x20
#endif

#ifndef GLX_SLOW_VISUAL_EXT
#define GLX_SLOW_VISUAL_EXT 0x8001
#endif

#ifndef GLX_NON_CONFORMANT_VISUAL_EXT
#define GLX_NON_CONFORMANT_VISUAL_EXT 0x800D
#endif

#ifndef GLX_SHARE_CONTEXT_EXT
#define GLX_SHARE_CONTEXT_EXT 0x800A
#endif

#ifndef GLX_VISUAL_ID_EXT
#define GLX_VISUAL_ID_EXT 0x800B
#endif

#ifndef GLX_SCREEN_EXT
#define GLX_SCREEN_EXT 0x800C
#endif

#ifndef GLX_WINDOW_BIT_SGIX
#define GLX_WINDOW_BIT_SGIX 0x00000001
#endif

#ifndef GLX_PIXMAP_BIT_SGIX
#define GLX_PIXMAP_BIT_SGIX 0x00000002
#endif

#ifndef GLX_RGBA_BIT_SGIX
#define GLX_RGBA_BIT_SGIX 0x00000001
#endif

#ifndef GLX_COLOR_INDEX_BIT_SGIX
#define GLX_COLOR_INDEX_BIT_SGIX 0x00000002
#endif

#ifndef GLX_DRAWABLE_TYPE_SGIX
#define GLX_DRAWABLE_TYPE_SGIX 0x8010
#endif

#ifndef GLX_RENDER_TYPE_SGIX
#define GLX_RENDER_TYPE_SGIX 0x8011
#endif

#ifndef GLX_X_RENDERABLE_SGIX
#define GLX_X_RENDERABLE_SGIX 0x8012
#endif

#ifndef GLX_FBCONFIG_ID_SGIX
#define GLX_FBCONFIG_ID_SGIX 0x8013
#endif

#ifndef GLX_RGBA_TYPE_SGIX
#define GLX_RGBA_TYPE_SGIX 0x8014
#endif

#ifndef GLX_COLOR_INDEX_TYPE_SGIX
#define GLX_COLOR_INDEX_TYPE_SGIX 0x8015
#endif

#ifndef GLX_PBUFFER_BIT_SGIX
#define GLX_PBUFFER_BIT_SGIX 0x00000004
#endif

#ifndef GLX_BUFFER_CLOBBER_MASK_SGIX
#define GLX_BUFFER_CLOBBER_MASK_SGIX 0x08000000
#endif

#ifndef GLX_FRONT_LEFT_BUFFER_BIT_SGIX
#define GLX_FRONT_LEFT_BUFFER_BIT_SGIX 0x00000001
#endif

#ifndef GLX_FRONT_RIGHT_BUFFER_BIT_SGIX
#define GLX_FRONT_RIGHT_BUFFER_BIT_SGIX 0x00000002
#endif

#ifndef GLX_BACK_LEFT_BUFFER_BIT_SGIX
#define GLX_BACK_LEFT_BUFFER_BIT_SGIX 0x00000004
#endif

#ifndef GLX_BACK_RIGHT_BUFFER_BIT_SGIX
#define GLX_BACK_RIGHT_BUFFER_BIT_SGIX 0x00000008
#endif

#ifndef GLX_AUX_BUFFERS_BIT_SGIX
#define GLX_AUX_BUFFERS_BIT_SGIX 0x00000010
#endif

#ifndef GLX_DEPTH_BUFFER_BIT_SGIX
#define GLX_DEPTH_BUFFER_BIT_SGIX 0x00000020
#endif

#ifndef GLX_STENCIL_BUFFER_BIT_SGIX
#define GLX_STENCIL_BUFFER_BIT_SGIX 0x00000040
#endif

#ifndef GLX_ACCUM_BUFFER_BIT_SGIX
#define GLX_ACCUM_BUFFER_BIT_SGIX 0x00000080
#endif

#ifndef GLX_SAMPLE_BUFFERS_BIT_SGIX
#define GLX_SAMPLE_BUFFERS_BIT_SGIX 0x00000100
#endif

#ifndef GLX_MAX_PBUFFER_WIDTH_SGIX
#define GLX_MAX_PBUFFER_WIDTH_SGIX 0x8016
#endif

#ifndef GLX_MAX_PBUFFER_HEIGHT_SGIX
#define GLX_MAX_PBUFFER_HEIGHT_SGIX 0x8017
#endif

#ifndef GLX_MAX_PBUFFER_PIXELS_SGIX
#define GLX_MAX_PBUFFER_PIXELS_SGIX 0x8018
#endif

#ifndef GLX_OPTIMAL_PBUFFER_WIDTH_SGIX
#define GLX_OPTIMAL_PBUFFER_WIDTH_SGIX 0x8019
#endif

#ifndef GLX_OPTIMAL_PBUFFER_HEIGHT_SGIX
#define GLX_OPTIMAL_PBUFFER_HEIGHT_SGIX 0x801A
#endif

#ifndef GLX_PRESERVED_CONTENTS_SGIX
#define GLX_PRESERVED_CONTENTS_SGIX 0x801B
#endif

#ifndef GLX_LARGEST_PBUFFER_SGIX
#define GLX_LARGEST_PBUFFER_SGIX 0x801C
#endif

#ifndef GLX_WIDTH_SGIX
#define GLX_WIDTH_SGIX 0x801D
#endif

#ifndef GLX_HEIGHT_SGIX
#define GLX_HEIGHT_SGIX 0x801E
#endif

#ifndef GLX_EVENT_MASK_SGIX
#define GLX_EVENT_MASK_SGIX 0x801F
#endif

#ifndef GLX_DAMAGED_SGIX
#define GLX_DAMAGED_SGIX 0x8020
#endif

#ifndef GLX_SAVED_SGIX
#define GLX_SAVED_SGIX 0x8021
#endif

#ifndef GLX_WINDOW_SGIX
#define GLX_WINDOW_SGIX 0x8022
#endif

#ifndef GLX_PBUFFER_SGIX
#define GLX_PBUFFER_SGIX 0x8023
#endif

#ifndef GLX_SYNC_FRAME_SGIX
#define GLX_SYNC_FRAME_SGIX 0x00000000
#endif

#ifndef GLX_SYNC_SWAP_SGIX
#define GLX_SYNC_SWAP_SGIX 0x00000001
#endif

#ifndef GLX_DIGITAL_MEDIA_PBUFFER_SGIX
#define GLX_DIGITAL_MEDIA_PBUFFER_SGIX 0x8024
#endif

#ifndef GLX_BLENDED_RGBA_SGIS
#define GLX_BLENDED_RGBA_SGIS 0x8025
#endif

#ifndef GLX_MULTISAMPLE_SUB_RECT_WIDTH_SGIS
#define GLX_MULTISAMPLE_SUB_RECT_WIDTH_SGIS 0x8026
#endif

#ifndef GLX_MULTISAMPLE_SUB_RECT_HEIGHT_SGIS
#define GLX_MULTISAMPLE_SUB_RECT_HEIGHT_SGIS 0x8027
#endif

#ifndef GLX_SAMPLE_BUFFERS_3DFX
#define GLX_SAMPLE_BUFFERS_3DFX 0x8050
#endif

#ifndef GLX_SAMPLES_3DFX
#define GLX_SAMPLES_3DFX 0x8051
#endif

#ifndef GLX_3DFX_WINDOW_MODE_MESA
#define GLX_3DFX_WINDOW_MODE_MESA 0x1
#endif

#ifndef GLX_3DFX_FULLSCREEN_MODE_MESA
#define GLX_3DFX_FULLSCREEN_MODE_MESA 0x2
#endif

#ifndef GLX_VISUAL_SELECT_GROUP_SGIX
#define GLX_VISUAL_SELECT_GROUP_SGIX 0x8028
#endif

#ifndef GLX_SWAP_METHOD_OML
#define GLX_SWAP_METHOD_OML 0x8060
#endif

#ifndef GLX_SWAP_EXCHANGE_OML
#define GLX_SWAP_EXCHANGE_OML 0x8061
#endif

#ifndef GLX_SWAP_COPY_OML
#define GLX_SWAP_COPY_OML 0x8062
#endif

#ifndef GLX_SWAP_UNDEFINED_OML
#define GLX_SWAP_UNDEFINED_OML 0x8063
#endif

#ifndef GLX_FLOAT_COMPONENTS_NV
#define GLX_FLOAT_COMPONENTS_NV 0x20B0
#endif

#ifndef GLX_HYPERPIPE_PIPE_NAME_LENGTH_SGIX
#define GLX_HYPERPIPE_PIPE_NAME_LENGTH_SGIX 80
#endif

#ifndef GLX_BAD_HYPERPIPE_CONFIG_SGIX
#define GLX_BAD_HYPERPIPE_CONFIG_SGIX 91
#endif

#ifndef GLX_BAD_HYPERPIPE_SGIX
#define GLX_BAD_HYPERPIPE_SGIX 92
#endif

#ifndef GLX_HYPERPIPE_DISPLAY_PIPE_SGIX
#define GLX_HYPERPIPE_DISPLAY_PIPE_SGIX 0x00000001
#endif

#ifndef GLX_HYPERPIPE_RENDER_PIPE_SGIX
#define GLX_HYPERPIPE_RENDER_PIPE_SGIX 0x00000002
#endif

#ifndef GLX_PIPE_RECT_SGIX
#define GLX_PIPE_RECT_SGIX 0x00000001
#endif

#ifndef GLX_PIPE_RECT_LIMITS_SGIX
#define GLX_PIPE_RECT_LIMITS_SGIX 0x00000002
#endif

#ifndef GLX_HYPERPIPE_STEREO_SGIX
#define GLX_HYPERPIPE_STEREO_SGIX 0x00000003
#endif

#ifndef GLX_HYPERPIPE_PIXEL_AVERAGE_SGIX
#define GLX_HYPERPIPE_PIXEL_AVERAGE_SGIX 0x00000004
#endif

#ifndef GLX_HYPERPIPE_ID_SGIX
#define GLX_HYPERPIPE_ID_SGIX 0x8030
#endif

#ifndef GLX_RGBA_UNSIGNED_FLOAT_TYPE_EXT
#define GLX_RGBA_UNSIGNED_FLOAT_TYPE_EXT 0x20B1
#endif

#ifndef GLX_RGBA_UNSIGNED_FLOAT_BIT_EXT
#define GLX_RGBA_UNSIGNED_FLOAT_BIT_EXT 0x00000008
#endif

#ifndef GLX_FRAMEBUFFER_SRGB_CAPABLE_EXT
#define GLX_FRAMEBUFFER_SRGB_CAPABLE_EXT 0x20B2
#endif

#ifndef GLX_TEXTURE_1D_BIT_EXT
#define GLX_TEXTURE_1D_BIT_EXT 0x00000001
#endif

#ifndef GLX_TEXTURE_2D_BIT_EXT
#define GLX_TEXTURE_2D_BIT_EXT 0x00000002
#endif

#ifndef GLX_TEXTURE_RECTANGLE_BIT_EXT
#define GLX_TEXTURE_RECTANGLE_BIT_EXT 0x00000004
#endif

#ifndef GLX_BIND_TO_TEXTURE_RGB_EXT
#define GLX_BIND_TO_TEXTURE_RGB_EXT 0x20D0
#endif

#ifndef GLX_BIND_TO_TEXTURE_RGBA_EXT
#define GLX_BIND_TO_TEXTURE_RGBA_EXT 0x20D1
#endif

#ifndef GLX_BIND_TO_MIPMAP_TEXTURE_EXT
#define GLX_BIND_TO_MIPMAP_TEXTURE_EXT 0x20D2
#endif

#ifndef GLX_BIND_TO_TEXTURE_TARGETS_EXT
#define GLX_BIND_TO_TEXTURE_TARGETS_EXT 0x20D3
#endif

#ifndef GLX_Y_INVERTED_EXT
#define GLX_Y_INVERTED_EXT 0x20D4
#endif

#ifndef GLX_TEXTURE_FORMAT_EXT
#define GLX_TEXTURE_FORMAT_EXT 0x20D5
#endif

#ifndef GLX_TEXTURE_TARGET_EXT
#define GLX_TEXTURE_TARGET_EXT 0x20D6
#endif

#ifndef GLX_MIPMAP_TEXTURE_EXT
#define GLX_MIPMAP_TEXTURE_EXT 0x20D7
#endif

#ifndef GLX_TEXTURE_FORMAT_NONE_EXT
#define GLX_TEXTURE_FORMAT_NONE_EXT 0x20D8
#endif

#ifndef GLX_TEXTURE_FORMAT_RGB_EXT
#define GLX_TEXTURE_FORMAT_RGB_EXT 0x20D9
#endif

#ifndef GLX_TEXTURE_FORMAT_RGBA_EXT
#define GLX_TEXTURE_FORMAT_RGBA_EXT 0x20DA
#endif

#ifndef GLX_TEXTURE_1D_EXT
#define GLX_TEXTURE_1D_EXT 0x20DB
#endif

#ifndef GLX_TEXTURE_2D_EXT
#define GLX_TEXTURE_2D_EXT 0x20DC
#endif

#ifndef GLX_TEXTURE_RECTANGLE_EXT
#define GLX_TEXTURE_RECTANGLE_EXT 0x20DD
#endif

#ifndef GLX_FRONT_LEFT_EXT
#define GLX_FRONT_LEFT_EXT 0x20DE
#endif

#ifndef GLX_FRONT_RIGHT_EXT
#define GLX_FRONT_RIGHT_EXT 0x20DF
#endif

#ifndef GLX_BACK_LEFT_EXT
#define GLX_BACK_LEFT_EXT 0x20E0
#endif

#ifndef GLX_BACK_RIGHT_EXT
#define GLX_BACK_RIGHT_EXT 0x20E1
#endif

#ifndef GLX_FRONT_EXT
#define GLX_FRONT_EXT GLX_FRONT_LEFT_EXT
#endif

#ifndef GLX_BACK_EXT
#define GLX_BACK_EXT GLX_BACK_LEFT_EXT
#endif

#ifndef GLX_AUX0_EXT
#define GLX_AUX0_EXT 0x20E2
#endif

#ifndef GLX_AUX1_EXT
#define GLX_AUX1_EXT 0x20E3
#endif

#ifndef GLX_AUX2_EXT
#define GLX_AUX2_EXT 0x20E4
#endif

#ifndef GLX_AUX3_EXT
#define GLX_AUX3_EXT 0x20E5
#endif

#ifndef GLX_AUX4_EXT
#define GLX_AUX4_EXT 0x20E6
#endif

#ifndef GLX_AUX5_EXT
#define GLX_AUX5_EXT 0x20E7
#endif

#ifndef GLX_AUX6_EXT
#define GLX_AUX6_EXT 0x20E8
#endif

#ifndef GLX_AUX7_EXT
#define GLX_AUX7_EXT 0x20E9
#endif

#ifndef GLX_AUX8_EXT
#define GLX_AUX8_EXT 0x20EA
#endif

#ifndef GLX_AUX9_EXT
#define GLX_AUX9_EXT 0x20EB
#endif

#ifndef GLX_NUM_VIDEO_SLOTS_NV
#define GLX_NUM_VIDEO_SLOTS_NV 0x20F0
#endif

#ifndef GLX_VIDEO_OUT_COLOR_NV
#define GLX_VIDEO_OUT_COLOR_NV 0x20C3
#endif

#ifndef GLX_VIDEO_OUT_ALPHA_NV
#define GLX_VIDEO_OUT_ALPHA_NV 0x20C4
#endif

#ifndef GLX_VIDEO_OUT_DEPTH_NV
#define GLX_VIDEO_OUT_DEPTH_NV 0x20C5
#endif

#ifndef GLX_VIDEO_OUT_COLOR_AND_ALPHA_NV
#define GLX_VIDEO_OUT_COLOR_AND_ALPHA_NV 0x20C6
#endif

#ifndef GLX_VIDEO_OUT_COLOR_AND_DEPTH_NV
#define GLX_VIDEO_OUT_COLOR_AND_DEPTH_NV 0x20C7
#endif

#ifndef GLX_VIDEO_OUT_FRAME_NV
#define GLX_VIDEO_OUT_FRAME_NV 0x20C8
#endif

#ifndef GLX_VIDEO_OUT_FIELD_1_NV
#define GLX_VIDEO_OUT_FIELD_1_NV 0x20C9
#endif

#ifndef GLX_VIDEO_OUT_FIELD_2_NV
#define GLX_VIDEO_OUT_FIELD_2_NV 0x20CA
#endif

#ifndef GLX_VIDEO_OUT_STACKED_FIELDS_1_2_NV
#define GLX_VIDEO_OUT_STACKED_FIELDS_1_2_NV 0x20CB
#endif

#ifndef GLX_VIDEO_OUT_STACKED_FIELDS_2_1_NV
#define GLX_VIDEO_OUT_STACKED_FIELDS_2_1_NV 0x20CC
#endif

#ifndef GLX_DEVICE_ID_NV
#define GLX_DEVICE_ID_NV 0x20CD
#endif

#ifndef GLX_UNIQUE_ID_NV
#define GLX_UNIQUE_ID_NV 0x20CE
#endif

#ifndef GLX_NUM_VIDEO_CAPTURE_SLOTS_NV
#define GLX_NUM_VIDEO_CAPTURE_SLOTS_NV 0x20CF
#endif

#ifndef GLX_SWAP_INTERVAL_EXT
#define GLX_SWAP_INTERVAL_EXT 0x20F1
#endif

#ifndef GLX_MAX_SWAP_INTERVAL_EXT
#define GLX_MAX_SWAP_INTERVAL_EXT 0x20F2
#endif

#ifndef GLX_BUFFER_SWAP_COMPLETE_INTEL_MASK
#define GLX_BUFFER_SWAP_COMPLETE_INTEL_MASK 0x04000000
#endif

#ifndef GLX_EXCHANGE_COMPLETE_INTEL
#define GLX_EXCHANGE_COMPLETE_INTEL 0x8180
#endif

#ifndef GLX_COPY_COMPLETE_INTEL
#define GLX_COPY_COMPLETE_INTEL 0x8181
#endif

#ifndef GLX_FLIP_COMPLETE_INTEL
#define GLX_FLIP_COMPLETE_INTEL 0x8182
#endif

#ifndef GLX_COVERAGE_SAMPLES_NV
#define GLX_COVERAGE_SAMPLES_NV 100001
#endif

#ifndef GLX_COLOR_SAMPLES_NV
#define GLX_COLOR_SAMPLES_NV 0x20B3
#endif

#ifndef GLX_GPU_VENDOR_AMD
#define GLX_GPU_VENDOR_AMD 0x1F00
#endif

#ifndef GLX_GPU_RENDERER_STRING_AMD
#define GLX_GPU_RENDERER_STRING_AMD 0x1F01
#endif

#ifndef GLX_GPU_OPENGL_VERSION_STRING_AMD
#define GLX_GPU_OPENGL_VERSION_STRING_AMD 0x1F02
#endif

#ifndef GLX_GPU_FASTEST_TARGET_GPUS_AMD
#define GLX_GPU_FASTEST_TARGET_GPUS_AMD 0x21A2
#endif

#ifndef GLX_GPU_RAM_AMD
#define GLX_GPU_RAM_AMD 0x21A3
#endif

#ifndef GLX_GPU_CLOCK_AMD
#define GLX_GPU_CLOCK_AMD 0x21A4
#endif

#ifndef GLX_GPU_NUM_PIPES_AMD
#define GLX_GPU_NUM_PIPES_AMD 0x21A5
#endif

#ifndef GLX_GPU_NUM_SIMD_AMD
#define GLX_GPU_NUM_SIMD_AMD 0x21A6
#endif

#ifndef GLX_GPU_NUM_RB_AMD
#define GLX_GPU_NUM_RB_AMD 0x21A7
#endif

#ifndef GLX_GPU_NUM_SPI_AMD
#define GLX_GPU_NUM_SPI_AMD 0x21A8
#endif

#ifndef GLX_CONTEXT_ES2_PROFILE_BIT_EXT
#define GLX_CONTEXT_ES2_PROFILE_BIT_EXT 0x00000004
#endif

#ifndef GLX_LATE_SWAPS_TEAR_EXT
#define GLX_LATE_SWAPS_TEAR_EXT 0x20F3
#endif

#ifndef GLX_BACK_BUFFER_AGE_EXT
#define GLX_BACK_BUFFER_AGE_EXT 0x20F4
#endif

#ifndef GLX_ARB_get_proc_address
typedef void (*__GLXextFuncPtr)(void);
#endif

#ifndef GLX_SGIX_video_source
typedef XID GLXVideoSourceSGIX;
#endif

#ifndef GLX_SGIX_fbconfig
typedef XID GLXFBConfigIDSGIX;
typedef struct __GLXFBConfigRec *GLXFBConfigSGIX;
#endif

#ifndef GLX_SGIX_pbuffer
typedef XID GLXPbufferSGIX;
typedef struct {
int type;
unsigned long serial;	  /* # of last request processed by server */
Bool send_event;		  /* true if this came for SendEvent request */
Display *display;		  /* display the event was read from */
GLXDrawable drawable;	  /* i.d. of Drawable */
int event_type;		  /* GLX_DAMAGED_SGIX or GLX_SAVED_SGIX */
int draw_type;		  /* GLX_WINDOW_SGIX or GLX_PBUFFER_SGIX */
unsigned int mask;	  /* mask indicating which buffers are affected*/
int x, y;
int width, height;
int count;		  /* if nonzero, at least this many more */
} GLXBufferClobberEventSGIX;
#endif

#ifndef GLX_NV_video_output
typedef unsigned int GLXVideoDeviceNV;
#endif

#ifndef GLX_NV_video_capture
typedef XID GLXVideoCaptureDeviceNV;
#endif

#ifndef GLEXT_64_TYPES_DEFINED
/* This code block is duplicated in glext.h, so must be protected */
#define GLEXT_64_TYPES_DEFINED
/* Define int32_t, int64_t, and uint64_t types for UST/MSC */
/* (as used in the GLX_OML_sync_control extension). */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#include <inttypes.h>
#elif defined(__sun__) || defined(__digital__)
#include <inttypes.h>
#if defined(__STDC__)
#if defined(__arch64__) || defined(_LP64)
typedef long int int64_t;
typedef unsigned long int uint64_t;
#else
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#endif /* __arch64__ */
#endif /* __STDC__ */
#elif defined( __VMS ) || defined(__sgi)
#include <inttypes.h>
#elif defined(__SCO__) || defined(__USLC__)
#include <stdint.h>
#elif defined(__UNIXOS2__) || defined(__SOL64__)
typedef long int int32_t;
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
#elif defined(_WIN32) && defined(__GNUC__)
#include <stdint.h>
#elif defined(_WIN32)
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <inttypes.h>     /* Fallback option */
#endif
#endif

typedef GLXFBConfig * (APIENTRY *glXGetFBConfigsFunc)(Display* dpy, int screen, int* nelements);
extern glXGetFBConfigsFunc _glXGetFBConfigs;
#define glXGetFBConfigs _glXGetFBConfigs
typedef GLXFBConfig * (APIENTRY *glXChooseFBConfigFunc)(Display* dpy, int screen, int* attrib_list, int* nelements);
extern glXChooseFBConfigFunc _glXChooseFBConfig;
#define glXChooseFBConfig _glXChooseFBConfig
typedef int (APIENTRY *glXGetFBConfigAttribFunc)(Display* dpy, GLXFBConfig config, int attribute, int* value);
extern glXGetFBConfigAttribFunc _glXGetFBConfigAttrib;
#define glXGetFBConfigAttrib _glXGetFBConfigAttrib
typedef XVisualInfo * (APIENTRY *glXGetVisualFromFBConfigFunc)(Display* dpy, GLXFBConfig config);
extern glXGetVisualFromFBConfigFunc _glXGetVisualFromFBConfig;
#define glXGetVisualFromFBConfig _glXGetVisualFromFBConfig
typedef GLXWindow (APIENTRY *glXCreateWindowFunc)(Display* dpy, GLXFBConfig config, Window win, int* attrib_list);
extern glXCreateWindowFunc _glXCreateWindow;
#define glXCreateWindow _glXCreateWindow
typedef void (APIENTRY *glXDestroyWindowFunc)(Display* dpy, GLXWindow win);
extern glXDestroyWindowFunc _glXDestroyWindow;
#define glXDestroyWindow VE_ASSERT(_glXDestroyWindow);_glXDestroyWindow
typedef GLXPixmap (APIENTRY *glXCreatePixmapFunc)(Display* dpy, GLXFBConfig config, Pixmap pixmap, int* attrib_list);
extern glXCreatePixmapFunc _glXCreatePixmap;
#define glXCreatePixmap _glXCreatePixmap
typedef void (APIENTRY *glXDestroyPixmapFunc)(Display* dpy, GLXPixmap pixmap);
extern glXDestroyPixmapFunc _glXDestroyPixmap;
#define glXDestroyPixmap VE_ASSERT(_glXDestroyPixmap);_glXDestroyPixmap
typedef GLXPbuffer (APIENTRY *glXCreatePbufferFunc)(Display* dpy, GLXFBConfig config, int* attrib_list);
extern glXCreatePbufferFunc _glXCreatePbuffer;
#define glXCreatePbuffer _glXCreatePbuffer
typedef void (APIENTRY *glXDestroyPbufferFunc)(Display* dpy, GLXPbuffer pbuf);
extern glXDestroyPbufferFunc _glXDestroyPbuffer;
#define glXDestroyPbuffer VE_ASSERT(_glXDestroyPbuffer);_glXDestroyPbuffer
typedef void (APIENTRY *glXQueryDrawableFunc)(Display* dpy, GLXDrawable draw, int attribute, unsigned int* value);
extern glXQueryDrawableFunc _glXQueryDrawable;
#define glXQueryDrawable VE_ASSERT(_glXQueryDrawable);_glXQueryDrawable
typedef GLXContext (APIENTRY *glXCreateNewContextFunc)(Display* dpy, GLXFBConfig config, int render_type, GLXContext share_list, Bool direct);
extern glXCreateNewContextFunc _glXCreateNewContext;
#define glXCreateNewContext _glXCreateNewContext
typedef Bool (APIENTRY *glXMakeContextCurrentFunc)(Display* dpy, GLXDrawable draw, GLXDrawable read, GLXContext ctx);
extern glXMakeContextCurrentFunc _glXMakeContextCurrent;
#define glXMakeContextCurrent _glXMakeContextCurrent
typedef GLXDrawable (APIENTRY *glXGetCurrentReadDrawableFunc)();
extern glXGetCurrentReadDrawableFunc _glXGetCurrentReadDrawable;
#define glXGetCurrentReadDrawable _glXGetCurrentReadDrawable
typedef Display * (APIENTRY *glXGetCurrentDisplayFunc)();
extern glXGetCurrentDisplayFunc _glXGetCurrentDisplay;
#define glXGetCurrentDisplay _glXGetCurrentDisplay
typedef int (APIENTRY *glXQueryContextFunc)(Display* dpy, GLXContext ctx, int attribute, int* value);
extern glXQueryContextFunc _glXQueryContext;
#define glXQueryContext _glXQueryContext
typedef void (APIENTRY *glXSelectEventFunc)(Display* dpy, GLXDrawable draw, unsigned long event_mask);
extern glXSelectEventFunc _glXSelectEvent;
#define glXSelectEvent VE_ASSERT(_glXSelectEvent);_glXSelectEvent
typedef void (APIENTRY *glXGetSelectedEventFunc)(Display* dpy, GLXDrawable draw, unsigned long* event_mask);
extern glXGetSelectedEventFunc _glXGetSelectedEvent;
#define glXGetSelectedEvent VE_ASSERT(_glXGetSelectedEvent);_glXGetSelectedEvent
typedef __GLXextFuncPtr (APIENTRY *glXGetProcAddressFunc)(GLubyte* procName);
extern glXGetProcAddressFunc _glXGetProcAddress;
#define glXGetProcAddress _glXGetProcAddress
typedef GLXContext (APIENTRY *glXCreateContextAttribsARBFunc)(Display* dpy, GLXFBConfig config, GLXContext share_context, Bool direct, int* attrib_list);
extern glXCreateContextAttribsARBFunc _glXCreateContextAttribsARB;
#define glXCreateContextAttribsARB _glXCreateContextAttribsARB
typedef int (APIENTRY *glXSwapIntervalSGIFunc)(int interval);
extern glXSwapIntervalSGIFunc _glXSwapIntervalSGI;
#define glXSwapIntervalSGI _glXSwapIntervalSGI
typedef int (APIENTRY *glXGetVideoSyncSGIFunc)(unsigned int* count);
extern glXGetVideoSyncSGIFunc _glXGetVideoSyncSGI;
#define glXGetVideoSyncSGI _glXGetVideoSyncSGI
typedef int (APIENTRY *glXWaitVideoSyncSGIFunc)(int divisor, int remainder, unsigned int* count);
extern glXWaitVideoSyncSGIFunc _glXWaitVideoSyncSGI;
#define glXWaitVideoSyncSGI _glXWaitVideoSyncSGI
typedef Bool (APIENTRY *glXMakeCurrentReadSGIFunc)(Display* dpy, GLXDrawable draw, GLXDrawable read, GLXContext ctx);
extern glXMakeCurrentReadSGIFunc _glXMakeCurrentReadSGI;
#define glXMakeCurrentReadSGI _glXMakeCurrentReadSGI
typedef GLXDrawable (APIENTRY *glXGetCurrentReadDrawableSGIFunc)();
extern glXGetCurrentReadDrawableSGIFunc _glXGetCurrentReadDrawableSGI;
#define glXGetCurrentReadDrawableSGI _glXGetCurrentReadDrawableSGI
#ifdef _VL_H
typedef GLXVideoSourceSGIX (APIENTRY *glXCreateGLXVideoSourceSGIXFunc)(Display* display, int screen, VLServer server, VLPath path, int nodeClass, VLNode drainNode);
extern glXCreateGLXVideoSourceSGIXFunc _glXCreateGLXVideoSourceSGIX;
#define glXCreateGLXVideoSourceSGIX _glXCreateGLXVideoSourceSGIX
typedef void (APIENTRY *glXDestroyGLXVideoSourceSGIXFunc)(Display* dpy, GLXVideoSourceSGIX glxvideosource);
extern glXDestroyGLXVideoSourceSGIXFunc _glXDestroyGLXVideoSourceSGIX;
#define glXDestroyGLXVideoSourceSGIX VE_ASSERT(_glXDestroyGLXVideoSourceSGIX);_glXDestroyGLXVideoSourceSGIX
#endif /* _VL_H */
typedef Display * (APIENTRY *glXGetCurrentDisplayEXTFunc)();
extern glXGetCurrentDisplayEXTFunc _glXGetCurrentDisplayEXT;
#define glXGetCurrentDisplayEXT _glXGetCurrentDisplayEXT
typedef int (APIENTRY *glXQueryContextInfoEXTFunc)(Display* dpy, GLXContext context, int attribute, int* value);
extern glXQueryContextInfoEXTFunc _glXQueryContextInfoEXT;
#define glXQueryContextInfoEXT _glXQueryContextInfoEXT
typedef GLXContextID (APIENTRY *glXGetContextIDEXTFunc)(const GLXContext context);
extern glXGetContextIDEXTFunc _glXGetContextIDEXT;
#define glXGetContextIDEXT _glXGetContextIDEXT
typedef GLXContext (APIENTRY *glXImportContextEXTFunc)(Display* dpy, GLXContextID contextID);
extern glXImportContextEXTFunc _glXImportContextEXT;
#define glXImportContextEXT _glXImportContextEXT
typedef void (APIENTRY *glXFreeContextEXTFunc)(Display* dpy, GLXContext context);
extern glXFreeContextEXTFunc _glXFreeContextEXT;
#define glXFreeContextEXT VE_ASSERT(_glXFreeContextEXT);_glXFreeContextEXT
typedef int (APIENTRY *glXGetFBConfigAttribSGIXFunc)(Display* dpy, GLXFBConfigSGIX config, int attribute, int* value);
extern glXGetFBConfigAttribSGIXFunc _glXGetFBConfigAttribSGIX;
#define glXGetFBConfigAttribSGIX _glXGetFBConfigAttribSGIX
typedef GLXFBConfigSGIX * (APIENTRY *glXChooseFBConfigSGIXFunc)(Display* dpy, int screen, int* attrib_list, int* nelements);
extern glXChooseFBConfigSGIXFunc _glXChooseFBConfigSGIX;
#define glXChooseFBConfigSGIX _glXChooseFBConfigSGIX
typedef GLXPixmap (APIENTRY *glXCreateGLXPixmapWithConfigSGIXFunc)(Display* dpy, GLXFBConfigSGIX config, Pixmap pixmap);
extern glXCreateGLXPixmapWithConfigSGIXFunc _glXCreateGLXPixmapWithConfigSGIX;
#define glXCreateGLXPixmapWithConfigSGIX _glXCreateGLXPixmapWithConfigSGIX
typedef GLXContext (APIENTRY *glXCreateContextWithConfigSGIXFunc)(Display* dpy, GLXFBConfigSGIX config, int render_type, GLXContext share_list, Bool direct);
extern glXCreateContextWithConfigSGIXFunc _glXCreateContextWithConfigSGIX;
#define glXCreateContextWithConfigSGIX _glXCreateContextWithConfigSGIX
typedef XVisualInfo * (APIENTRY *glXGetVisualFromFBConfigSGIXFunc)(Display* dpy, GLXFBConfigSGIX config);
extern glXGetVisualFromFBConfigSGIXFunc _glXGetVisualFromFBConfigSGIX;
#define glXGetVisualFromFBConfigSGIX _glXGetVisualFromFBConfigSGIX
typedef GLXFBConfigSGIX (APIENTRY *glXGetFBConfigFromVisualSGIXFunc)(Display* dpy, XVisualInfo* vis);
extern glXGetFBConfigFromVisualSGIXFunc _glXGetFBConfigFromVisualSGIX;
#define glXGetFBConfigFromVisualSGIX _glXGetFBConfigFromVisualSGIX
typedef GLXPbufferSGIX (APIENTRY *glXCreateGLXPbufferSGIXFunc)(Display* dpy, GLXFBConfigSGIX config, unsigned int width, unsigned int height, int* attrib_list);
extern glXCreateGLXPbufferSGIXFunc _glXCreateGLXPbufferSGIX;
#define glXCreateGLXPbufferSGIX _glXCreateGLXPbufferSGIX
typedef void (APIENTRY *glXDestroyGLXPbufferSGIXFunc)(Display* dpy, GLXPbufferSGIX pbuf);
extern glXDestroyGLXPbufferSGIXFunc _glXDestroyGLXPbufferSGIX;
#define glXDestroyGLXPbufferSGIX VE_ASSERT(_glXDestroyGLXPbufferSGIX);_glXDestroyGLXPbufferSGIX
typedef int (APIENTRY *glXQueryGLXPbufferSGIXFunc)(Display* dpy, GLXPbufferSGIX pbuf, int attribute, unsigned int* value);
extern glXQueryGLXPbufferSGIXFunc _glXQueryGLXPbufferSGIX;
#define glXQueryGLXPbufferSGIX _glXQueryGLXPbufferSGIX
typedef void (APIENTRY *glXSelectEventSGIXFunc)(Display* dpy, GLXDrawable drawable, unsigned long mask);
extern glXSelectEventSGIXFunc _glXSelectEventSGIX;
#define glXSelectEventSGIX VE_ASSERT(_glXSelectEventSGIX);_glXSelectEventSGIX
typedef void (APIENTRY *glXGetSelectedEventSGIXFunc)(Display* dpy, GLXDrawable drawable, unsigned long* mask);
extern glXGetSelectedEventSGIXFunc _glXGetSelectedEventSGIX;
#define glXGetSelectedEventSGIX VE_ASSERT(_glXGetSelectedEventSGIX);_glXGetSelectedEventSGIX
typedef void (APIENTRY *glXCushionSGIFunc)(Display* dpy, Window window, float cushion);
extern glXCushionSGIFunc _glXCushionSGI;
#define glXCushionSGI VE_ASSERT(_glXCushionSGI);_glXCushionSGI
typedef int (APIENTRY *glXBindChannelToWindowSGIXFunc)(Display* display, int screen, int channel, Window window);
extern glXBindChannelToWindowSGIXFunc _glXBindChannelToWindowSGIX;
#define glXBindChannelToWindowSGIX _glXBindChannelToWindowSGIX
typedef int (APIENTRY *glXChannelRectSGIXFunc)(Display* display, int screen, int channel, int x, int y, int w, int h);
extern glXChannelRectSGIXFunc _glXChannelRectSGIX;
#define glXChannelRectSGIX _glXChannelRectSGIX
typedef int (APIENTRY *glXQueryChannelRectSGIXFunc)(Display* display, int screen, int channel, int* dx, int* dy, int* dw, int* dh);
extern glXQueryChannelRectSGIXFunc _glXQueryChannelRectSGIX;
#define glXQueryChannelRectSGIX _glXQueryChannelRectSGIX
typedef int (APIENTRY *glXQueryChannelDeltasSGIXFunc)(Display* display, int screen, int channel, int* x, int* y, int* w, int* h);
extern glXQueryChannelDeltasSGIXFunc _glXQueryChannelDeltasSGIX;
#define glXQueryChannelDeltasSGIX _glXQueryChannelDeltasSGIX
typedef int (APIENTRY *glXChannelRectSyncSGIXFunc)(Display* display, int screen, int channel, GLenum synctype);
extern glXChannelRectSyncSGIXFunc _glXChannelRectSyncSGIX;
#define glXChannelRectSyncSGIX _glXChannelRectSyncSGIX
#ifdef _DM_BUFFER_H_
typedef Bool (APIENTRY *glXAssociateDMPbufferSGIXFunc)(Display* dpy, GLXPbufferSGIX pbuffer, DMparams* params, DMbuffer dmbuffer);
extern glXAssociateDMPbufferSGIXFunc _glXAssociateDMPbufferSGIX;
#define glXAssociateDMPbufferSGIX _glXAssociateDMPbufferSGIX
#endif /* _DM_BUFFER_H_ */
typedef void (APIENTRY *glXJoinSwapGroupSGIXFunc)(Display* dpy, GLXDrawable drawable, GLXDrawable member);
extern glXJoinSwapGroupSGIXFunc _glXJoinSwapGroupSGIX;
#define glXJoinSwapGroupSGIX VE_ASSERT(_glXJoinSwapGroupSGIX);_glXJoinSwapGroupSGIX
typedef void (APIENTRY *glXBindSwapBarrierSGIXFunc)(Display* dpy, GLXDrawable drawable, int barrier);
extern glXBindSwapBarrierSGIXFunc _glXBindSwapBarrierSGIX;
#define glXBindSwapBarrierSGIX VE_ASSERT(_glXBindSwapBarrierSGIX);_glXBindSwapBarrierSGIX
typedef Bool (APIENTRY *glXQueryMaxSwapBarriersSGIXFunc)(Display* dpy, int screen, int* max);
extern glXQueryMaxSwapBarriersSGIXFunc _glXQueryMaxSwapBarriersSGIX;
#define glXQueryMaxSwapBarriersSGIX _glXQueryMaxSwapBarriersSGIX
typedef Status (APIENTRY *glXGetTransparentIndexSUNFunc)(Display* dpy, Window overlay, Window underlay, long* pTransparentIndex);
extern glXGetTransparentIndexSUNFunc _glXGetTransparentIndexSUN;
#define glXGetTransparentIndexSUN _glXGetTransparentIndexSUN
typedef void (APIENTRY *glXCopySubBufferMESAFunc)(Display* dpy, GLXDrawable drawable, int x, int y, int width, int height);
extern glXCopySubBufferMESAFunc _glXCopySubBufferMESA;
#define glXCopySubBufferMESA VE_ASSERT(_glXCopySubBufferMESA);_glXCopySubBufferMESA
typedef GLXPixmap (APIENTRY *glXCreateGLXPixmapMESAFunc)(Display* dpy, XVisualInfo* visual, Pixmap pixmap, Colormap cmap);
extern glXCreateGLXPixmapMESAFunc _glXCreateGLXPixmapMESA;
#define glXCreateGLXPixmapMESA _glXCreateGLXPixmapMESA
typedef Bool (APIENTRY *glXReleaseBuffersMESAFunc)(Display* dpy, GLXDrawable drawable);
extern glXReleaseBuffersMESAFunc _glXReleaseBuffersMESA;
#define glXReleaseBuffersMESA _glXReleaseBuffersMESA
typedef Bool (APIENTRY *glXSet3DfxModeMESAFunc)(int mode);
extern glXSet3DfxModeMESAFunc _glXSet3DfxModeMESA;
#define glXSet3DfxModeMESA _glXSet3DfxModeMESA
typedef Bool (APIENTRY *glXGetSyncValuesOMLFunc)(Display* dpy, GLXDrawable drawable, int64_t* ust, int64_t* msc, int64_t* sbc);
extern glXGetSyncValuesOMLFunc _glXGetSyncValuesOML;
#define glXGetSyncValuesOML _glXGetSyncValuesOML
typedef Bool (APIENTRY *glXGetMscRateOMLFunc)(Display* dpy, GLXDrawable drawable, int32_t* numerator, int32_t* denominator);
extern glXGetMscRateOMLFunc _glXGetMscRateOML;
#define glXGetMscRateOML _glXGetMscRateOML
typedef int64_t (APIENTRY *glXSwapBuffersMscOMLFunc)(Display* dpy, GLXDrawable drawable, int64_t target_msc, int64_t divisor, int64_t remainder);
extern glXSwapBuffersMscOMLFunc _glXSwapBuffersMscOML;
#define glXSwapBuffersMscOML _glXSwapBuffersMscOML
typedef Bool (APIENTRY *glXWaitForMscOMLFunc)(Display* dpy, GLXDrawable drawable, int64_t target_msc, int64_t divisor, int64_t remainder, int64_t* ust, int64_t* msc, int64_t* sbc);
extern glXWaitForMscOMLFunc _glXWaitForMscOML;
#define glXWaitForMscOML _glXWaitForMscOML
typedef Bool (APIENTRY *glXWaitForSbcOMLFunc)(Display* dpy, GLXDrawable drawable, int64_t target_sbc, int64_t* ust, int64_t* msc, int64_t* sbc);
extern glXWaitForSbcOMLFunc _glXWaitForSbcOML;
#define glXWaitForSbcOML _glXWaitForSbcOML

typedef struct {
char    pipeName[GLX_HYPERPIPE_PIPE_NAME_LENGTH_SGIX];
int     networkId;
} GLXHyperpipeNetworkSGIX;

typedef struct {
char    pipeName[GLX_HYPERPIPE_PIPE_NAME_LENGTH_SGIX];
int     channel;
unsigned int
participationType;
int     timeSlice;
} GLXHyperpipeConfigSGIX;

typedef struct {
char pipeName[GLX_HYPERPIPE_PIPE_NAME_LENGTH_SGIX];
int srcXOrigin, srcYOrigin, srcWidth, srcHeight;
int destXOrigin, destYOrigin, destWidth, destHeight;
} GLXPipeRect;

typedef struct {
char pipeName[GLX_HYPERPIPE_PIPE_NAME_LENGTH_SGIX];
int XOrigin, YOrigin, maxHeight, maxWidth;
} GLXPipeRectLimits;

typedef GLXHyperpipeNetworkSGIX * (APIENTRY *glXQueryHyperpipeNetworkSGIXFunc)(Display* dpy, int* npipes);
extern glXQueryHyperpipeNetworkSGIXFunc _glXQueryHyperpipeNetworkSGIX;
#define glXQueryHyperpipeNetworkSGIX _glXQueryHyperpipeNetworkSGIX
typedef int (APIENTRY *glXHyperpipeConfigSGIXFunc)(Display* dpy, int networkId, int npipes, GLXHyperpipeConfigSGIX* cfg, int* hpId);
extern glXHyperpipeConfigSGIXFunc _glXHyperpipeConfigSGIX;
#define glXHyperpipeConfigSGIX _glXHyperpipeConfigSGIX
typedef GLXHyperpipeConfigSGIX * (APIENTRY *glXQueryHyperpipeConfigSGIXFunc)(Display* dpy, int hpId, int* npipes);
extern glXQueryHyperpipeConfigSGIXFunc _glXQueryHyperpipeConfigSGIX;
#define glXQueryHyperpipeConfigSGIX _glXQueryHyperpipeConfigSGIX
typedef int (APIENTRY *glXDestroyHyperpipeConfigSGIXFunc)(Display* dpy, int hpId);
extern glXDestroyHyperpipeConfigSGIXFunc _glXDestroyHyperpipeConfigSGIX;
#define glXDestroyHyperpipeConfigSGIX _glXDestroyHyperpipeConfigSGIX
typedef int (APIENTRY *glXBindHyperpipeSGIXFunc)(Display* dpy, int hpId);
extern glXBindHyperpipeSGIXFunc _glXBindHyperpipeSGIX;
#define glXBindHyperpipeSGIX _glXBindHyperpipeSGIX
typedef int (APIENTRY *glXQueryHyperpipeBestAttribSGIXFunc)(Display* dpy, int timeSlice, int attrib, int size, void* attribList, void* returnAttribList);
extern glXQueryHyperpipeBestAttribSGIXFunc _glXQueryHyperpipeBestAttribSGIX;
#define glXQueryHyperpipeBestAttribSGIX _glXQueryHyperpipeBestAttribSGIX
typedef int (APIENTRY *glXHyperpipeAttribSGIXFunc)(Display* dpy, int timeSlice, int attrib, int size, void* attribList);
extern glXHyperpipeAttribSGIXFunc _glXHyperpipeAttribSGIX;
#define glXHyperpipeAttribSGIX _glXHyperpipeAttribSGIX
typedef int (APIENTRY *glXQueryHyperpipeAttribSGIXFunc)(Display* dpy, int timeSlice, int attrib, int size, void* returnAttribList);
extern glXQueryHyperpipeAttribSGIXFunc _glXQueryHyperpipeAttribSGIX;
#define glXQueryHyperpipeAttribSGIX _glXQueryHyperpipeAttribSGIX
typedef unsigned int (APIENTRY *glXGetAGPOffsetMESAFunc)(void* pointer);
extern glXGetAGPOffsetMESAFunc _glXGetAGPOffsetMESA;
#define glXGetAGPOffsetMESA _glXGetAGPOffsetMESA
typedef void (APIENTRY *glXBindTexImageEXTFunc)(Display* dpy, GLXDrawable drawable, int buffer, int* attrib_list);
extern glXBindTexImageEXTFunc _glXBindTexImageEXT;
#define glXBindTexImageEXT VE_ASSERT(_glXBindTexImageEXT);_glXBindTexImageEXT
typedef void (APIENTRY *glXReleaseTexImageEXTFunc)(Display* dpy, GLXDrawable drawable, int buffer);
extern glXReleaseTexImageEXTFunc _glXReleaseTexImageEXT;
#define glXReleaseTexImageEXT VE_ASSERT(_glXReleaseTexImageEXT);_glXReleaseTexImageEXT
typedef unsigned int * (APIENTRY *glXEnumerateVideoDevicesNVFunc)(Display* dpy, int screen, int* nelements);
extern glXEnumerateVideoDevicesNVFunc _glXEnumerateVideoDevicesNV;
#define glXEnumerateVideoDevicesNV _glXEnumerateVideoDevicesNV
typedef int (APIENTRY *glXBindVideoDeviceNVFunc)(Display* dpy, unsigned int video_slot, unsigned int video_device, int* attrib_list);
extern glXBindVideoDeviceNVFunc _glXBindVideoDeviceNV;
#define glXBindVideoDeviceNV _glXBindVideoDeviceNV
typedef int (APIENTRY *glXGetVideoDeviceNVFunc)(Display* dpy, int screen, int numVideoDevices, GLXVideoDeviceNV* pVideoDevice);
extern glXGetVideoDeviceNVFunc _glXGetVideoDeviceNV;
#define glXGetVideoDeviceNV _glXGetVideoDeviceNV
typedef int (APIENTRY *glXReleaseVideoDeviceNVFunc)(Display* dpy, int screen, GLXVideoDeviceNV VideoDevice);
extern glXReleaseVideoDeviceNVFunc _glXReleaseVideoDeviceNV;
#define glXReleaseVideoDeviceNV _glXReleaseVideoDeviceNV
typedef int (APIENTRY *glXBindVideoImageNVFunc)(Display* dpy, GLXVideoDeviceNV VideoDevice, GLXPbuffer pbuf, int iVideoBuffer);
extern glXBindVideoImageNVFunc _glXBindVideoImageNV;
#define glXBindVideoImageNV _glXBindVideoImageNV
typedef int (APIENTRY *glXReleaseVideoImageNVFunc)(Display* dpy, GLXPbuffer pbuf);
extern glXReleaseVideoImageNVFunc _glXReleaseVideoImageNV;
#define glXReleaseVideoImageNV _glXReleaseVideoImageNV
typedef int (APIENTRY *glXSendPbufferToVideoNVFunc)(Display* dpy, GLXPbuffer pbuf, int iBufferType, unsigned long* pulCounterPbuffer, GLboolean bBlock);
extern glXSendPbufferToVideoNVFunc _glXSendPbufferToVideoNV;
#define glXSendPbufferToVideoNV _glXSendPbufferToVideoNV
typedef int (APIENTRY *glXGetVideoInfoNVFunc)(Display* dpy, int screen, GLXVideoDeviceNV VideoDevice, unsigned long* pulCounterOutputPbuffer, unsigned long* pulCounterOutputVideo);
extern glXGetVideoInfoNVFunc _glXGetVideoInfoNV;
#define glXGetVideoInfoNV _glXGetVideoInfoNV
typedef Bool (APIENTRY *glXJoinSwapGroupNVFunc)(Display* dpy, GLXDrawable drawable, GLuint group);
extern glXJoinSwapGroupNVFunc _glXJoinSwapGroupNV;
#define glXJoinSwapGroupNV _glXJoinSwapGroupNV
typedef Bool (APIENTRY *glXBindSwapBarrierNVFunc)(Display* dpy, GLuint group, GLuint barrier);
extern glXBindSwapBarrierNVFunc _glXBindSwapBarrierNV;
#define glXBindSwapBarrierNV _glXBindSwapBarrierNV
typedef Bool (APIENTRY *glXQuerySwapGroupNVFunc)(Display* dpy, GLXDrawable drawable, GLuint* group, GLuint* barrier);
extern glXQuerySwapGroupNVFunc _glXQuerySwapGroupNV;
#define glXQuerySwapGroupNV _glXQuerySwapGroupNV
typedef Bool (APIENTRY *glXQueryMaxSwapGroupsNVFunc)(Display* dpy, int screen, GLuint* maxGroups, GLuint* maxBarriers);
extern glXQueryMaxSwapGroupsNVFunc _glXQueryMaxSwapGroupsNV;
#define glXQueryMaxSwapGroupsNV _glXQueryMaxSwapGroupsNV
typedef Bool (APIENTRY *glXQueryFrameCountNVFunc)(Display* dpy, int screen, GLuint* count);
extern glXQueryFrameCountNVFunc _glXQueryFrameCountNV;
#define glXQueryFrameCountNV _glXQueryFrameCountNV
typedef Bool (APIENTRY *glXResetFrameCountNVFunc)(Display* dpy, int screen);
extern glXResetFrameCountNVFunc _glXResetFrameCountNV;
#define glXResetFrameCountNV _glXResetFrameCountNV
typedef int (APIENTRY *glXBindVideoCaptureDeviceNVFunc)(Display* dpy, unsigned int video_capture_slot, GLXVideoCaptureDeviceNV device);
extern glXBindVideoCaptureDeviceNVFunc _glXBindVideoCaptureDeviceNV;
#define glXBindVideoCaptureDeviceNV _glXBindVideoCaptureDeviceNV
typedef GLXVideoCaptureDeviceNV * (APIENTRY *glXEnumerateVideoCaptureDevicesNVFunc)(Display* dpy, int screen, int* nelements);
extern glXEnumerateVideoCaptureDevicesNVFunc _glXEnumerateVideoCaptureDevicesNV;
#define glXEnumerateVideoCaptureDevicesNV _glXEnumerateVideoCaptureDevicesNV
typedef void (APIENTRY *glXLockVideoCaptureDeviceNVFunc)(Display* dpy, GLXVideoCaptureDeviceNV device);
extern glXLockVideoCaptureDeviceNVFunc _glXLockVideoCaptureDeviceNV;
#define glXLockVideoCaptureDeviceNV VE_ASSERT(_glXLockVideoCaptureDeviceNV);_glXLockVideoCaptureDeviceNV
typedef int (APIENTRY *glXQueryVideoCaptureDeviceNVFunc)(Display* dpy, GLXVideoCaptureDeviceNV device, int attribute, int* value);
extern glXQueryVideoCaptureDeviceNVFunc _glXQueryVideoCaptureDeviceNV;
#define glXQueryVideoCaptureDeviceNV _glXQueryVideoCaptureDeviceNV
typedef void (APIENTRY *glXReleaseVideoCaptureDeviceNVFunc)(Display* dpy, GLXVideoCaptureDeviceNV device);
extern glXReleaseVideoCaptureDeviceNVFunc _glXReleaseVideoCaptureDeviceNV;
#define glXReleaseVideoCaptureDeviceNV VE_ASSERT(_glXReleaseVideoCaptureDeviceNV);_glXReleaseVideoCaptureDeviceNV
typedef void (APIENTRY *glXSwapIntervalEXTFunc)(Display* dpy, GLXDrawable drawable, int interval);
extern glXSwapIntervalEXTFunc _glXSwapIntervalEXT;
#define glXSwapIntervalEXT VE_ASSERT(_glXSwapIntervalEXT);_glXSwapIntervalEXT
typedef void (APIENTRY *glXCopyImageSubDataNVFunc)(Display* dpy, GLXContext srcCtx, GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLXContext dstCtx, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei width, GLsizei height, GLsizei depth);
extern glXCopyImageSubDataNVFunc _glXCopyImageSubDataNV;
#define glXCopyImageSubDataNV VE_ASSERT(_glXCopyImageSubDataNV);_glXCopyImageSubDataNV
typedef void (APIENTRY *glXRenderFunc)();
extern glXRenderFunc _glXRender;
#define glXRender VE_ASSERT(_glXRender);_glXRender
typedef void (APIENTRY *glXRenderLargeFunc)();
extern glXRenderLargeFunc _glXRenderLarge;
#define glXRenderLarge VE_ASSERT(_glXRenderLarge);_glXRenderLarge
typedef void (APIENTRY *glXDestroyContextFunc)(GLint context);
extern glXDestroyContextFunc _glXDestroyContext;
#define glXDestroyContext VE_ASSERT(_glXDestroyContext);_glXDestroyContext
typedef void (APIENTRY *glXIsDirectFunc)(GLint dpy, GLint context);
extern glXIsDirectFunc _glXIsDirect;
#define glXIsDirect VE_ASSERT(_glXIsDirect);_glXIsDirect
typedef void (APIENTRY *glXQueryVersionFunc)(GLint* major, GLint* minor);
extern glXQueryVersionFunc _glXQueryVersion;
#define glXQueryVersion VE_ASSERT(_glXQueryVersion);_glXQueryVersion
typedef void (APIENTRY *glXWaitGLFunc)(GLint context);
extern glXWaitGLFunc _glXWaitGL;
#define glXWaitGL VE_ASSERT(_glXWaitGL);_glXWaitGL
typedef void (APIENTRY *glXWaitXFunc)();
extern glXWaitXFunc _glXWaitX;
#define glXWaitX VE_ASSERT(_glXWaitX);_glXWaitX
typedef void (APIENTRY *glXCopyContextFunc)(GLint source, GLint dest, GLint mask);
extern glXCopyContextFunc _glXCopyContext;
#define glXCopyContext VE_ASSERT(_glXCopyContext);_glXCopyContext
typedef void (APIENTRY *glXUseXFontFunc)(GLint font, GLint first, GLint count, GLint list_base);
extern glXUseXFontFunc _glXUseXFont;
#define glXUseXFont VE_ASSERT(_glXUseXFont);_glXUseXFont
typedef void (APIENTRY *glXCreateGLXPixmapFunc)(GLint visual, GLint pixmap, GLint glxpixmap);
extern glXCreateGLXPixmapFunc _glXCreateGLXPixmap;
#define glXCreateGLXPixmap VE_ASSERT(_glXCreateGLXPixmap);_glXCreateGLXPixmap
typedef void (APIENTRY *glXGetVisualConfigsFunc)();
extern glXGetVisualConfigsFunc _glXGetVisualConfigs;
#define glXGetVisualConfigs VE_ASSERT(_glXGetVisualConfigs);_glXGetVisualConfigs
typedef void (APIENTRY *glXDestroyGLXPixmapFunc)(GLint pixmap);
extern glXDestroyGLXPixmapFunc _glXDestroyGLXPixmap;
#define glXDestroyGLXPixmap VE_ASSERT(_glXDestroyGLXPixmap);_glXDestroyGLXPixmap
typedef void (APIENTRY *glXVendorPrivateFunc)();
extern glXVendorPrivateFunc _glXVendorPrivate;
#define glXVendorPrivate VE_ASSERT(_glXVendorPrivate);_glXVendorPrivate
typedef void (APIENTRY *glXVendorPrivateWithReplyFunc)();
extern glXVendorPrivateWithReplyFunc _glXVendorPrivateWithReply;
#define glXVendorPrivateWithReply VE_ASSERT(_glXVendorPrivateWithReply);_glXVendorPrivateWithReply
typedef void (APIENTRY *glXQueryExtensionsStringFunc)(GLint screen);
extern glXQueryExtensionsStringFunc _glXQueryExtensionsString;
#define glXQueryExtensionsString VE_ASSERT(_glXQueryExtensionsString);_glXQueryExtensionsString
typedef void (APIENTRY *glXQueryServerStringFunc)(GLint screen, GLint name);
extern glXQueryServerStringFunc _glXQueryServerString;
#define glXQueryServerString VE_ASSERT(_glXQueryServerString);_glXQueryServerString
typedef void (APIENTRY *glXClientInfoFunc)();
extern glXClientInfoFunc _glXClientInfo;
#define glXClientInfo VE_ASSERT(_glXClientInfo);_glXClientInfo
typedef void (APIENTRY *glXGetDrawableAttributesFunc)(GLint drawable);
extern glXGetDrawableAttributesFunc _glXGetDrawableAttributes;
#define glXGetDrawableAttributes VE_ASSERT(_glXGetDrawableAttributes);_glXGetDrawableAttributes
typedef void (APIENTRY *glXChangeDrawableAttributesFunc)(GLint drawable);
extern glXChangeDrawableAttributesFunc _glXChangeDrawableAttributes;
#define glXChangeDrawableAttributes VE_ASSERT(_glXChangeDrawableAttributes);_glXChangeDrawableAttributes
typedef void (APIENTRY *glXGetFBConfigsSGIXFunc)();
extern glXGetFBConfigsSGIXFunc _glXGetFBConfigsSGIX;
#define glXGetFBConfigsSGIX VE_ASSERT(_glXGetFBConfigsSGIX);_glXGetFBConfigsSGIX
typedef void (APIENTRY *glXChangeDrawableAttributesSGIXFunc)(GLint drawable);
extern glXChangeDrawableAttributesSGIXFunc _glXChangeDrawableAttributesSGIX;
#define glXChangeDrawableAttributesSGIX VE_ASSERT(_glXChangeDrawableAttributesSGIX);_glXChangeDrawableAttributesSGIX
typedef void (APIENTRY *glXGetDrawableAttributesSGIXFunc)(GLint drawable);
extern glXGetDrawableAttributesSGIXFunc _glXGetDrawableAttributesSGIX;
#define glXGetDrawableAttributesSGIX VE_ASSERT(_glXGetDrawableAttributesSGIX);_glXGetDrawableAttributesSGIX

void glXFuncload();

void glXFuncUnload();

}

#endif
