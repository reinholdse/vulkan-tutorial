#pragma once

#include <vulkan\vulkan.h>
#include <vector>

struct VulkanConfiguration;

namespace Initializers
{
	VkApplicationInfo ApplicationInfo(VulkanConfiguration& config);

	VkInstanceCreateInfo InstanceCreateInfo(VkApplicationInfo& app_info, std::vector<const char*>& layers, std::vector<const char*>& extensions);

	VkDeviceQueueCreateInfo DeviceQueueCreateInfo(uint32_t queue_family_index, float priority);

	VkDeviceCreateInfo DeviceCreateInfo(std::vector<VkDeviceQueueCreateInfo>& queue_create_infos, VkPhysicalDeviceFeatures& physical_device_features);

	VkCommandPoolCreateInfo CommandPoolCreateInfo(uint32_t queue_family_index, VkCommandPoolCreateFlags flags = 0);

	VkCommandBufferAllocateInfo CommandBufferAllocateInfo(VkCommandPool pool, uint32_t count);

	VkBufferCreateInfo BufferCreateInfo(VkDeviceSize size, VkBufferUsageFlags usage);

	VkMemoryAllocateInfo MemoryAllocateInfo(VkDeviceSize size, uint32_t memory_type_index);
}