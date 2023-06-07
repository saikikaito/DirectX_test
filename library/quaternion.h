#pragma once
#include <DirectXMath.h>


namespace lib {

	class Vector3;
	class Matrix4x4;

	class Quaternion final {
	public:
		Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
		Quaternion(const float x, const float y, const float z, const float w) : x(x), y(y), z(z), w(w) {}
		Quaternion(const Vector3& v, const float w);
		Quaternion(const DirectX::XMFLOAT4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
		Quaternion(const DirectX::XMVECTOR& v) : x(v.m128_f32[0]), y(v.m128_f32[1]), z(v.m128_f32[2]), w(v.m128_f32[3]) {}
		~Quaternion() {}

		//====================================================================================================
		// �����o�ϐ�

		float x, y, z, w;

		//====================================================================================================
		// static�萔

		static const Quaternion IDENTITY;	// �P�ʉ�]

		//====================================================================================================
		// �����o�֐�

		// �e�퉉�Z�q
		Quaternion operator *(const Quaternion& other) const;
		Quaternion& operator *=(const Quaternion& other);
		inline operator DirectX::XMFLOAT4() const { return DirectX::XMFLOAT4(x, y, z, w); }
		inline operator DirectX::XMVECTOR() const {
			DirectX::XMFLOAT4 v = *this;
			return DirectX::XMLoadFloat4(&v);
		}

		// �I�C���[�p�ɕϊ�
		Vector3 getEulerAngle() const;

		// ��]�s��ɕϊ�
		Matrix4x4 getMatrix4x4() const;

		//====================================================================================================
		// static�֐�

		// �C�Ӊ�]���̃N�H�[�^�j�I�����쐬
		static Quaternion createRotationAxis(const Vector3& axis, const float angle);

		// �I�C���[�p����N�H�[�^�j�I�����쐬
		static Quaternion createEulerAngle(const float x, const float y, const float z);
		static Quaternion createEulerAngle(const Vector3& euler);

		// ��]�s�񂩂�N�H�[�^�j�I�����쐬
		static Quaternion createRotationMatrix4x4(const Matrix4x4& matrix);

		// �t�N�H�[�^�j�I�����쐬
		static Quaternion createInverse(const Quaternion& q);

		//====================================================================================================
	};

}
