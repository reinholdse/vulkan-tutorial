#pragma once

#include <vulkan/vulkan.h>

class VulkanDevice;

class VulkanBuffer
{
public:
	VulkanBuffer(VulkanDevice* device, void* ptr, unsigned int element_size, unsigned int count = 1);
	~VulkanBuffer();

	virtual void SetData();
	virtual void SetData(unsigned int count);
	virtual void SetData(unsigned int start_index, unsigned int count);
private:
	void CreateBuffer();
	uint32_t FindMemoryType(VkMemoryPropertyFlags props, uint32_t filter);

	VulkanDevice* m_device;
	void* m_ptr;
	unsigned int m_element_size;
	unsigned int m_count;
	VkDeviceSize m_total_size;
	VkBuffer m_buffer;
	VkDeviceMemory m_device_memory;
	void* m_mapped_memory;
};