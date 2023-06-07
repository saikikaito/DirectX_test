#include "time.h"


namespace lib {

	void Time::initialize() {
		start_ = std::chrono::system_clock::now();
	}

	void Time::update() {
		// �t���[���Ԃ̌o�ߎ���
		// �}�C�N���b�Ōv�����ĕb�ɕϊ�
		end_ = std::chrono::system_clock::now();
		long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_).count();
		delta_time_ = static_cast<float>(microseconds / 1000.0 / 1000.0);
		start_ = end_;
		elapsed_time_ += delta_time_;
		++elapsed_frame_;
		delta_time_avg_ = elapsed_time_ / elapsed_frame_;
		fps_ = static_cast<int>(elapsed_frame_ / elapsed_time_);
	}

}
