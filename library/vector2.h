#pragma once
#include <DirectXMath.h>


namespace lib {

	class Vector3;

	class Vector2 final {
	public:
		Vector2() : x(0.0f), y(0.0f) {}
		Vector2(const float x, const float y) : x(x), y(y) {}
		Vector2(const DirectX::XMFLOAT2& v) : x(v.x), y(v.y) {}
		Vector2(const DirectX::XMVECTOR& v) : x(v.m128_f32[0]), y(v.m128_f32[1]) {}
		~Vector2() {}

		//====================================================================================================
		// �����o�ϐ�

		float x, y;

		//====================================================================================================
		// static�萔

		static const Vector2 ZERO;	// {  0,  0 }
		static const Vector2 ONE;	// {  1,  1 }
		static const Vector2 UP;	// {  0,  1 }
		static const Vector2 DOWN;	// {  0, -1 }
		static const Vector2 LEFT;	// { -1,  0 }
		static const Vector2 RIGHT;	// {  1,  0 }

		//====================================================================================================
		// �����o�֐�

		// �e�퉉�Z�q
		Vector2 operator +(const Vector2& other) const;
		Vector2& operator +=(const Vector2& other);
		Vector2 operator -() const;
		Vector2 operator -(const Vector2& other) const;
		Vector2& operator -=(const Vector2& other);
		Vector2 operator *(const Vector2& other) const;
		Vector2 operator *(const float other) const;
		Vector2& operator *=(const Vector2& other);
		Vector2& operator *=(const float other);
		Vector2 operator /(const Vector2& other) const;
		Vector2 operator /(const float other) const;
		Vector2& operator /=(const Vector2& other);
		Vector2& operator /=(const float other);
		bool operator ==(const Vector2& other) const;
		bool operator !=(const Vector2& other) const;
		operator Vector3() const;
		inline operator DirectX::XMFLOAT2() const { return DirectX::XMFLOAT2(x, y); }
		inline operator DirectX::XMVECTOR() const {
			DirectX::XMFLOAT2 v = *this;
			return DirectX::XMLoadFloat2(&v);
		}

		// �Z�b�g
		inline void set(const float x, const float y) { this->x = x; this->y = y; }

		// ����
		float length() const;

		// 2��̒���
		float sqrLength() const;

		//====================================================================================================
		// static�֐�

		// ���K��
		static Vector2 normalize(const Vector2& v);

		// �p�x
		static float angle(const Vector2& from, const Vector2& to);

		// ����
		static float dot(const Vector2& v1, const Vector2& v2);

		// �O��
		static float cross(const Vector2& v1, const Vector2& v2);

		// ����
		static float distance(const Vector2& v1, const Vector2& v2);

		//// �������ق��̗v�f�𔲂��o���ĐV�����x�N�g���𐶐�
		//static Vector2 min(const Vector2& v1, const Vector2& v2);

		//// �傫���ق��̗v�f�𔲂��o���ĐV�����x�N�g���𐶐�
		//static Vector2 max(const Vector2& v1, const Vector2& v2);

		//====================================================================================================
	};

}
