#pragma once
#include <cstdio>


namespace lib {

	class Debug final {
	private:
		// �����̋֎~
		Debug() = delete;
		Debug(const Debug&) = delete;
		Debug(const Debug&&) = delete;
		Debug& operator =(const Debug&) = delete;
		Debug& operator =(const Debug&&) = delete;

	public:
		//====================================================================================================
		// static�֐�

		// ������̏o��
		static void trace(const char* str, ...);

		//====================================================================================================
	};

#if _DEBUG
	// �f�o�b�O�o��(Release�ł͋@�\���Ȃ�)
	#define lib_DebugLog(str, ...) { \
		lib::Debug::trace("\n==================================================\n"); \
		char buff[256]; \
		sprintf_s(buff, str, __VA_ARGS__); \
		lib::Debug::trace("DebugLog: %s\n", buff); \
		lib::Debug::trace("File: %s\n", __FILE__); \
		lib::Debug::trace("Line: %d\n", __LINE__); \
		lib::Debug::trace("==================================================\n\n"); \
	}
#else
	// �f�o�b�O�o��(Release�ł͋@�\���Ȃ�)
	#define lib_DebugLog(str, ...) {}
#endif

}
