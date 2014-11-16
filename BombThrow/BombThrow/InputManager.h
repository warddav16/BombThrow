#pragma once

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>

#include "KeyCode.h"

class InputManager
{
public:
	static InputManager& Instance(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
	{
		static InputManager instance(hinstance, hwnd, screenWidth, screenHeight);
		return instance; //Fancy singleton pattern
	}
	
	~InputManager(void);
	void PollInput();
	void GetMouseLocation(int& mouseX, int& mouseY) { mouseX = m_mouseX; mouseY = m_mouseY; }
	bool GetKey(KeyCode key) { return m_keyboardState[key] & 0x80; }

private:
	InputManager(void) {}

	InputManager(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight);

	InputManager(InputManager const&) {}
	void operator=(InputManager const&) {}

	void ReadMouse();
	void ReadKeyboard();

	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

	unsigned char m_keyboardState[256];
	DIMOUSESTATE m_mouseState;

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
};

