#pragma once

#include <cstdlib>
#include <memory>

#include <openvr_driver.h>

extern "C" __declspec(dllexport) void *HmdDriverFactory(const char *interface_name, int *return_code);

namespace WheelchairDriver
{
	class VRDriver;

	std::shared_ptr<VRDriver> GetDriver();
}