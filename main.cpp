#include "VulkanInstance.h"
#include "VulkanPhysicalDevice.h"
#include "VulkanDevice.h"
#include "VulkanBuffer.h"

VulkanInstance* instance;
VulkanPhysicalDevice* physical_device;
VulkanDevice* device;
VulkanBuffer* buffer;

int main()
{
	VulkanConfiguration vulkan_config;
	vulkan_config.application_name = "My Vulkan App";
	vulkan_config.application_version = VK_MAKE_VERSION(1, 0, 0);

	instance = new VulkanInstance(vulkan_config);
	physical_device = VulkanPhysicalDevice::GetPhysicalDevice(instance);
	device = new VulkanDevice(instance, physical_device);
	
	VkCommandBuffer* commands = new VkCommandBuffer[3];
	device->GetComputeCommand(commands, 3);

	float* arr = new float[3];
	for (unsigned int i = 0; i < 3; i++)
	{
		arr[i] = i;
	}

	buffer = new VulkanBuffer(device, arr, sizeof(float), 3);

	buffer->SetData();


	device->FreeComputeCommand(commands, 3);

	delete buffer;
	delete arr;
	delete device;
	delete physical_device;
	delete instance;

	return 0;
}