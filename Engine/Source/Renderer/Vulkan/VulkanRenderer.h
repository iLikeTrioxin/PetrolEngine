#pragma once

#include "../Renderer.h"
#include <vulkan/vulkan.h>

namespace PetrolEngine {
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
		void setViewport(int x, int y, int width, int height) override;
		void clear() override;
		int  init (bool debug) override;

		void getDeviceConstantValue(DeviceConstant deviceConstant, void* outputBuffer) override;

		void resetBuffers();

		const std::unordered_map<DeviceConstant, GLint> VulkanDeviceConstants{
			{DeviceConstant::MAX_TEXTURE_IMAGE_UNITS, GL_MAX_TEXTURE_IMAGE_UNITS}
		};

        ~VulkanRenderer() override;
    private:
        static Vector<const char*> validationLayers;
        static Vector<const char*> deviceExtensions;

        Vector<const char*> getRequiredExtensions() const;

        static bool checkDeviceExtensionSupport(VkPhysicalDevice device);

        int  getDeviceScore  (VkPhysicalDevice device) const;
        bool isDeviceSuitable(VkPhysicalDevice device) const;

        QueueFamilyIndices      findQueueFamilies    (VkPhysicalDevice device) const;
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) const;
        VkShaderModule createShaderModule(const std::vector<char>& code);

        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);

        void createSwapChain(Window* window);

        VkExtent2D       chooseSwapExtent     (const VkSurfaceCapabilitiesKHR& capabilities, Window* window);
        VkPresentModeKHR chooseSwapPresentMode(const Vector<VkPresentModeKHR>& availablePresentModes);

        void   createImageViews();
        void   getPhysicalDevices();
        void createLogicalDevice ();
        bool checkValidationLayerSupport();

        Vector<VkImageView>      swapChainImageViews {};
        Vector<VkImage>          swapChainImages     {};
        VkExtent2D               swapChainExtent     {};
        VkFormat                 swapChainImageFormat{};

        VkSwapchainKHR           swapChain      = VK_NULL_HANDLE;
        VkQueue                  graphicsQueue  = VK_NULL_HANDLE;
        VkDevice                 logicalDevice  = VK_NULL_HANDLE;
        VkInstance               instance       = VK_NULL_HANDLE;
        VkSurfaceKHR             surface        = VK_NULL_HANDLE;
        VkPhysicalDevice         physicalDevice = VK_NULL_HANDLE;
        VkDebugUtilsMessengerEXT debugMessenger = VK_NULL_HANDLE;
	};
}
