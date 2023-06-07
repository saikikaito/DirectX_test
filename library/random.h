#pragma once
#include <stdint.h>
#include <stdlib.h>


namespace lib {

	class Random final {
	private:
		// �����̋֎~
		Random() = delete;
		Random(const Random&) = delete;
		Random(const Random&&) = delete;
		Random& operator =(const Random&) = delete;
		Random& operator =(const Random&&) = delete;

		//====================================================================================================
		// static�ϐ�

		inline static uint32_t seed_ = 0;	// �����V�[�h�l

		//====================================================================================================
	public:
		//====================================================================================================
		// static�֐�

		// �V�[�h�l�̐ݒ�
		inline static void setSeed(const uint32_t seed) { seed_ = seed; srand(seed_); }

		// �V�[�h�l�̎擾
		inline static uint32_t getSeed() { return seed_; }

		// �͈͓��̗������擾
		template<class T>
		inline static T range(T min, T max) {
			return min + static_cast<T>((rand()) / (static_cast<T>(RAND_MAX / (max - min))));
		}

		//====================================================================================================
	};

}
