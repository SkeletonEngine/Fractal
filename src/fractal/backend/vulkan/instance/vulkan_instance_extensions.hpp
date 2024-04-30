#pragma once

struct VkInstanceCreateInfo;

namespace Fractal {

void ListInstanceExtensionSupport();
bool CheckInstanceExtensionSupport();
void PopulateInstanceExtensions(VkInstanceCreateInfo& instance_info);

}
