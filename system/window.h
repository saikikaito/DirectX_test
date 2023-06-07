#pragma once
#include <windows.h>
#include <d3d12.h>


namespace sys {

	class Window final {
		friend class System;
	private:
		Window() {}
		~Window() {}

		//====================================================================================================
		// static�֐�

		// �E�B���h�E�v���V�[�W��
		static LRESULT CALLBACK procedure(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

		// �E�B���h�E�̍쐬
		static HWND createWindow(HINSTANCE h_instance);

		//====================================================================================================
	public:
		//====================================================================================================
		// static�萔

		// ��
		inline static constexpr LONG WIDTH = 1280;

		// ����
		inline static constexpr LONG HEIGHT = 720;

		// �r���[�|�[�g
		// �I�t�X�N���[�������_�����O���g�p����ʕ�������ۂɌʂɕK�v�H
		inline static constexpr D3D12_VIEWPORT VIEWPORT = { 0.0f, 0.0f, (FLOAT)WIDTH, (FLOAT)HEIGHT, 0.0f, 1.0f };
		inline static constexpr D3D12_RECT SCISSOR_RECT = { 0, 0, WIDTH, HEIGHT };

		inline static constexpr float ASPECT_RATIO = (float)WIDTH / (float)HEIGHT;

		//====================================================================================================
		// static�ϐ�

		// �n���h��
		inline static HWND handle_ = 0;

		//====================================================================================================
		// static�֐�

		// �x�����b�Z�[�W�{�b�N�X�̕\��
		static void warningMessageBox(const LPCWSTR& message);

		//====================================================================================================
	};

}
