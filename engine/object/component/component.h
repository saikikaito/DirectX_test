#pragma once
#include "../game_object.h"


namespace eng {

	class Component : public Object {
		// �e��protected�֐��ɃA�N�Z�X���邽��
		friend class GameObject;
	public:
		using s_ptr = std::shared_ptr<Component>;
		using w_ptr = std::weak_ptr<Component>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		bool is_start_ = true;						// start�֐��Ăяo���t���O
		bool is_enable_ = true;						// onEnable, onDisable�֐��Ăяo���t���O
		GameObject::w_ptr game_object_;				// ���g���A�^�b�`����Ă���GameObject
		Transform<GameObject>::w_ptr transform_;	// GameObject��Transform

		//====================================================================================================
	protected:
		//====================================================================================================
		// �����o�֐�

		// ������
		virtual bool onCreated() { return true; }

		// �폜��
		virtual void onDestroy() {}

		// �L���ɂȂ�����
		virtual void onEnable() {}

		// �����ɂȂ�����
		virtual void onDisable() {}

		// �J�n��
		virtual void start() {}

		// �X�V
		virtual void update() {}

		//====================================================================================================
	public:
		Component() {}
		virtual ~Component() {}

		//====================================================================================================
		// �����o�֐�

		// �A�^�b�`����Ă���GameObject�̎擾
		inline GameObject::s_ptr getGameObject() const { return (game_object_.expired()) ? nullptr : game_object_.lock(); }

		// GameObject��Transform�̎擾
		inline Transform<GameObject>::s_ptr getTransform() const { return (transform_.expired()) ? nullptr : transform_.lock(); }

		// Component�̒ǉ�
		template<class T>
		inline std::shared_ptr<T> addComponent() { return getGameObject()->addComponent<T>(); }

		// Component�̎擾
		template<class T>
		inline std::shared_ptr<T> getComponent() { return getGameObject()->getComponent<T>(); }

		//====================================================================================================
	};

}
