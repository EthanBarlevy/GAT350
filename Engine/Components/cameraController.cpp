#include "cameraController.h"
#include "includes.h"
#include "Framework/actor.h"

namespace vl
{
	void CameraController::Update()
	{
		// update transform
		if (g_inputSystem.GetKeyState(key_left) == InputSystem::Held)
		{
			m_owner->GetTransform().position.x -= speed * (float)g_time.deltaTime;
		}
		if (g_inputSystem.GetKeyState(key_right) == InputSystem::Held)
		{
			m_owner->GetTransform().position.x += speed * (float)g_time.deltaTime;
		}
		if (g_inputSystem.GetKeyState(key_up) == InputSystem::Held)
		{
			m_owner->GetTransform().position.y += speed * (float)g_time.deltaTime;
		}
		if (g_inputSystem.GetKeyState(key_down) == InputSystem::Held)
		{
			m_owner->GetTransform().position.y -= speed * (float)g_time.deltaTime;
		}
		if (g_inputSystem.GetKeyState(key_pUp) == InputSystem::Held)
		{
			m_owner->GetTransform().position.z -= speed * (float)g_time.deltaTime;
		}
		if (g_inputSystem.GetKeyState(key_pDn) == InputSystem::Held)
		{
			m_owner->GetTransform().position.z += speed * (float)g_time.deltaTime;
		}
	}

	bool CameraController::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool CameraController::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, speed);
		return true;
	}
}
