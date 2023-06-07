#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include "../../system/system.h"
#include "../../library/library.h"


namespace eng {

	class DescriptorManager;
	class RenderTargetView;
	class DepthStencilView;
	class PipelineState;
	class Shader;
	class Texture;

	class GraphicsManager final : public lib::Singleton<GraphicsManager> {
		// ���N���X�Ő������邽��
		friend class lib::Singleton<GraphicsManager>;
		// initialize, finalize���ĂԂ���
		friend class sys::System;
		// resetCommandList, renderBefore, renderAfter, executeCommandList���ĂԂ���
		friend class Scene;
	private:
		template<class T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;
	private:
		GraphicsManager() {}

		//====================================================================================================
		// static�萔

		inline static constexpr UINT FRAME_COUNT = 2;				// �t���[����
		inline static constexpr UINT DESCRIPTOR_RTV_NUM = 100;		// �����_�[�^�[�Q�b�g�r���[
		inline static constexpr UINT DESCRIPTOR_DSV_NUM = 100;		// �[�x�X�e���V���r���[
		inline static constexpr UINT DESCRIPTOR_SRV_NUM = 2048;		// �V�F�[�_�[���\�[�X�r���[

		//====================================================================================================
		// �����o�ϐ�

		UINT frame_index_ = 0;								// ���݂̕`��t���[��
		ComPtr<ID3D12CommandQueue> command_queue_;			// �R�}���h�L���[
		ComPtr<ID3D12CommandAllocator> command_allocator_;	// �R�}���h�A���P�[�^�[
		ComPtr<ID3D12GraphicsCommandList> command_list_;	// �R�}���h���X�g
		ComPtr<IDXGISwapChain3> swap_chain_;				// �X���b�v�`�F�C��

		std::shared_ptr<PipelineState> default_pso_ = nullptr;	// �f�t�H���g��PSO
		std::shared_ptr<Shader> default_shader_ = nullptr;		// �f�t�H���g�̃V�F�[�_
		std::shared_ptr<Texture> default_texture_ = nullptr;	// �f�t�H���g�̃e�N�X�`��

		//--------------------------------------------------
		// Layer�ɓ�������H

		std::shared_ptr<RenderTargetView> rtv_[FRAME_COUNT] = {};	// �����_�[�^�[�Q�b�g�r���[
		std::shared_ptr<DepthStencilView> dsv_ = nullptr;			// �[�x�X�e���V���r���[

		//--------------------------------------------------

		std::shared_ptr<DescriptorManager> rtv_heap_ = nullptr;	// �����_�[�^�[�Q�b�g�r���[�̃f�B�X�N���v�^�q�[�v
		std::shared_ptr<DescriptorManager> dsv_heap_ = nullptr;	// �[�x�X�e���V���r���[�̃f�B�X�N���v�^�q�[�v
		std::shared_ptr<DescriptorManager> srv_heap_ = nullptr;	// �V�F�[�_�[���\�[�X�r���[�̃f�B�X�N���v�^�q�[�v

		//====================================================================================================
		// �����o�֐�

		// ������
		bool initialize();

		// �I������
		void finalize();

		// �`�抮���̓��������
		bool waitForPreviousFrame();

		// �R�}���h���X�g�ƃR�}���h�A���P�[�^�[�����Z�b�g
		bool resetCommandList();

		// �o���A��\��
		void setResourceBarrier(ID3D12Resource* rtv, const D3D12_RESOURCE_STATES state_before, const D3D12_RESOURCE_STATES state_after);

		// �`��O�̏���
		void renderBefore(const D3D12_VIEWPORT& viewport, const D3D12_RECT& scissor_rect, const std::shared_ptr<RenderTargetView>& rtv, const std::shared_ptr<DepthStencilView>& dsv);

		// �`���̏���
		void renderAfter(const std::shared_ptr<RenderTargetView>& rtv);

		// �R�}���h���X�g�����s���`��
		bool executeCommandList();

		// �t���[�����ŏI�o��
		bool presentSwapChain();

		//====================================================================================================
	public:
		~GraphicsManager() {}
		
		//====================================================================================================
		// �����o�ϐ�

		// �Q�b�^�[
		inline ComPtr<ID3D12GraphicsCommandList> getCommandList() const { return command_list_; }

		inline std::shared_ptr<PipelineState> getDefaultPSO() const { return default_pso_; }
		inline std::shared_ptr<Shader> getDefaultShader() const { return default_shader_; }
		inline std::shared_ptr<Texture> getDefaultTexture() const { return default_texture_; }
		
		inline std::shared_ptr<RenderTargetView> getMainRTV() const { return rtv_[frame_index_]; }
		inline std::shared_ptr<DepthStencilView> getMainDSV() const { return dsv_; }

		inline std::shared_ptr<DescriptorManager> getRTVHeap() const { return rtv_heap_; }
		inline std::shared_ptr<DescriptorManager> getDSVHeap() const { return dsv_heap_; }
		inline std::shared_ptr<DescriptorManager> getSRVHeap() const { return srv_heap_; }

		//====================================================================================================
	};

}
