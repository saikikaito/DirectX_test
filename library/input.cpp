#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#include "../system/window.h"
#include "input.h"


namespace lib {

	static UINT key_codes[] = {
		DIK_BACKSPACE,	// KEY_BACK BackSpace�L�[
		DIK_TAB,		// KEY_TAB Tab�L�[
		DIK_RETURN,		// KEY_RETURN Enter�L�[

		DIK_LSHIFT,		// KEY_LSHIFT ��Shift�L�[
		DIK_RSHIFT,		// KEY_RSHIFT �EShift�L�[
		DIK_LCONTROL,	// KEY_LCONTROL ��Ctrl�L�[
		DIK_RCONTROL,	// KEY_RCONTROL �ECtrl�L�[
		DIK_ESCAPE,		// KEY_ESCAPE Esc�L�[
		DIK_SPACE,		// KEY_SPACE �X�y�[�X�L�[
		DIK_PGUP,		// KEY_PGUP PageUp�L�[
		DIK_PGDN,		// KEY_PGDN PageDown�L�[
		DIK_END,		// KEY_END End�L�[
		DIK_HOME,		// KEY_HOME Home�L�[
		DIK_LEFT,		// KEY_LEFT ���L�[
		DIK_UP,			// KEY_UP ��L�[
		DIK_RIGHT,		// KEY_RIGHT �E�L�[
		DIK_DOWN,		// KEY_DOWN ���L�[
		DIK_INSERT,		// KEY_INSERT Insert�L�[
		DIK_DELETE,		// KEY_DELETE Delete�L�[

		DIK_MINUS,		// KEY_MINUS �|�L�[
		DIK_YEN,		// KEY_YEN ���L�[
		DIK_PREVTRACK,	// KEY_PREVTRACK �O�L�[
		DIK_PERIOD,		// KEY_PERIOD �D�L�[
		DIK_SLASH,		// KEY_SLASH �^�L�[
		DIK_LALT,		// KEY_LALT ��Alt�L�[
		DIK_RALT,		// KEY_RALT �EAlt�L�[
		DIK_SCROLL,		// KEY_SCROLL ScrollLock�L�[
		DIK_SEMICOLON,	// KEY_SEMICOLON �G�L�[
		DIK_COLON,		// KEY_COLON �F�L�[
		DIK_LBRACKET,	// KEY_LBRACKET �m�L�[
		DIK_RBRACKET,	// KEY_RBRACKET �n�L�[
		DIK_AT,			// KEY_AT ���L�[
		DIK_BACKSLASH,	// KEY_BACKSLASH �_�L�[
		DIK_COMMA,		// KEY_COMMA �C�L�[
		DIK_KANJI,		// KEY_KANJI �����L�[
		DIK_CONVERT,	// KEY_CONVERT �ϊ��L�[
		DIK_NOCONVERT,	// KEY_NOCONVERT ���ϊ��L�[
		DIK_KANA,		// KEY_KANA �J�i�L�[
		DIK_APPS,		// KEY_APPS �A�v���P�[�V�������j���[�L�[
		DIK_CAPSLOCK,	// KEY_CAPSLOCK CaspLock�L�[
		DIK_SYSRQ,		// KEY_SYSRQ PrintScreen�L�[
		DIK_PAUSE,		// KEY_PAUSE PauseBreak�L�[
		DIK_LWIN,		// KEY_LWIN ��Win�L�[
		DIK_RWIN,		// KEY_RWIN �EWin�L�[

		DIK_NUMLOCK,	// KEY_NUMLOCK �e���L�[NumLock�L�[
		DIK_NUMPAD0,	// KEY_NUMPAD0 �e���L�[�O
		DIK_NUMPAD1,	// KEY_NUMPAD1 �e���L�[�P
		DIK_NUMPAD2,	// KEY_NUMPAD2 �e���L�[�Q
		DIK_NUMPAD3,	// KEY_NUMPAD3 �e���L�[�R
		DIK_NUMPAD4,	// KEY_NUMPAD4 �e���L�[�S
		DIK_NUMPAD5,	// KEY_NUMPAD5 �e���L�[�T
		DIK_NUMPAD6,	// KEY_NUMPAD6 �e���L�[�U
		DIK_NUMPAD7,	// KEY_NUMPAD7 �e���L�[�V
		DIK_NUMPAD8,	// KEY_NUMPAD8 �e���L�[�W
		DIK_NUMPAD9,	// KEY_NUMPAD9 �e���L�[�X
		DIK_MULTIPLY,	// KEY_MULTIPLY �e���L�[���L�[
		DIK_ADD,		// KEY_ADD �e���L�[�{�L�[
		DIK_SUBTRACT,	// KEY_SUBTRACT �e���L�[�|�L�[
		DIK_DECIMAL,	// KEY_DECIMAL �e���L�[�D�L�[
		DIK_DIVIDE,		// KEY_DIVIDE �e���L�[�^�L�[
		DIK_NUMPADENTER,// KEY_NUMPADENTER �e���L�[�̃G���^�[�L�[

		DIK_F1,			// KEY_F1 �e�P�L�[
		DIK_F2,			// KEY_F2 �e�Q�L�[
		DIK_F3,			// KEY_F3 �e�R�L�[
		DIK_F4,			// KEY_F4 �e�S�L�[
		DIK_F5,			// KEY_F5 �e�T�L�[
		DIK_F6,			// KEY_F6 �e�U�L�[
		DIK_F7,			// KEY_F7 �e�V�L�[
		DIK_F8,			// KEY_F8 �e�W�L�[
		DIK_F9,			// KEY_F9 �e�X�L�[
		DIK_F10,		// KEY_F10 �e�P�O�L�[
		DIK_F11,		// KEY_F11 �e�P�P�L�[
		DIK_F12,		// KEY_F12 �e�P�Q�L�[

		DIK_A,			// KEY_A �`�L�[
		DIK_B,			// KEY_B �a�L�[
		DIK_C,			// KEY_C �b�L�[
		DIK_D,			// KEY_D �c�L�[
		DIK_E,			// KEY_E �d�L�[
		DIK_F,			// KEY_F �e�L�[
		DIK_G,			// KEY_G �f�L�[
		DIK_H,			// KEY_H �g�L�[
		DIK_I,			// KEY_I �h�L�[
		DIK_J,			// KEY_J �i�L�[
		DIK_K,			// KEY_K �j�L�[
		DIK_L,			// KEY_L �k�L�[
		DIK_M,			// KEY_M �l�L�[
		DIK_N,			// KEY_N �m�L�[
		DIK_O,			// KEY_O �n�L�[
		DIK_P,			// KEY_P �o�L�[
		DIK_Q,			// KEY_Q �p�L�[
		DIK_R,			// KEY_R �q�L�[
		DIK_S,			// KEY_S �r�L�[
		DIK_T,			// KEY_T �s�L�[
		DIK_U,			// KEY_U �t�L�[
		DIK_V,			// KEY_V �u�L�[
		DIK_W,			// KEY_W �v�L�[
		DIK_X,			// KEY_X �w�L�[
		DIK_Y,			// KEY_Y �x�L�[
		DIK_Z,			// KEY_Z �y�L�[

		DIK_0,			// KEY_0 �O�L�[
		DIK_1,			// KEY_1 �P�L�[
		DIK_2,			// KEY_2 �Q�L�[
		DIK_3,			// KEY_3 �R�L�[
		DIK_4,			// KEY_4 �S�L�[
		DIK_5,			// KEY_5 �T�L�[
		DIK_6,			// KEY_6 �U�L�[
		DIK_7,			// KEY_7 �V�L�[
		DIK_8,			// KEY_8 �W�L�[
		DIK_9,			// KEY_9 �X�L�[
	};

	bool Input::initialize() {

		memset(key_now_, 0, sizeof(key_now_));
		memset(key_prev_, 0, sizeof(key_prev_));

		// �C���^�[�t�F�[�X�̍쐬
		if (FAILED(DirectInput8Create(GetModuleHandle(0), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)(&input_), NULL))) return false;

		// �f�o�C�X�̍쐬
		if (FAILED(input_->CreateDevice(GUID_SysKeyboard, &device_, NULL))) return false;

		// �t�H�[�}�b�g�̐ݒ�
		// �L�[             ... c_dfDIKeyboard
		// �}�E�X           ... c_dfDIMouse
		// �W���C�X�e�B�b�N ... c_dfDIJoystick
		if (FAILED(device_->SetDataFormat(&c_dfDIKeyboard))) return false;

		// �������[�h�̐ݒ�
		// �t�H�A�O���E���h or �o�b�N�O���E���h
		// �r���I or ��r���I
		if (FAILED(device_->SetCooperativeLevel(sys::Window::handle_, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND))) return false;

		// �f�o�C�X����J�n
		if (FAILED(device_->Acquire())) return false;

		return true;
	}

	bool Input::update() {
		memcpy(key_prev_, key_now_, sizeof(key_prev_));
		if (FAILED(device_->GetDeviceState(KEY_MAX, key_now_))) return false;
		return true;
	}

	bool Input::finalize() {

		// �f�o�C�X����̒�~
		if (FAILED(device_->Unacquire())) return false;

		device_->Release();
		input_->Release();
		
		return true;
	}

	bool Input::isKeyDown(const KeyCode key_code) {
		return (key_now_[key_codes[(int)key_code]] & 0x80);
	}

	bool Input::isKeyDownTrigger(const KeyCode key_code) {
		return (key_now_[key_codes[(int)key_code]] & 0x80) && !(key_prev_[key_codes[(int)key_code]] & 0x80);
	}

	bool Input::isKeyReleaseTrigger(const KeyCode key_code) {
		return !(key_now_[key_codes[(int)key_code]] & 0x80) && (key_prev_[key_codes[(int)key_code]] & 0x80);
	}

}
