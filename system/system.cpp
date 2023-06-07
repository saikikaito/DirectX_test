#include "system.h"
#include "window.h"
#include "dx12_manager.h"
#include "../library/library.h"
#include "../engine/graphics/graphics_manager.h"
#include "../engine/engine.h"


namespace sys {

	bool System::initialize(HINSTANCE h_instance) {

		// �E�B���h�E�̍쐬
		if (!sys::Window::createWindow(h_instance)) {
			sys::Window::warningMessageBox(L"�E�B���h�E�̍쐬�Ɏ��s���܂����B");
			return false;
		}

		// DirectX12�̏�����
		if (!sys::Dx12Manager::getInstance().initialize()) {
			sys::Window::warningMessageBox(L"DirectX12�̏������Ɏ��s���܂����B");
			return false;
		}
			
		// �`��ݒ�̏�����
		if (!eng::GraphicsManager::getInstance().initialize()) {
			sys::Window::warningMessageBox(L"�`��ݒ�̏������Ɏ��s���܂����B");
			return false;
		}

		// ���C�u�����̏�����
		if (!lib::Library::initialize()) {
			sys::Window::warningMessageBox(L"���C�u�����̏������Ɏ��s���܂����B");
			return false;
		}
			
		// �G���W���̏�����
		if (!eng::Engine::getInstance().initialize()) {
			sys::Window::warningMessageBox(L"�G���W���̏������Ɏ��s���܂����B");
			return false;
		}

		// �E�B���h�E�̕\��
		ShowWindow(sys::Window::handle_, SW_SHOW);

		return true;
	}

	void System::update() {

		// ���C�u�����̍X�V
		lib::Library::update();

		// �G���W���̍X�V
		eng::Engine::getInstance().update();

		// �`�抮���̓���
		eng::GraphicsManager& mgr = eng::GraphicsManager::getInstance();
		mgr.waitForPreviousFrame();
		mgr.frame_index_ = mgr.swap_chain_->GetCurrentBackBufferIndex();

	}
	
	void System::finalize() {

		// �G���W���̏I������
		eng::Engine::getInstance().finalize();

		// ���C�u�����̏I������
		lib::Library::finalize();

		// �`��̏I������
		eng::GraphicsManager::getInstance().finalize();

		// DirectX12�̏I������
		sys::Dx12Manager::getInstance().finalize();
	}

}
