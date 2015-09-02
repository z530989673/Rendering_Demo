#ifndef __INPUT_MANAGER__
#define __INPUT_MANAGER__
#include "Includes.h"
#include <bitset>

class InputManager {
public:
	InputManager();
	~InputManager();
	static InputManager* Instance() {
		if (!m_instance) {
			m_instance = new InputManager();
		}
		return m_instance;
	}

	void Update();
	bool GetKeyDown(char key);
	bool GetKeyUp(char key);
	bool GetKeyHold(char key);

private:
	static InputManager* m_instance;

	bitset<256> m_keyState;
	bitset<256> m_lastKeyState;

};

#endif
