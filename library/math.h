#pragma once


namespace lib {

	class Math final {
	private:
		// �����̋֎~
		Math() = delete;
		Math(const Math&) = delete;
		Math(const Math&&) = delete;
		Math& operator =(const Math&) = delete;
		Math& operator =(const Math&&) = delete;

	public:
		//====================================================================================================
		// static�萔

		inline static const float PI = 3.1415965352f;	// �~����

		//====================================================================================================
		// static�֐�

		// ���W�A������x�֕ϊ�
		inline static float toDegree(const float radian) { return radian * 180 / PI; }

		// �x���烉�W�A���֕ϊ�
		inline static float toRadian(const float degree) { return degree * PI / 180; }

		//====================================================================================================
	};

}
