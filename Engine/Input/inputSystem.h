#pragma once
#include "Math/mathUtils.h"
#include <vector>
#include <array>
#include <cstdint>

namespace vl
{
	class InputSystem
	{
	public:
		enum State
		{
			Idle,
			Pressed,
			Held,
			Released
		};
	public:
		InputSystem() = default;
		~InputSystem() = default;

		void Initialize();
		void Shutdown();

		void Update();

		// keyboard
		State GetKeyState(uint32_t key);
		bool GetKeyDown(uint32_t key) { return m_keybardState[key]; }
		bool GetPreviousKeyDown(uint32_t key) { return m_prevKeybardState[key]; }

		// mouse
		const glm::vec2& GetMousePosition() const { return m_mousePosition; }
		const glm::vec2& GetMouseRelative() const { return m_mouseRelative; }

		State GetButtonState(uint32_t button);
		bool GetButtonDown(uint32_t button) { return m_mouseButtonState[button]; }
		bool GetPreviousButtonDown(uint32_t button) { return m_prevMouseButtonState[button]; }


	private:
		// keyboard
		int m_numKeys;
		std::vector<uint8_t> m_keybardState;
		std::vector<uint8_t> m_prevKeybardState;

		// mouse
		glm::vec2 m_mousePosition;
		glm::vec2 m_prevMousePosition;
		glm::vec2 m_mouseRelative;

		std::array<uint8_t, 3> m_mouseButtonState;
		std::array<uint8_t, 3> m_prevMouseButtonState;
	};

	extern const uint32_t key_space;
	extern const uint32_t key_pUp;
	extern const uint32_t key_pDn;
	extern const uint32_t key_up;
	extern const uint32_t key_down;
	extern const uint32_t key_left;
	extern const uint32_t key_right;
	extern const uint32_t key_escape;

	extern const uint32_t button_left;
	extern const uint32_t button_middle;
	extern const uint32_t button_right;
}