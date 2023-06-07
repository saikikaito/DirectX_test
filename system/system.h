#pragma once
#include <windows.h>


namespace sys {

	class System final {
	private:
		System() {}
		~System() {}

	public:
		//====================================================================================================
		// static�ϐ�

		// ������
		static bool initialize(HINSTANCE h_instance);

		// �X�V
		static void update();

		// �I������
		static void finalize();

		//====================================================================================================
	};

}
