#pragma once

#include <vulkan/vulkan.h>

class VulkanPhysicalDevice;
class VulkanInstance;

class VulkanDevice
{
public:
	VulkanDevice(VulkanInstance* instance, VulkanPhysicalDevice* physical_device);
	VulkanInstance* GetInstance();
	VkDevice* GetDevice();
	VkQueue* GetComputeQueue();
	VkCommandPool& GetComputeCommandPool();
	VulkanPhysicalDevice* GetPhysicalDevice();
	void GetComputeCommand(VkCommandBuffer* buffers, uint32_t count);
	void FreeComputeCommand(VkCommandBuffer* buffers, uint32_t count);
	~VulkanDevice();
private:
	VulkanInstance* m_instance;
	VulkanPhysicalDevice* m_physical_device;
	VkDevice m_device;
	VkQueue m_compute_queue;
	VkCommandPool m_compute_command_pool;
};