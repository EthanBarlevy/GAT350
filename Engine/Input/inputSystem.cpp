#include "inputSystem.h"
#include <SDL.h>
#include <iostream>

namespace vl
{
	const uint32_t key_space = SDL_SCANCODE_SPACE;
	const uint32_t key_up = SDL_SCANCODE_W;
	const uint32_t key_down = SDL_SCANCODE_S;
	const uint32_t key_left = SDL_SCANCODE_A;
	const uint32_t key_right = SDL_SCANCODE_D;
	const uint32_t key_escape = SDL_SCANCODE_ESCAPE;
	const uint32_t key_pUp = SDL_SCANCODE_Q;
	const uint32_t key_pDn = SDL_SCANCODE_E;

	const uint32_t button_left = 0;
	const uint32_t button_middle = 1;
	const uint32_t button_right = 2;

	void InputSystem::Initialize()
	{
		const uint8_t* keyboardState = SDL_GetKeyboardState(&m_numKeys);

		m_keybardState.resize(m_numKeys);
		std::copy(keyboardState, keyboardState + m_numKeys, m_keybardState.begin());

		m_prevKeybardState = m_keybardState;
	}

	void InputSystem::Shutdown()
	{
		//
	}
	void InputSystem::Update()
	{
		SDL_Event event;
		SDL_PollEvent(&event);

		// save prev state
		m_prevKeybardState = m_keybardState;

		// save current state
		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardState, keyboardState + m_numKeys, m_keybardState.begin());

		// idk mouse things
		m_prevMouseButtonState = m_mouseButtonState;
		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		m_mousePosition = glm::vec2{ (float)x , (float)y };
		m_mouseRelative = m_mousePosition - m_prevMousePosition;
		m_prevMousePosition = m_mousePosition;

		m_mouseButtonState[0] = buttons & SDL_BUTTON_LMASK;
		m_mouseButtonState[1] = buttons & SDL_BUTTON_MMASK;
		m_mouseButtonState[2] = buttons & SDL_BUTTON_RMASK;
	}

	InputSystem::State InputSystem::GetKeyState(uint32_t key)
	{
		State keyState = State::Idle;
		bool keyDown = GetKeyDown(key);
		bool prevKeyDown = GetPreviousKeyDown(key);

		if (keyDown) 
		{
			if(prevKeyDown) 
			{
				keyState = State::Held;
			}
			else 
			{
				keyState = State::Pressed;
			}
		}
		else if (prevKeyDown)
		{
			keyState = State::Released;
		}

		return keyState;
	}

	InputSystem::State InputSystem::GetButtonState(uint32_t button)
	{
		State keyState = State::Idle;
		bool buttonDown = GetButtonDown(button);
		bool prevButtonDown = GetPreviousButtonDown(button);

		if (buttonDown)
		{
			if (prevButtonDown)
			{
				keyState = State::Held;
			}
			else
			{
				keyState = State::Pressed;
			}
		}
		else if (prevButtonDown)
		{
			keyState = State::Released;
		}

		return keyState;
	}
}