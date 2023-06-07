#pragma once
#include "object.h"
#include "../graphics/shape.h"
#include "../transform.h"


namespace eng {

	class Camera;
	class Component;
	class Renderer;

	class GameObject final : public Object {
		// �e��private�����o�ɃA�N�Z�X���邽��
		friend class Scene;
		// ���N���X�Ő������邽��
		friend class lib::SmartFactory;
	public:
		using s_ptr = std::shared_ptr<GameObject>;
		using w_ptr = std::weak_ptr<GameObject>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		bool is_enable_ = true;		// �֐��Ăяo���t���O
		std::list<std::shared_ptr<Component>> components_;	// ���ׂĂ�Component�Ǘ����X�g
		std::list<std::shared_ptr<Renderer>> renderers_;	// �`��Component�Ǘ����X�g

		//====================================================================================================
		// �����o�֐�

		// �R���X�g���N�^
		bool constructor() final override;

		// �폜��
		void onDestroy();

		// �L���ɂȂ�����
		void onEnable();

		// �����ɂȂ�����
		void onDisable();

		// �X�V
		void update();

		// �`��
		void render(std::shared_ptr<Camera> camera);

		//====================================================================================================
	public:
		GameObject() {}
		~GameObject() {}

		//====================================================================================================
		// �����o�ϐ�

		Transform<GameObject>::s_ptr transform_ = nullptr;	// �e�q�֌W

		//====================================================================================================
		// �����o�֐�

		// Component�̒ǉ�
		template<class T>
		inline std::shared_ptr<T> addComponent() {
			if (!std::is_base_of<Component, T>::value) return nullptr;
			std::shared_ptr<T> add = SmartFactory::createShared<T>();
			std::shared_ptr<Component> com = std::static_pointer_cast<Component>(add);
			com->game_object_ = shared_from_this<GameObject>();
			com->transform_ = transform_;
			if (!com->onCreated()) return nullptr;
			components_.emplace_back(com);
			if (std::is_base_of<Renderer, T>::value) renderers_.emplace_back(std::static_pointer_cast<Renderer>(com));
			return add;
		}

		// Component�̎擾
		template<class T>
		inline std::shared_ptr<T> getComponent(const int find_count = 0) {
			int count = 0;
			std::list<std::shared_ptr<Component>>::iterator it = components_.begin();
			while (it != components_.end()) {
				if (typeid(*(*it)) == typeid(T)) {
					if (count == find_count) return std::static_pointer_cast<T>((*it));
					++count;
				}
				++it;
			}
			return nullptr;
		}

		// ���g�̐e�̗L����Ԃ��ċA�I�Ɏ擾
		bool isActiveParent();

		// ���g�ɃA�^�b�`����Ă���Component�Ǝq�����ꏏ�ɍ폜
		void destroy();

		//====================================================================================================
		// static�֐�

		// ���GameObject�̐���
		static GameObject::s_ptr createEmpty(const std::string& name);
		// �l�p�`
		static GameObject::s_ptr createPlaneXY(const std::string& name, const Shape::CreateDesc& desc, const std::string& texture_file_path = "");
		static GameObject::s_ptr createPlaneYZ(const std::string& name, const Shape::CreateDesc& desc, const std::string& texture_file_path = "");
		static GameObject::s_ptr createPlaneZX(const std::string& name, const Shape::CreateDesc& desc, const std::string& texture_file_path = "");
		// �L���[�u
		static GameObject::s_ptr createCube(const std::string& name, const Shape::CreateDesc& desc, const std::string& texture_file_path = "");
		// ���ʂ��\�̃L���[�u
		static GameObject::s_ptr createInnerCube(const std::string& name, const Shape::CreateDesc& desc, const std::string& texture_file_path = "");
		// �񓙕ӎO�p�`
		static GameObject::s_ptr createTriangleIsosceles(const std::string& name, const Shape::CreateDesc& desc, const std::string& texture_file_path = "");
		// ���p�O�p�`
		static GameObject::s_ptr createTriangleRight(const std::string& name, const Shape::CreateDesc& desc, const std::string& texture_file_path = "");
		static GameObject::s_ptr createTriangleLeft(const std::string& name, const Shape::CreateDesc& desc, const std::string& texture_file_path = "");
		// ���O�p�`
		static GameObject::s_ptr createTriangleEquilateral(const std::string& name, const Shape::CreateDesc& desc, const std::string& texture_file_path = "");
		// ����
		static GameObject::s_ptr createSphere(const std::string& name, const Shape::CreateDesc& desc, const std::string& texture_file_path = "");
		// �h�[��
		static GameObject::s_ptr createDome(const std::string& name, const Shape::CreateDesc& desc, const std::string& texture_file_path = "");
		// ��ʂȂ��̉~��
		static GameObject::s_ptr createCone(const std::string& name, const Shape::CreateDesc& desc, const std::string& texture_file_path = "");
		// �~��
		static GameObject::s_ptr createDisk(const std::string& name, const Shape::CreateDesc& desc, const std::string& texture_file_path = "");
		// �~�Տ�̃����O 
		static GameObject::s_ptr createDiskRing(const std::string& name, const Shape::CreateDesc& desc, const std::string& texture_file_path = "");
		// �~��
		static GameObject::s_ptr createCylinder(const std::string& name, const Shape::CreateDesc& desc, const std::string& texture_file_path = "");

		//====================================================================================================
	};

}
