#pragma once
#include "../library/library.h"


namespace eng {

	template<class T>
	class Transform final : public lib::LinkTree<Transform<T>> {
	public:
		using s_ptr = std::shared_ptr<Transform<T>>;
		using w_ptr = std::weak_ptr<Transform<T>>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		std::weak_ptr<T> included_;		// ��܂���Ă���N���X

		//====================================================================================================
	public:
		Transform() {}
		~Transform() {}

		//====================================================================================================
		// �����o�ϐ�

		lib::Vector3 local_position_ = lib::Vector3::ZERO;				// ���[�J�����W
		lib::Quaternion local_rotation_ = lib::Quaternion::IDENTITY;	// ���[�J����]
		lib::Vector3 local_scale_ = lib::Vector3::ONE;					// ���[�J���g�嗦

		//====================================================================================================
		// �����o�֐�

		// ��܂���Ă���N���X�̎擾
		inline std::shared_ptr<T> getIncluded() const { return (included_.expired()) ? nullptr : included_.lock(); }

		// �q�ɒǉ�
		inline void pushChild(Transform<T>::s_ptr child) {
			if (lib::LinkTree<Transform<T>>::isExist(child)) return;
			child->popParent();
			lib::LinkTree<Transform<T>>::pushChild(child);
			lib::Quaternion iq = lib::Quaternion::createInverse(local_rotation_);
			lib::Quaternion pq = iq * lib::Quaternion(child->local_position_ - local_position_, 0.0f) * local_rotation_;
			child->local_position_ = lib::Vector3(pq.x, pq.y, pq.z) / local_scale_;
			child->local_rotation_ *= iq;
			child->local_scale_ /= local_scale_;
		}

		// �e���痣�E
		inline void popParent() {
			if (!lib::LinkTree<Transform<T>>::getParent()) return;
			local_position_ = getPosition();
			local_rotation_ = getRotation();
			local_scale_ = getScale();
			lib::LinkTree<Transform<T>>::pop();
		}

		// �o�O��������ۂ��̂Ŏg�p�֎~
#if 0
		// ���[���h���W�̐ݒ�
		inline void setPosition(const float x, const float y, const float z) { setPosition(lib::Vector3(x, y, z)); }
		inline void setPosition(const lib::Vector3& position) {
			Transform<T>::s_ptr p = lib::LinkTree<Transform<T>>::getParent();
			if (!p) {
				local_position_ = position;
				return;
			}
			lib::Quaternion iq = lib::Quaternion::createInverse(p->local_rotation_);
			lib::Quaternion pq = iq * lib::Quaternion(position - p->getPosition(), 0.0f) * p->local_rotation_;
			local_position_ = lib::Vector3(pq.x, pq.y, pq.z) / p->local_scale_;
		}

		// ���[���h��]�̐ݒ�
		inline void setRotation(const lib::Quaternion& rotation) {
			Transform<T>::s_ptr p = lib::LinkTree<Transform<T>>::getParent();
			local_rotation_ = (p) ? rotation * lib::Quaternion::createInverse(p->getRotation()) : rotation;
		}

		// ���[���h�g�嗦�̐ݒ�
		inline void setScale(const float x, const float y, const float z) { setScale(lib::Vector3(x, y, z)); }
		inline void setScale(const lib::Vector3& scale) {
			Transform<T>::s_ptr p = lib::LinkTree<Transform<T>>::getParent();
			local_scale_ = (p) ? scale / p->getScale() : scale;
		}
#endif

		// ���[���h���W�n�ł̉E�����P�ʃx�N�g��
		inline lib::Vector3 getRight() const {
			lib::Matrix4x4 wm = getWorldMatrix4x4();
			return lib::Vector3::normalize(lib::Vector3(wm._11, wm._12, wm._13));
		}

		// ���[���h���W�n�ł̏�����P�ʃx�N�g��
		inline lib::Vector3 getUp() const {
			lib::Matrix4x4 wm = getWorldMatrix4x4();
			return lib::Vector3::normalize(lib::Vector3(wm._21, wm._22, wm._23));
		}

		// ���[���h���W�n�ł̑O�����P�ʃx�N�g��
		inline lib::Vector3 getForward() const {
			lib::Matrix4x4 wm = getWorldMatrix4x4();
			return lib::Vector3::normalize(lib::Vector3(wm._31, wm._32, wm._33));
		}

		// ���[���h���W�̎擾
		inline lib::Vector3 getPosition() const {
			lib::Matrix4x4 wm = getWorldMatrix4x4();
			return lib::Vector3(wm._41, wm._42, wm._43);
		}

		// ���[���h��]�̎擾(�N�H�[�^�j�I��)
		inline lib::Quaternion getRotation() const {
			Transform<T>::s_ptr p = lib::LinkTree<Transform<T>>::getParent();
			return (p) ? p->getRotation() * local_rotation_ : local_rotation_;
		}

		// ���[���h��]�̎擾(�I�C���[�p)
		inline lib::Vector3 getEulerAngle() const {
			return getRotation().getEulerAngle();
		}

		// ���[���h�g�嗦�̎擾
		inline lib::Vector3 getScale() const {
			Transform<T>::s_ptr p = lib::LinkTree<Transform<T>>::getParent();
			return (p) ? local_scale_ * p->getScale() : local_scale_;
		}

		// ���[���h�s��̎擾
		inline lib::Matrix4x4 getWorldMatrix4x4() const {
			lib::Matrix4x4 rm = local_rotation_.getMatrix4x4();
			lib::Matrix4x4 wm = lib::Matrix4x4(
				local_scale_.x * rm._11,
				local_scale_.x * rm._12,
				local_scale_.x * rm._13,
				0.0f,

				local_scale_.y * rm._21,
				local_scale_.y * rm._22,
				local_scale_.y * rm._23,
				0.0f,

				local_scale_.z * rm._31,
				local_scale_.z * rm._32,
				local_scale_.z * rm._33,
				0.0f,

				local_position_.x,
				local_position_.y,
				local_position_.z,
				1.0f
			);

			Transform<T>::s_ptr p = lib::LinkTree<Transform<T>>::getParent();
			return (p) ? wm * p->getWorldMatrix4x4() : wm;
		}

		// ���s�ړ�
		inline void translate(const float x, const float y, const float z) {
			lib::Matrix4x4 rm = local_rotation_.getMatrix4x4();
			float ox = (x * rm._11) + (y * rm._21) + (z * rm._31);
			float oy = (x * rm._12) + (y * rm._22) + (z * rm._32);
			float oz = (x * rm._13) + (y * rm._23) + (z * rm._33);
			local_position_ += lib::Vector3(ox, oy, oz);
		}
		inline void translate(const lib::Vector3& vector) {
			translate(vector.x, vector.y, vector.z);
		}
		inline void translateWorld(const float x, const float y, const float z) {
			local_position_ += lib::Vector3(x, y, z);
		}
		inline void translateWorld(const lib::Vector3& vector) {
			local_position_ += vector;
		}

		// ��]
		inline void rotate(const lib::Vector3& axis, const float angle) {
			local_rotation_ *= lib::Quaternion::createRotationAxis(axis, angle);
		}
		inline void rotate(const float x, const float y, const float z) {
			local_rotation_ *= lib::Quaternion::createEulerAngle(x, y, z);
		}
		inline void rotate(const lib::Vector3& euler) {
			local_rotation_ *= lib::Quaternion::createEulerAngle(euler);
		}

		// target�̕�������
		// ����: ���[�g�I�u�W�F�N�g�ɂ̂ݗL��
		inline void lookAt(const float x, const float y, const float z, const lib::Vector3& up = lib::Vector3::UP) { lookAt(lib::Vector3(x, y, z), up); }
		inline void lookAt(const lib::Vector3& target, const lib::Vector3& up = lib::Vector3::UP) {
			lib::Vector3 z = lib::Vector3::normalize(target - getPosition());
			lib::Vector3 x = lib::Vector3::normalize(lib::Vector3::cross(up, z));
			lib::Vector3 y = lib::Vector3::normalize(lib::Vector3::cross(z, x));

			lib::Matrix4x4 rm = lib::Matrix4x4(
				x.x,  x.y,  x.z,  0.0f,
				y.x,  y.y,  y.z,  0.0f,
				z.x,  z.y,  z.z,  0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			);

			local_rotation_ = lib::Quaternion::createRotationMatrix4x4(rm);
		}

		//====================================================================================================
		// static�֐�

		// ����
		inline static Transform<T>::s_ptr create(std::shared_ptr<T> parent) {
			Transform<T>::s_ptr ptr = lib::SmartFactory::createShared<Transform<T>>();
			ptr->included_ = parent;
			return ptr;
		}

		//====================================================================================================
	};

}
