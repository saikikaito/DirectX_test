#pragma once
#include <chrono>


namespace lib {

	class FPSControl final {
		// update���ĂԂ���
		friend class Library;
	private:
		// �����̋֎~
		FPSControl() = delete;
		FPSControl(const FPSControl&) = delete;
		FPSControl(const FPSControl&&) = delete;
		FPSControl& operator =(const FPSControl&) = delete;
		FPSControl& operator =(const FPSControl&&) = delete;

		//====================================================================================================
		// static�ϐ�

		inline static int fps_setting_ = 60;						// �ݒ肳�ꂽ���t���b�V�����[�g
		inline static std::chrono::system_clock::time_point start_;	// �R���g���[���O�̎���
		inline static std::chrono::system_clock::time_point end_;	// �R���g���[����̎���

		//====================================================================================================
		// static�֐�

		// �X�V
		static void update();

		//====================================================================================================
	public:
		//====================================================================================================

		// �Z�b�^�[
		inline static void setFPS(const int fps) { fps_setting_ = fps; }

		// �Q�b�^�[
		inline static int getFPSSetting() { return fps_setting_; }

		//====================================================================================================
	};

}
