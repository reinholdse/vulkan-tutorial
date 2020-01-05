#include "VulkanBuffer.h"
#include "VulkanDevice.h"
#include "VulkanPhysicalDevice.h"
#include "Initializers.h"
#include "Validation.h"

#include <assert.h>

VulkanBuffer::VulkanBuffer(VulkanDevice* device, void* ptr, unsigned int element_size, unsigned int count)
{
	m_device = device;
	m_ptr = ptr;
	m_element_size = element_size;
	m_count = count;
	m_total_size = m_element_size * m_count;
	CreateBuffer();
}

VulkanBuffer::~VulkanBuffer()
{
	vkUnmapMemory(*m_device->GetDevice(), m_device_memory);
	vkDestroyBuffer(*m_device->GetDevice(), m_buffer, nullptr);
	vkFreeMemory(*m_device->GetDevice(), m_device_memory, nullptr);
}

void VulkanBuffer::SetData()
{
	memcpy(m_mapped_memory, m_ptr, (size_t)m_total_size);
}

void VulkanBuffer::SetData(unsigned int count)
{
	memcpy(m_mapped_memory, m_ptr, m_element_size * count);
}

void VulkanBuffer::SetData(unsigned int start_index, unsigned int count)
{
	memcpy(
		((char*)m_mapped_memory) + (start_index * m_element_size),
		((char*)m_ptr) + (start_index * m_element_size),
		m_element_size * count
	);
}

void VulkanBuffer::CreateBuffer()
{
	VkBufferCreateInfo buffer_create_info = Initializers::BufferCreateInfo(m_total_size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);

	ErrorCheck(vkCreateBuffer(*m_device->GetDevice(), &buffer_create_info, nullptr, &m_buffer));

	VkMemoryRequirements memory_requirements;
	vkGetBufferMemoryRequirements(*m_device->GetDevice(), m_buffer, &memory_requirements);

	VkMemoryAllocateInfo memory_allocate_info = Initializers::MemoryAllocateInfo(memory_requirements.size, FindMemoryType(
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,
		memory_requirements.memoryTypeBits
	));

	ErrorCheck(vkAllocateMemory(*m_device->GetDevice(), &memory_allocate_info, nullptr, &m_device_memory));
	ErrorCheck(vkBindBufferMemory(*m_device->GetDevice(), m_buffer, m_device_memory, 0));

	vkMapMemory(*m_device->GetDevice(), m_device_memory, 0, memory_requirements.size, 0, &m_mapped_memory);
}

uint32_t VulkanBuffer::FindMemoryType(VkMemoryPropertyFlags props, uint32_t type_filter)
{
	for (uint32_t i = 0; m_device->GetPhysicalDevice()->GetPhysicalDeviceMemoryProperties().memoryTypeCount; i++)
	{
		if ((type_filter & (1 << i)) && (m_device->GetPhysicalDevice()->GetPhysicalDeviceMemoryProperties().memoryTypes[i].propertyFlags & props) == props)
		{
			return i;
		}
	}

	assert(0 && "No Available Memory Properties");
	return -1;
}
