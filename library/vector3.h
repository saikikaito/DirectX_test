#pragma once
#include <DirectXMath.h>


namespace lib {

	class Vector2;

	class Vector3 final {
	public:
		Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
		Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
		Vector3(const DirectX::XMFLOAT3& v) : x(v.x), y(v.y), z(v.z) {}
		Vector3(const DirectX::XMVECTOR& v) : x(v.m128_f32[0]), y(v.m128_f32[1]), z(v.m128_f32[2]) {}
		~Vector3() {}

		//====================================================================================================
		// �����o�ϐ�

		float x, y, z;

		//====================================================================================================
		// static�萔

		static const Vector3 ZERO;		// {  0,  0,  0 }
		static const Vector3 ONE;		// {  1,  1,  1 }
		static const Vector3 UP;		// {  0,  1,  0 }
		static const Vector3 DOWN;		// {  0, -1,  0 }
		static const Vector3 LEFT;		// { -1,  0,  0 }
		static const Vector3 RIGHT;		// {  1,  0,  0 }
		static const Vector3 FORWARD;	// {  0,  0,  1 }
		static const Vector3 BACK;		// {  0,  0, -1 }

		//====================================================================================================
		// �����o�֐�

		// �e�퉉�Z�q
		Vector3 operator +(const Vector3& other) const;
		Vector3& operator +=(const Vector3& other);
		Vector3 operator -() const;
		Vector3 operator -(const Vector3& other) const;
		Vector3& operator -=(const Vector3& other);
		Vector3 operator *(const Vector3& other) const;
		Vector3 operator *(const float other) const;
		Vector3& operator *=(const Vector3& other);
		Vector3& operator *=(const float other);
		Vector3 operator /(const Vector3& other) const;
		Vector3 operator /(const float other) const;
		Vector3& operator /=(const Vector3& other);
		Vector3& operator /=(const float other);
		bool operator ==(const Vector3& other) const;
		bool operator !=(const Vector3& other) const;
		operator Vector2() const;
		inline operator DirectX::XMFLOAT3() const { return DirectX::XMFLOAT3(x, y, z); }
		inline operator DirectX::XMVECTOR() const {
			DirectX::XMFLOAT3 v = *this;
			return DirectX::XMLoadFloat3(&v);
		}

		// �Z�b�g
		inline void set(const float x, const float y, const float z) { this->x = x; this->y = y; this->z = z; }

		// ����
		float length() const;

		// 2��̒���
		float sqrLength() const;

		//====================================================================================================
		// static�֐�

		// ���K��
		static Vector3 normalize(const Vector3& v);

		// �p�x
		static float angle(const Vector3& from, const Vector3& to);

		// ����
		static float dot(const Vector3& v1, const Vector3& v2);

		// �O��
		static Vector3 cross(const Vector3& v1, const Vector3& v2);

		// ����
		static float distance(const Vector3& v1, const Vector3& v2);

		//// �������ق��̗v�f�𔲂��o���ĐV�����x�N�g���𐶐�
		//static Vector3 min(const Vector3& v1, const Vector3& v2);

		//// �傫���ق��̗v�f�𔲂��o���ĐV�����x�N�g���𐶐�
		//static Vector3 max(const Vector3& v1, const Vector3& v2);

		//====================================================================================================
	};

}
