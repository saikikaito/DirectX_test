#pragma once
#include <chrono>


namespace lib {

	class Time final {
		friend class Library;
	private:
		// �����̋֎~
		Time() = delete;
		Time(const Time&) = delete;
		Time(const Time&&) = delete;
		Time& operator =(const Time&) = delete;
		Time& operator =(const Time&&) = delete;

		//====================================================================================================
		// static�ϐ�

		inline static std::chrono::system_clock::time_point start_;	// �O��t���[���̎���
		inline static std::chrono::system_clock::time_point end_;	// ���݃t���[���̎���
		inline static float delta_time_ = 0.0f;						// 1�t���[��������̎���
		inline static float delta_time_avg_ = 0.0f;					// 1�t���[��������̎��Ԃ̕���
		inline static float elapsed_time_ = 0.0f;					// �Q�[�����N�����Ă���̌o�ߎ���
		inline static int fps_ = 0;									// 1�b������̃t���[����
		inline static int elapsed_frame_ = 0;						// �Q�[�����N�����Ă���̌o�߃t���[����

		//====================================================================================================
		// static�֐�

		// ������
		static void initialize();

		// �X�V
		static void update();

		//====================================================================================================
	public:
		//====================================================================================================
		// static�֐�

		// �Q�b�^�[
		inline static float getDeltaTime() { return delta_time_; }
		inline static float getDeltaTimeAvg() { return delta_time_avg_; }
		inline static float getElapsedTime() { return elapsed_time_; }
		inline static int getFPS() { return fps_; }
		inline static int getElapsedFrame() { return elapsed_frame_; }

		//====================================================================================================
	};

}
