#pragma once

#include "../Renderer.h"
#include <vulkan/vulkan.h>

namespace Engine {
    struct QueueFamilyIndices {
        Optional<uint32_t> graphicsFamily;
        Optional<uint32_t> presentFamily;

        bool isValid() const { return graphicsFamily.has_value() && presentFamily.has_value(); }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;

        Vector<VkSurfaceFormatKHR> formats;
        Vector<VkPresentModeKHR  > presentModes;
    };

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
        static Vector<const char*> validationLayers;
        static Vector<const char*> deviceExtensions;

        Vector<const char*> getRequiredExtensions() const;

        static bool checkDeviceExtensionSupport(VkPhysicalDevice device);

        int  getDeviceScore  (VkPhysicalDevice device) const;
        bool isDeviceSuitable(VkPhysicalDevice device) const;

        QueueFamilyIndices      findQueueFamilies    (VkPhysicalDevice device) const;
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) const;

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
