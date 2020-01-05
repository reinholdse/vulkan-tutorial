#include "Validation.h"

#include <assert.h>
#include <iostream>

void ErrorCheck(VkResult result)
{
	if (result != VK_SUCCESS)
	{
		std::cout << "Error" << std::endl;
		assert(0 && "There Was A Error");
	}
}
