#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>


namespace lib {

	// �L�[�񋓒萔
	enum class KeyCode {
		KEY_BACK,			// BackSpace�L�[
		KEY_TAB,			// Tab�L�[
		KEY_RETURN,			// Enter�L�[

		KEY_LSHIFT,			// ��Shift�L�[
		KEY_RSHIFT,			// �EShift�L�[
		KEY_LCONTROL,		// ��Ctrl�L�[
		KEY_RCONTROL,		// �ECtrl�L�[
		KEY_ESCAPE,			// Esc�L�[
		KEY_SPACE,			// �X�y�[�X�L�[
		KEY_PGUP,			// PageUp�L�[
		KEY_PGDN,			// PageDown�L�[
		KEY_END,			// End�L�[
		KEY_HOME,			// Home�L�[
		KEY_LEFT,			// ���L�[
		KEY_UP,				// ��L�[
		KEY_RIGHT,			// �E�L�[
		KEY_DOWN,			// ���L�[
		KEY_INSERT,			// Insert�L�[
		KEY_DELETE,			// Delete�L�[

		KEY_MINUS,			// �|�L�[
		KEY_YEN,			// ���L�[
		KEY_PREVTRACK,		// �O�L�[
		KEY_PERIOD,			// �D�L�[
		KEY_SLASH,			// �^�L�[
		KEY_LALT,			// ��Alt�L�[
		KEY_RALT,			// �EAlt�L�[
		KEY_SCROLL,			// ScrollLock�L�[
		KEY_SEMICOLON,		// �G�L�[
		KEY_COLON,			// �F�L�[
		KEY_LBRACKET,		// �m�L�[
		KEY_RBRACKET,		// �n�L�[
		KEY_AT,				// ���L�[
		KEY_BACKSLASH,		// �_�L�[
		KEY_COMMA,			// �C�L�[
		KEY_KANJI,			// �����L�[
		KEY_CONVERT,		// �ϊ��L�[
		KEY_NOCONVERT,		// ���ϊ��L�[
		KEY_KANA,			// �J�i�L�[
		KEY_APPS,			// �A�v���P�[�V�������j���[�L�[
		KEY_CAPSLOCK,		// CaspLock�L�[
		KEY_SYSRQ,			// PrintScreen�L�[
		KEY_PAUSE,			// PauseBreak�L�[
		KEY_LWIN,			// ��Win�L�[
		KEY_RWIN,			// �EWin�L�[

		KEY_NUMLOCK,		// �e���L�[NumLock�L�[
		KEY_NUMPAD0,		// �e���L�[�O
		KEY_NUMPAD1,		// �e���L�[�P
		KEY_NUMPAD2,		// �e���L�[�Q
		KEY_NUMPAD3,		// �e���L�[�R
		KEY_NUMPAD4,		// �e���L�[�S
		KEY_NUMPAD5,		// �e���L�[�T
		KEY_NUMPAD6,		// �e���L�[�U
		KEY_NUMPAD7,		// �e���L�[�V
		KEY_NUMPAD8,		// �e���L�[�W
		KEY_NUMPAD9,		// �e���L�[�X
		KEY_MULTIPLY,		// �e���L�[���L�[
		KEY_ADD,			// �e���L�[�{�L�[
		KEY_SUBTRACT,		// �e���L�[�|�L�[
		KEY_DECIMAL,		// �e���L�[�D�L�[
		KEY_DIVIDE,			// �e���L�[�^�L�[
		KEY_NUMPADENTER,	// �e���L�[�̃G���^�[�L�[

		KEY_F1,				// �e�P�L�[
		KEY_F2,				// �e�Q�L�[
		KEY_F3,				// �e�R�L�[
		KEY_F4,				// �e�S�L�[
		KEY_F5,				// �e�T�L�[
		KEY_F6,				// �e�U�L�[
		KEY_F7,				// �e�V�L�[
		KEY_F8,				// �e�W�L�[
		KEY_F9,				// �e�X�L�[
		KEY_F10,			// �e�P�O�L�[
		KEY_F11,			// �e�P�P�L�[
		KEY_F12,			// �e�P�Q�L�[

		KEY_A,				// �`�L�[
		KEY_B,				// �a�L�[
		KEY_C,				// �b�L�[
		KEY_D,				// �c�L�[
		KEY_E,				// �d�L�[
		KEY_F,				// �e�L�[
		KEY_G,				// �f�L�[
		KEY_H,				// �g�L�[
		KEY_I,				// �h�L�[
		KEY_J,				// �i�L�[
		KEY_K,				// �j�L�[
		KEY_L,				// �k�L�[
		KEY_M,				// �l�L�[
		KEY_N,				// �m�L�[
		KEY_O,				// �n�L�[
		KEY_P,				// �o�L�[
		KEY_Q,				// �p�L�[
		KEY_R,				// �q�L�[
		KEY_S,				// �r�L�[
		KEY_T,				// �s�L�[
		KEY_U,				// �t�L�[
		KEY_V,				// �u�L�[
		KEY_W,				// �v�L�[
		KEY_X,				// �w�L�[
		KEY_Y,				// �x�L�[
		KEY_Z,				// �y�L�[

		KEY_0,				// �O�L�[
		KEY_1,				// �P�L�[
		KEY_2,				// �Q�L�[
		KEY_3,				// �R�L�[
		KEY_4,				// �S�L�[
		KEY_5,				// �T�L�[
		KEY_6,				// �U�L�[
		KEY_7,				// �V�L�[
		KEY_8,				// �W�L�[
		KEY_9,				// �X�L�[
	};

	//// �}�E�X�{�^���񋓒萔
	//enum class MouseCode {
	//	MOUSE_LEFT,		// �}�E�X���{�^��
	//	MOUSE_RIGHT,	// �}�E�X�E�{�^��
	//	MOUSE_MIDDLE,	// �}�E�X�����{�^��
	//	MOUSE_1,		// �}�E�X�P�{�^��
	//	MOUSE_2,		// �}�E�X�Q�{�^��
	//	MOUSE_3,		// �}�E�X�R�{�^��
	//	MOUSE_4,		// �}�E�X�S�{�^��
	//	MOUSE_5,		// �}�E�X�T�{�^��
	//	MOUSE_6,		// �}�E�X�U�{�^��
	//	MOUSE_7,		// �}�E�X�V�{�^��
	//	MOUSE_8,		// �}�E�X�W�{�^��
	//};

	class Input final {
		// initialize, finalize���ĂԂ���
		friend class Library;
	private:
		// �����̋֎~
		Input() = delete;
		Input(const Input&) = delete;
		Input(const Input&&) = delete;
		Input& operator =(const Input&) = delete;
		Input& operator =(const Input&&) = delete;

		inline static constexpr int KEY_MAX = 256;

		inline static LPDIRECTINPUT8 input_ = nullptr;
		inline static LPDIRECTINPUTDEVICE8 device_ = nullptr;
		inline static BYTE key_now_[KEY_MAX];
		inline static BYTE key_prev_[KEY_MAX];

		static bool initialize();
		static bool update();
		static bool finalize();

	public:
		//====================================================================================================
		// static�֐�

		// �L�[����
		static bool isKeyDown(const KeyCode key_code);

		// �L�[�������ꂽ�u��
		static bool isKeyDownTrigger(const KeyCode key_code);

		// �L�[�������ꂽ�u��
		static bool isKeyReleaseTrigger(const KeyCode key_code);

		//====================================================================================================
	};

}
