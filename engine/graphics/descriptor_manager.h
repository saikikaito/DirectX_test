#pragma once
#include <wrl.h>
#include "../../system/d3dx12.h"
#include "../../library/library.h"
#include "descriptor_handle.h"


namespace eng {

	class DescriptorManager final : public lib::SmartFactory {
	private:
		template<class T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;
	public:
		using s_ptr = std::shared_ptr<DescriptorManager>;
		using w_ptr = std::weak_ptr<DescriptorManager>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		ComPtr<ID3D12DescriptorHeap> heap_;			// �f�B�X�N���v�^�q�[�v
		CD3DX12_CPU_DESCRIPTOR_HANDLE handle_cpu_;	// �m�ۂ��Ă���CPU�n���h��
		CD3DX12_GPU_DESCRIPTOR_HANDLE handle_gpu_;	// �m�ۂ��Ă���GPU�n���h��
		UINT index_ = 0;							// �m�ۂ�����
		UINT increment_size_ = 0;					// �Ǘ�����f�B�X�N���v�^1�̂̃T�C�Y
		std::list<DescriptorHandle> free_list_;		// �J�������n���h��

		//====================================================================================================
	public:
		DescriptorManager() {}
		~DescriptorManager() {}

		//====================================================================================================
		// �����o�֐�

		// �m��
		DescriptorHandle alloc();

		// �J��
		inline void free(const DescriptorHandle& handle) { free_list_.emplace_back(handle); }

		// �f�B�X�N���v�^�q�[�v�̎擾
		inline ComPtr<ID3D12DescriptorHeap> getHeap() const { return heap_; }

		//====================================================================================================
		// static�֐�

		// ����
		static DescriptorManager::s_ptr create(const D3D12_DESCRIPTOR_HEAP_DESC& desc);

		//====================================================================================================
	};

}
