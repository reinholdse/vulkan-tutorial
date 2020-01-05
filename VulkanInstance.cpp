#include "VulkanInstance.h"

#include "Validation.h"
#include "Initializers.h"

VulkanInstance::VulkanInstance(VulkanConfiguration& vulkan_config)
{
	layers.push_back("VK_LAYER_LUNARG_standard_validation");
	extensions.push_back("VK_EXT_debug_report");

	VkApplicationInfo application_info = Initializers::ApplicationInfo(vulkan_config);
	VkInstanceCreateInfo instance_info = Initializers::InstanceCreateInfo(application_info, layers, extensions);
	ErrorCheck(vkCreateInstance(&instance_info, NULL, &instance));
}

VulkanInstance::~VulkanInstance()
{
	vkDestroyInstance(instance, NULL);
}

VkInstance& VulkanInstance::GetInstance()
{
	return instance;
}
