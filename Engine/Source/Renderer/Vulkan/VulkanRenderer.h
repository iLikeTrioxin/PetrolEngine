#pragma once

#include "../Renderer.h"
#include <vulkan/vulkan.h>

namespace Engine {
	
    class VulkanRenderer : public RendererAPI {
	public:
		// 2D stuff
	    void renderText(const String& text, Transform& transform) override;

		// 3D stuff
		void renderMesh(Mesh& mesh, Transform& transform, Camera& camera) override;

		// utility
		void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		void clear() override;
		int  init (bool debug) override;

		void getDeviceConstantValue(DeviceConstant deviceConstant, void* outputBuffer) override;

		void resetBuffers();

		const std::unordered_map<DeviceConstant, GLint> VulkanDeviceConstants{
			{DeviceConstant::MAX_TEXTURE_IMAGE_UNITS, GL_MAX_TEXTURE_IMAGE_UNITS}
		};

    private:
        const Vector<const char*> validationLayers{ "VK_LAYER_KHRONOS_validation"    };
        const Vector<const char*> deviceExtensions{  VK_KHR_SWAPCHAIN_EXTENSION_NAME };

        bool checkDeviceExtensionSupport(VkPhysicalDevice device) const;
        Vector<const char*> getRequiredExtensions();

        int  getDeviceScore  (VkPhysicalDevice device) const;
        bool isDeviceSuitable(VkPhysicalDevice device) const;

        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        void   getPhysicalDevices();
        void createLogicalDevice ();
        bool checkValidationLayerSupport();

        ~VulkanRenderer();

        VkQueue                  graphicsQueue  = VK_NULL_HANDLE;
        VkDevice                 logicalDevice  = VK_NULL_HANDLE;
        VkInstance               instance       = VK_NULL_HANDLE;
        VkSurfaceKHR             surface        = VK_NULL_HANDLE;
        VkPhysicalDevice         physicalDevice = VK_NULL_HANDLE;
        VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
	};
}
