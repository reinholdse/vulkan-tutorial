#include "Initializers.h"
#include "VulkanConfiguration.h"

VkApplicationInfo Initializers::ApplicationInfo(VulkanConfiguration& config)
{
	VkApplicationInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	info.pApplicationName = config.application_name;
	info.pEngineName = config.engine_name;
	info.applicationVersion = config.application_version;
	info.engineVersion = config.engine_version;
	info.apiVersion = config.api_version;
	return info;
}

VkInstanceCreateInfo Initializers::InstanceCreateInfo(VkApplicationInfo& app_info, std::vector<const char*>& layers, std::vector<const char*>& extensions)
{
	VkInstanceCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	info.pApplicationInfo = &app_info;
	info.enabledExtensionCount = extensions.size();
	info.enabledLayerCount = layers.size();
	info.ppEnabledExtensionNames = extensions.data();
	info.ppEnabledLayerNames = layers.data();
	return info;
}

VkDeviceQueueCreateInfo Initializers::DeviceQueueCreateInfo(uint32_t queue_family_index, float priority)
{
	VkDeviceQueueCreateInfo queue_create_info = {};
	queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queue_create_info.queueFamilyIndex = queue_family_index;
	queue_create_info.queueCount = 1;
	queue_create_info.pQueuePriorities = &priority;
	return queue_create_info;
}

VkDeviceCreateInfo Initializers::DeviceCreateInfo(std::vector<VkDeviceQueueCreateInfo>& queue_create_infos, VkPhysicalDeviceFeatures& physical_device_features)
{
	VkDeviceCreateInfo create_info = {};
	create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	create_info.pQueueCreateInfos = queue_create_infos.data();
	create_info.queueCreateInfoCount = (uint32_t)queue_create_infos.size();
	create_info.pEnabledFeatures = &physical_device_features;
	return create_info;
}

VkCommandPoolCreateInfo Initializers::CommandPoolCreateInfo(uint32_t queue_family_index, VkCommandPoolCreateFlags flags)
{
	VkCommandPoolCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	info.queueFamilyIndex = queue_family_index;
	info.flags = flags;
	return info;
}

VkCommandBufferAllocateInfo Initializers::CommandBufferAllocateInfo(VkCommandPool pool, uint32_t count)
{
	VkCommandBufferAllocateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	info.commandPool = pool;
	info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	info.commandBufferCount = count;
	return info;
}

VkBufferCreateInfo Initializers::BufferCreateInfo(VkDeviceSize size, VkBufferUsageFlags usage)
{
	VkBufferCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	info.size = size;
	info.usage = usage;
	return info;
}

VkMemoryAllocateInfo Initializers::MemoryAllocateInfo(VkDeviceSize size, uint32_t memory_type_index)
{
	VkMemoryAllocateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	info.allocationSize = size;
	info.memoryTypeIndex = memory_type_index;
	return info;
}
