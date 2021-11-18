#pragma once

#include <Aliases.h>
#include <memory>
#include "../Components.h"
#include "../DebugTools.h"

namespace PetrolEngine{

    enum class DeviceConstant {
        None,

        // Compute
        MAX_COMPUTE_SHADER_STORAGE_BLOCKS,
        MAX_COMPUTE_TEXTURE_IMAGE_UNITS,
        MAX_COMPUTE_UNIFORM_BLOCKS,
        MAX_COMPUTE_UNIFORM_COMPONENTS,
        MAX_COMPUTE_ATOMIC_COUNTERS,
        MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS,
        MAX_COMPUTE_WORK_GROUP_INVOCATIONS,
        MAX_COMPUTE_WORK_GROUP_COUNT,
        MAX_COMPUTE_WORK_GROUP_SIZE,
        MAX_COMBINED_SHADER_STORAGE_BLOCKS,
        MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS,

        // Texture related
        MAX_TEXTURE_IMAGE_UNITS,
        MAX_3D_TEXTURE_SIZE,
        MAX_TEXTURE_SIZE,
        MAX_ARRAY_TEXTURE_LAYERS,
        MAX_CLIP_DISTANCES,
        MAX_COLOR_TEXTURE_SAMPLES,

        // Shader related
        MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS,
        MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS,
        MAX_COMBINED_TEXTURE_IMAGE_UNITS,
        MAX_COMBINED_UNIFORM_BLOCKS,
        MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS,
        MAX_CUBE_MAP_TEXTURE_SIZE,
        MAX_DEPTH_TEXTURE_SAMPLES,

        // Buffer related
        MAX_ELEMENTS_INDICES,
        MAX_ELEMENTS_VERTICES,

        // Framebuffer
        MAX_FRAMEBUFFER_WIDTH,
        MAX_FRAMEBUFFER_HEIGHT,
        MAX_FRAMEBUFFER_LAYERS,
        MAX_FRAMEBUFFER_SAMPLES,

        // Others
        MAX_SERVER_WAIT_TIMEOUT,
        MAX_TEXTURE_BUFFER_SIZE,
        MAX_VIEWPORTS,
        MAX_DRAW_BUFFERS,
        MAX_DUAL_SOURCE_DRAW_BUFFERS
    };

    class Renderer {
    public:
        static Renderer* create(RRC creator);

        virtual int  init    (bool debug) = 0;
        virtual void setViewport(int x, int y, int width, int height) = 0;
        virtual void renderMesh (Mesh& mesh, Transform& transform, Camera& camera) = 0;
        virtual void renderText(const String& text, Transform& transform) = 0;
        virtual void clear() = 0;
        virtual void getDeviceConstantValue(DeviceConstant deviceConstant, void* outputBuffer) = 0;
        virtual void drawQuad2D(Material material, Transform transform) = 0;

        virtual ~Renderer() = 0;

    protected:
        bool debugMode = false;
    };
}