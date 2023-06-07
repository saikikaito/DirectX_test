#include "system.h"


// �G���g���[�|�C���g
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd) {

	// ������
	if (!sys::System::initialize(hInstance)) return 0;

	// ���b�Z�[�W���[�v
	MSG	msg;
	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) break;
			
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	// �I������
	sys::System::finalize();

	return 0;
}
