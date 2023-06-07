#include "graphics/graphics_manager.h"
#include "graphics/texture.h"
#include "scene.h"
#include "object/game_object.h"
#include "object/component/camera.h"
#include "object/component/renderer/renderer.h"	// addComponent�ł̃G���[�h�~


using namespace Microsoft::WRL;

namespace eng {

	bool Scene::onCreated() {

		// ���C���J�����̍쐬
		GameObject::s_ptr obj = GameObject::createEmpty("main_camera");
		camera_ = obj->addComponent<Camera>();
		obj->transform_->local_position_.set(0.0f, 0.0f, -20.0f);

		initialize();

		return true;
	}

	void Scene::update() {
		
		std::list<std::shared_ptr<GameObject>>::iterator it = game_objects_.begin();
		while (it != game_objects_.end()) {
			if (!(*it)->isAlive()) {
				(*it)->onDestroy();
				it = game_objects_.erase(it);
				continue;
			}
			if ((*it)->isActiveParent()) {
				if (!(*it)->is_enable_) {
					(*it)->onEnable();
					(*it)->is_enable_ = true;
				}
				(*it)->update();
			}
			else {
				if ((*it)->is_enable_) {
					(*it)->onDisable();
					(*it)->is_enable_ = false;
				}
			}
			++it;
		}

		lateUpdate();

	}

	void Scene::render() {

		GraphicsManager& mgr = GraphicsManager::getInstance();

		// �R�}���h�A���P�[�^�[�ƃR�}���h���X�g�̃��Z�b�g
		if (!mgr.resetCommandList()) {
			lib_DebugLog("ERROR: GraphicsManager::resetCommandList");
			return;
		}

		// �`��O�̏���
		// �r���[�|�[�g�̐ݒ�
		// PRESENT��RENDER_TERGET�֑J�ڂ̃o���A���͂�
		// �����_�[�^�[�Q�b�g�̐ݒ�
		// �����_�[�^�[�Q�b�g�Ɛ[�x�o�b�t�@�̃N���A
		mgr.renderBefore(sys::Window::VIEWPORT, sys::Window::SCISSOR_RECT, mgr.getMainRTV(), mgr.getMainDSV());

		// �R�}���h���X�g�֕`�揈�������ߍ���
		std::list<std::shared_ptr<GameObject>>::iterator it = game_objects_.begin();
		while (it != game_objects_.end()) {
			if ((*it)->isActiveParent()) {
				(*it)->render(camera_);
			}
			++it;
		}

		// RENDER_TERGET��PRESENT�֑J�ڂ̃o���A���͂�
		mgr.renderAfter(mgr.getMainRTV());

		// �R�}���h���X�g�ɂ��ߍ��܂ꂽ�`�揈�����ŏI�o��
		if (!mgr.executeCommandList()) {
			lib_DebugLog("ERROR: GraphicsManager::executeCommandList");
			return;
		}

		// �t���[�����ŏI�o��
		mgr.presentSwapChain();

	}

}
