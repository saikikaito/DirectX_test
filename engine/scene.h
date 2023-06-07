#pragma once
#include "../library/library.h"


namespace eng {

	class Camera;
	class GameObject;

	class Scene : public lib::SmartFactory {
		// update, render���ĂԂ���
		friend class Engine;
		// �o�^���邽��
		friend class GameObject;
	public:
		using s_ptr = std::shared_ptr<Scene>;
		using w_ptr = std::weak_ptr<Scene>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		// GameObject�ꊇ�Ǘ����X�g
		std::list<std::shared_ptr<GameObject>> game_objects_;

		//====================================================================================================
		// �����o�֐�

		// ������
		bool onCreated();

		// �X�V
		void update();

		// �`��
		void render();

		//====================================================================================================
	protected:
		//====================================================================================================
		// �����o�֐�

		// ������
		virtual bool initialize() = 0;

		// GameObject�̍X�V��ɌĂ΂��X�V
		virtual void lateUpdate() {}

		// �I������
		virtual void finalize() {}

		//====================================================================================================
	public:
		Scene() {}
		virtual ~Scene() {}

		//====================================================================================================
		// �����o�ϐ�

		std::shared_ptr<Camera> camera_ = nullptr;	// �J����

		//====================================================================================================
	};

}
