#include "InputManager.h"


InputManager::InputManager(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	m_directInput = 0;
	m_keyboard = 0;
	m_mouse = 0;

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	m_mouseX = 0;
	m_mouseY = 0;

	HRESULT result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if(FAILED(result))
	{
		return ;
	}

	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if(FAILED(result))
	{
		return ;
	}

	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(result))
	{
		return ;
	}

	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if(FAILED(result))
	{
		return ;
	}

	result = m_keyboard->Acquire();
	if(FAILED(result))
	{
		return ;
	}
	
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if(FAILED(result))
	{
		return ;
	}
	
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if(FAILED(result))
	{
		return ;
	}

	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if(FAILED(result))
	{
		return ;
	}

	result = m_mouse->Acquire();
	if(FAILED(result))
	{
		return ;
	}

}


InputManager::~InputManager(void)
{
	if(m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = 0;
	}

	if(m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = 0;
	}

	if(m_directInput)
	{
		m_directInput->Release();
		m_directInput = 0;
	}
}

void InputManager::PollInput()
{
	ReadKeyboard();
	ReadMouse();
}

void InputManager::ReadKeyboard()
{
	HRESULT result;

	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if(FAILED(result))
	{
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
	}
}

void InputManager::ReadMouse()
{
	HRESULT result;

	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if(FAILED(result))
	{

		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
	}
	else
	{
		m_mouseX += m_mouseState.lX;
		m_mouseY += m_mouseState.lY;

		if(m_mouseX < 0)  { m_mouseX = 0; }
		if(m_mouseY < 0)  { m_mouseY = 0; }
	
		if(m_mouseX > m_screenWidth)  { m_mouseX = m_screenWidth; }
		if(m_mouseY > m_screenHeight) { m_mouseY = m_screenHeight; }
	}
}