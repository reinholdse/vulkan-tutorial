#include "VulkanPhysicalDevice.h"
#include "VulkanInstance.h"
#include "Validation.h"

#include <set>

VulkanPhysicalDevice::~VulkanPhysicalDevice()
{
}

VkPhysicalDevice& VulkanPhysicalDevice::GetPhysicalDevice()
{
	return m_device;
}

QueueFamilyIndices& VulkanPhysicalDevice::GetQueueFamilyIndices()
{
	return m_family_indices;
}

VkPhysicalDeviceProperties& VulkanPhysicalDevice::GetPhysicalDeviceProperties()
{
	return m_physical_device_properties;
}

VkPhysicalDeviceFeatures& VulkanPhysicalDevice::GetPhysicalDeviceFeatures()
{
	return m_physical_device_features;
}

VkPhysicalDeviceMemoryProperties& VulkanPhysicalDevice::GetPhysicalDeviceMemoryProperties()
{
	return m_physical_device_memory_properties;
}

VulkanPhysicalDevice::VulkanPhysicalDevice(VulkanInstance* instance, VkPhysicalDevice device, QueueFamilyIndices family_indices)
{
	m_instance = instance;
	m_device = device;
	m_family_indices = family_indices;
	vkGetPhysicalDeviceProperties(m_device, &m_physical_device_properties);
	vkGetPhysicalDeviceFeatures(m_device, &m_physical_device_features);
	vkGetPhysicalDeviceMemoryProperties(m_device, &m_physical_device_memory_properties);
}

VulkanPhysicalDevice* VulkanPhysicalDevice::GetPhysicalDevice(VulkanInstance* instance)
{
	std::vector<VkPhysicalDevice> devices = GetAvailablePhysicalDevices(instance);

	VkPhysicalDevice secondary_device = VK_NULL_HANDLE;
	QueueFamilyIndices secondary_queue;

	for (auto& device : devices)
	{
		QueueFamilyIndices queue_family;
		if (PhysicalDeviceSupported(device, queue_family))
		{
			VkPhysicalDeviceProperties physical_device_properties;
			vkGetPhysicalDeviceProperties(device, &physical_device_properties);

			if (physical_device_properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			{
				return new VulkanPhysicalDevice(instance, device, queue_family);
			}
			else
			{
				secondary_device = device;
				secondary_queue = queue_family;
			}
		}
	}

	if (secondary_device == VK_NULL_HANDLE)
		return nullptr;

	return new VulkanPhysicalDevice(instance, secondary_device, secondary_queue);
}

std::vector<VkPhysicalDevice> VulkanPhysicalDevice::GetAvailablePhysicalDevices(VulkanInstance* instance)
{
	uint32_t device_count = 0;
	vkEnumeratePhysicalDevices(instance->GetInstance(), &device_count, nullptr);

	std::vector<VkPhysicalDevice> devices(device_count);

	vkEnumeratePhysicalDevices(instance->GetInstance(), &device_count, devices.data());

	return devices;
}

bool VulkanPhysicalDevice::PhysicalDeviceSupported(VkPhysicalDevice& device, QueueFamilyIndices& family_indices)
{
	bool supports_queue_family = SupportsQueueFamily(device, family_indices);

	return supports_queue_family;
}

bool VulkanPhysicalDevice::SupportsQueueFamily(VkPhysicalDevice& device, QueueFamilyIndices& family_indices)
{
	uint32_t queue_family_count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, nullptr);

	std::vector<VkQueueFamilyProperties> queue_families(queue_family_count);

	vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families.data());

	uint32_t i = 0;
	for (auto& queue_family : queue_families)
	{
		if (queue_family.queueCount > 0)
		{
			if (queue_family.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				family_indices.graphics_indices = i;
			if (queue_family.queueFlags & VK_QUEUE_COMPUTE_BIT)
				family_indices.compute_indices = i;
		}

		if (family_indices.graphics_indices < UINT32_MAX && family_indices.compute_indices < UINT32_MAX)
			return true;

		i++;
	}
	return false;
}

