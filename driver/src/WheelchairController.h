#pragma once

#include <chrono>
#include <cmath>

#include <WheelchairDriverFactory.h>

class WheelchairController : public vr::ITrackedDeviceServerDriver
{
public:

	explicit WheelchairController(std::string serial);

	~WheelchairController() = default;

	std::string GetSerial();

	void Update();

	vr::TrackedDeviceIndex_t GetDeviceIndex();

	vr::EVRInitError Activate(uint32_t unObjectId) override;

	void Deactivate() override;

	void EnterStandby() override;

	void *GetComponent(const char *pchComponentNameAndVersion) override;

	void DebugRequest(const char *pchRequest, char *pchResponseBuffer, uint32_t unResponseBufferSize) override;

	vr::DriverPose_t GetPose() override;

private:
	vr::TrackedDeviceIndex_t m_deviceIndex = vr::k_unTrackedDeviceIndexInvalid;
	std::string m_serial;

	bool m_arduinoConnected;

	vr::VRInputComponentHandle_t m_xComponent = 0;
	vr::VRInputComponentHandle_t m_yComponent = 0;
};