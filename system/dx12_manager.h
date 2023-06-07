#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include "../library/singleton.h"
#include "../engine/graphics/graphics_manager.h"


namespace sys {

	class Dx12Manager final : public lib::Singleton<Dx12Manager> {
		// ���N���X�Ő������邽��
		friend class lib::Singleton<Dx12Manager>;
		// initialize, finalize���ĂԂ���
		friend class System;
		// �e��private�����o�ɃA�N�Z�X���邽��
		friend class eng::GraphicsManager;
	private:
		template<class T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;
	private:
		Dx12Manager() {}

		//====================================================================================================
		// �����o�ϐ�

		ComPtr<IDXGIFactory4> factory_;	// �n�[�h�E�F�A�A�_�v�^
		ComPtr<ID3D12Device> device_;	// �f�o�C�X
		HANDLE fence_event_ = nullptr;	// �t�F���X�C�x���g
		ComPtr<ID3D12Fence> fence_;		// �t�F���X
		UINT64 fence_value_ = 0;

		//====================================================================================================
		// �����o�֐�

		// ������
		bool initialize();

		// �I������
		void finalize();

		//====================================================================================================
	public:
		~Dx12Manager() {}

		//====================================================================================================
		// �����o�ϐ�

		inline ComPtr<ID3D12Device> getDevice() const { return device_; }

		//====================================================================================================
	};

}
