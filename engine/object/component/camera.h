#pragma once
#include "../../../system/window.h"
#include "component.h"


namespace eng {

	class Camera : public Component {
	public:
		using s_ptr = std::shared_ptr<Camera>;
		using w_ptr = std::weak_ptr<Camera>;
	private:


	public:
		Camera() {}
		virtual ~Camera() {}

		//====================================================================================================
		// �����o�ϐ�

		float angle_ = 60.0f;						// ����p
		float aspect_ = sys::Window::ASPECT_RATIO;	// �A�X�y�N�g��
		float near_ = 3.0f;							// �ߋ����̉f��͈�
		float far_ = 10000.0f;						// �������̉f��͈�

		//====================================================================================================
		// �����o�֐�

		// �r���[�s��̎擾
		lib::Matrix4x4 getViewMatrix4x4() const;

		// �v���W�F�N�V�����s��̎擾
		lib::Matrix4x4 getProjectionMatrix4x4() const;

		//====================================================================================================
	};

}
