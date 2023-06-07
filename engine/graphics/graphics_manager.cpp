#include "../../system/dx12_manager.h"
#include "../../system/window.h"
#include "graphics_manager.h"
#include "descriptor_manager.h"
#include "render_target_view.h"
#include "depth_stencil_view.h"
#include "pipeline_state.h"
#include "shader.h"
#include "texture.h"


namespace eng {

	bool GraphicsManager::initialize() {

		sys::Dx12Manager& mgr = sys::Dx12Manager::getInstance();

		/* �R�}���h�L���[�̍쐬 */ {

			// �`�掞�ɂ̓R�}���h�L���[�ɒ~����ꂽ�R�}���h���X�g�����s�����
			D3D12_COMMAND_QUEUE_DESC queue_desc = {};
			queue_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;	// �Q�[���J���Ȃ炱���̃t���O�� NONE �ł悢�炵��
			queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;	// ���̃t���O�Ƃ��Ă̓R���s���[�g�V�F�[�_��p�̃t���O������
			if (FAILED(mgr.device_->CreateCommandQueue(&queue_desc, IID_PPV_ARGS(&command_queue_)))) return false;
		}

		/* �X���b�v�`�F�C���̍쐬 */ {

			DXGI_SWAP_CHAIN_DESC1	swap_chain_desc = {};
			swap_chain_desc.BufferCount = FRAME_COUNT;
			swap_chain_desc.Width = sys::Window::WIDTH;
			swap_chain_desc.Height = sys::Window::HEIGHT;
			swap_chain_desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
			swap_chain_desc.SampleDesc.Count = 1;

			ComPtr<IDXGISwapChain1>	swap_chain;
			if (FAILED(mgr.factory_->CreateSwapChainForHwnd(command_queue_.Get(), sys::Window::handle_, &swap_chain_desc, nullptr, nullptr, &swap_chain))) return false;

			// �t���X�N���[���̃T�|�[�g�Ȃ�
			if (FAILED(mgr.factory_->MakeWindowAssociation(sys::Window::handle_, DXGI_MWA_NO_ALT_ENTER))) return false;

			if (FAILED(swap_chain.As(&swap_chain_))) return false;
			frame_index_ = swap_chain_->GetCurrentBackBufferIndex();
		}

		/* �����_�[�^�[�Q�b�g�r���[�̍쐬 */ {

			// DirectX12�ł͗l�X�ȃo�b�t�@�� DescriptorHeap �Ƃ��Ĉ��� 
			// ( dx11 �ł�RenderTargetView �� ShaderResourceView ��������ɂȂ� )

			// DescriptorHeap �����̃o�b�t�@�Ȃ̂���\���^
			D3D12_DESCRIPTOR_HEAP_DESC	rtv_heap_desc = {
				D3D12_DESCRIPTOR_HEAP_TYPE_RTV,		// �����_�[�^�[�Q�b�g�r���[
				DESCRIPTOR_RTV_NUM,					// ���߂Ɋm�ۂ��Ă���
				D3D12_DESCRIPTOR_HEAP_FLAG_NONE,	// �V�F�[�_�̌��ʂ����\�[�X�Ƃ��Ďg�p����ꍇ�͕ύX����H
				0
			};
			rtv_heap_ = DescriptorManager::create(rtv_heap_desc);
			for (UINT i = 0; i < FRAME_COUNT; i++) {
				rtv_[i] = RenderTargetView::create(lib::Color(0.0f, 0.2f, 0.4f, 1.0f), sys::Window::WIDTH, sys::Window::HEIGHT);
				if (FAILED(swap_chain_->GetBuffer(i, IID_PPV_ARGS(&rtv_[i]->getBuffer())))) return FALSE;
				mgr.device_->CreateRenderTargetView(rtv_[i]->getBuffer().Get(), nullptr, rtv_[i]->getHandle().getCpuHandle());
			}
		}

		/* �[�x�X�e���V���r���[�̍쐬 */ {

			//�[�x�o�b�t�@�p�̃f�X�N���v�^�q�[�v�̍쐬
			D3D12_DESCRIPTOR_HEAP_DESC dsv_heap_desc = {
				D3D12_DESCRIPTOR_HEAP_TYPE_DSV,
				DESCRIPTOR_DSV_NUM,					// ���߂Ɋm�ۂ��Ă���
				D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
				0
			};
			dsv_heap_ = DescriptorManager::create(dsv_heap_desc);
			dsv_ = DepthStencilView::create(sys::Window::WIDTH, sys::Window::HEIGHT);
		}

		/* �R�}���h�A���P�[�^�[�̍쐬 */ {

			// �R�}���h�A���P�[�^�̓R�}���h�L���[�ɃR�}���h���X�g�̓��e��ςވׂ̃R���e�i�̂悤�Ȗ���������
			// ������ D3D12_COMMAND_LIST_TYPE_DIRECT �̓R�}���h�L���[�ƍ��킹��K�v������
			if (FAILED(mgr.device_->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&command_allocator_)))) return false;
		}

		/* ���[�g�V�O�l�`���ƃV�F�[�_�[�̍쐬 */ {

			// ���[�g�V�O�l�`���� �V�F�[�_�Ŏg�p�����萔�o�b�t�@�E�e�N�X�`���E�T���v���Ȃǂ�
			// �V�F�[�_���̉����ɂǂ�Ȍ`���ő��݂��邩��`����悤�Ȃ���
			// �V�F�[�_���W�X�^�� b0 �͂���� t0 �͂���łƂ������ׂ����ݒ肪�\�Ȃ悤��
			eng::Shader::CreateDesc shader_desc;
			shader_desc.vertex_shader_name = "VSMain";
			shader_desc.vertex_target = "vs_5_0";
			shader_desc.pixel_shader_name = "PSMain";
			shader_desc.pixel_target = "ps_5_0";
			shader_desc.input_element_desc = new D3D12_INPUT_ELEMENT_DESC[]{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
				{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
				{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,	 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}
			};
			shader_desc.input_element_size = 3;

			D3D12_DESCRIPTOR_RANGE range[1] = {};
			D3D12_ROOT_PARAMETER root_parameters[2] = {};
			D3D12_STATIC_SAMPLER_DESC sampler_desc[1] = {};

			//�ϊ��s��p�̒萔�o�b�t�@	
			root_parameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
			root_parameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			root_parameters[0].Descriptor.ShaderRegister = 0;
			root_parameters[0].Descriptor.RegisterSpace = 0;

			//���C�g�p�̒萔�o�b�t�@
			//root_parameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
			//root_parameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			//root_parameters[1].Descriptor.ShaderRegister = 1;
			//root_parameters[1].Descriptor.RegisterSpace = 0;

			//�e�N�X�`��
			range[0].NumDescriptors = 1;
			range[0].BaseShaderRegister = 0;
			range[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
			range[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

			root_parameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			root_parameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			root_parameters[1].DescriptorTable.NumDescriptorRanges = 1;
			root_parameters[1].DescriptorTable.pDescriptorRanges = &range[0];

			//�T���v��
			sampler_desc[0].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
			sampler_desc[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			sampler_desc[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			sampler_desc[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			sampler_desc[0].MipLODBias = 0.0f;
			sampler_desc[0].MaxAnisotropy = 16;
			sampler_desc[0].ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
			sampler_desc[0].BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
			sampler_desc[0].MinLOD = 0.0f;
			sampler_desc[0].MaxLOD = D3D12_FLOAT32_MAX;
			sampler_desc[0].ShaderRegister = 0;
			sampler_desc[0].RegisterSpace = 0;
			sampler_desc[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

			shader_desc.root_signature_desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
			shader_desc.root_signature_desc.NumParameters = _countof(root_parameters);
			shader_desc.root_signature_desc.pParameters = root_parameters;
			shader_desc.root_signature_desc.NumStaticSamplers = _countof(sampler_desc);
			shader_desc.root_signature_desc.pStaticSamplers = sampler_desc;

			default_shader_ = eng::Shader::create(shader_desc);
			if (!default_shader_) return false;
		}

		/* �p�C�v���C���X�e�[�g�I�u�W�F�N�g(PSO)�̍쐬 */ {

			// dx11 �ł͌ʂɃC�~�f�B�G�C�g�R���e�L�X�g( dx12 �ł͔p�~ ) ���g���Đݒ肵�Ă����p�C�v���C���X�e�[�g�� dx12 �ł͂P�ɂ܂Ƃ߂�ꂽ
			// �e��V�F�[�_�E���X�^���C�U�E�u�����h�X�e�[�g�E�f�v�X�X�e���V���X�e�[�g��
			// ���̂��߂����̐ݒ��ς����`����s�������ꍇ�� PSO �𕡐����ǂ���g���ĕ`�悷�邩�Ǘ�����K�v������
			eng::PipelineState::CreateDesc pso_desc;
			pso_desc.shader = default_shader_;

			// �O���t�B�b�N�X�p�C�v���C���̏�ԃI�u�W�F�N�g���쐬
				//�V�F�[�_�[�̐ݒ�
			pso_desc.pso_desc.VS.pShaderBytecode = default_shader_->getVertexShader()->GetBufferPointer();
			pso_desc.pso_desc.VS.BytecodeLength = default_shader_->getVertexShader()->GetBufferSize();
			pso_desc.pso_desc.PS.pShaderBytecode = default_shader_->getPixelShader()->GetBufferPointer();
			pso_desc.pso_desc.PS.BytecodeLength = default_shader_->getPixelShader()->GetBufferSize();

			//�C���v�b�g���C�A�E�g�̐ݒ�
			pso_desc.pso_desc.InputLayout.pInputElementDescs = default_shader_->getInputElementDesc();
			pso_desc.pso_desc.InputLayout.NumElements = default_shader_->getInputElementSize();

			//�T���v���n�̐ݒ�
			pso_desc.pso_desc.SampleDesc.Count = 1;
			pso_desc.pso_desc.SampleDesc.Quality = 0;
			pso_desc.pso_desc.SampleMask = UINT_MAX;

			//�����_�[�^�[�Q�b�g�̐ݒ�
			pso_desc.pso_desc.NumRenderTargets = 1;
			pso_desc.pso_desc.RTVFormats[0] = DXGI_FORMAT_B8G8R8A8_UNORM;

			//�O�p�`�ɐݒ�
			pso_desc.pso_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

			//���[�g�V�O�l�`��
			pso_desc.pso_desc.pRootSignature = default_shader_->getRootSignature().Get();

			//���X�^���C�U�X�e�[�g�̐ݒ�
			pso_desc.pso_desc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
			//pso_desc.pso_desc.RasterizerState.CullMode = D3D12_CULL_MODE_FRONT;
			//pso_desc.pso_desc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
			pso_desc.pso_desc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
			//pso_desc.pso_desc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;
			pso_desc.pso_desc.RasterizerState.FrontCounterClockwise = FALSE;
			pso_desc.pso_desc.RasterizerState.DepthBias = 0;
			pso_desc.pso_desc.RasterizerState.DepthBiasClamp = 0;
			pso_desc.pso_desc.RasterizerState.SlopeScaledDepthBias = 0;
			pso_desc.pso_desc.RasterizerState.DepthClipEnable = TRUE;
			pso_desc.pso_desc.RasterizerState.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
			pso_desc.pso_desc.RasterizerState.AntialiasedLineEnable = FALSE;
			pso_desc.pso_desc.RasterizerState.MultisampleEnable = FALSE;

			//�u�����h�X�e�[�g�̐ݒ�
			for (int i = 0; i < _countof(pso_desc.pso_desc.BlendState.RenderTarget); ++i) {
				pso_desc.pso_desc.BlendState.RenderTarget[i].BlendEnable = FALSE;
				pso_desc.pso_desc.BlendState.RenderTarget[i].SrcBlend = D3D12_BLEND_ONE;
				pso_desc.pso_desc.BlendState.RenderTarget[i].DestBlend = D3D12_BLEND_ZERO;
				pso_desc.pso_desc.BlendState.RenderTarget[i].BlendOp = D3D12_BLEND_OP_ADD;
				pso_desc.pso_desc.BlendState.RenderTarget[i].SrcBlendAlpha = D3D12_BLEND_ONE;
				pso_desc.pso_desc.BlendState.RenderTarget[i].DestBlendAlpha = D3D12_BLEND_ZERO;
				pso_desc.pso_desc.BlendState.RenderTarget[i].BlendOpAlpha = D3D12_BLEND_OP_ADD;
				pso_desc.pso_desc.BlendState.RenderTarget[i].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
				pso_desc.pso_desc.BlendState.RenderTarget[i].LogicOpEnable = FALSE;
				pso_desc.pso_desc.BlendState.RenderTarget[i].LogicOp = D3D12_LOGIC_OP_CLEAR;
			}
			pso_desc.pso_desc.BlendState.AlphaToCoverageEnable = FALSE;
			pso_desc.pso_desc.BlendState.IndependentBlendEnable = FALSE;

			//�f�v�X�X�e���V���X�e�[�g�̐ݒ�
			pso_desc.pso_desc.DepthStencilState.DepthEnable = TRUE;								//�[�x�e�X�g����
			pso_desc.pso_desc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
			pso_desc.pso_desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
			pso_desc.pso_desc.DepthStencilState.StencilEnable = FALSE;							//�X�e���V���e�X�g�Ȃ�
			pso_desc.pso_desc.DepthStencilState.StencilReadMask = D3D12_DEFAULT_STENCIL_READ_MASK;
			pso_desc.pso_desc.DepthStencilState.StencilWriteMask = D3D12_DEFAULT_STENCIL_WRITE_MASK;

			pso_desc.pso_desc.DepthStencilState.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
			pso_desc.pso_desc.DepthStencilState.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
			pso_desc.pso_desc.DepthStencilState.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
			pso_desc.pso_desc.DepthStencilState.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

			pso_desc.pso_desc.DepthStencilState.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
			pso_desc.pso_desc.DepthStencilState.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
			pso_desc.pso_desc.DepthStencilState.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
			pso_desc.pso_desc.DepthStencilState.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_ALWAYS;

			pso_desc.pso_desc.DSVFormat = DXGI_FORMAT_D32_FLOAT;

			default_pso_ = eng::PipelineState::create(pso_desc);
			if (!default_pso_) return false;
		}

		/* �f�t�H���g�e�N�X�`���̍쐬 */ {

			//�e�N�X�`���p�̃f�X�N���v�^�q�[�v�̍쐬
			D3D12_DESCRIPTOR_HEAP_DESC srv_heap_desc = {
				D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,
				DESCRIPTOR_SRV_NUM,							// ���߂Ɋm�ۂ��Ă���
				D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE,
				0
			};
			srv_heap_ = DescriptorManager::create(srv_heap_desc);

			default_texture_ = Texture::loadFromFile("");
			if (!default_texture_) return false;
		}

		/* �R�}���h���X�g�̍쐬 */ {

			if (FAILED(mgr.device_->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, command_allocator_.Get(), default_pso_->getPSO().Get(), IID_PPV_ARGS(&command_list_)))) return false;
			if (FAILED(command_list_->Close())) return false;
		}

		// ���\�[�X��GPU�ɃA�b�v���[�h�����܂őҋ@
		return waitForPreviousFrame();
	}

	void GraphicsManager::finalize() {
		waitForPreviousFrame();
	}

	bool GraphicsManager::waitForPreviousFrame() {

		sys::Dx12Manager& mgr = sys::Dx12Manager::getInstance();

		const UINT64 fence = mgr.fence_value_;
		if (FAILED(command_queue_->Signal(mgr.fence_.Get(), fence))) return false;
		mgr.fence_value_++;

		// �O�̃t���[�����I������܂őҋ@
		if (mgr.fence_->GetCompletedValue() < fence) {
			if (FAILED(mgr.fence_->SetEventOnCompletion(fence, mgr.fence_event_))) return false;
			WaitForSingleObject(mgr.fence_event_, INFINITE);
		}

		return true;
	}

	bool GraphicsManager::resetCommandList() {
		if (FAILED(command_allocator_->Reset())) return false;
		if (FAILED(command_list_->Reset(command_allocator_.Get(), default_pso_->getPSO().Get()))) return false;
		return true;
	}

	void GraphicsManager::setResourceBarrier(ID3D12Resource* rtv, const D3D12_RESOURCE_STATES state_before, const D3D12_RESOURCE_STATES state_after) {
		CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(rtv, state_before, state_after);
		command_list_->ResourceBarrier(1, &barrier);
	}

	void GraphicsManager::renderBefore(const D3D12_VIEWPORT& viewport, const D3D12_RECT& scissor_rect, const std::shared_ptr<RenderTargetView>& rtv, const std::shared_ptr<DepthStencilView>& dsv) {

		command_list_->RSSetViewports(1, &viewport);
		command_list_->RSSetScissorRects(1, &scissor_rect);

		// �y �o�b�N�o�b�t�@���`��^�[�Q�b�g�Ƃ��Ďg�p�ł���悤�ɂȂ�܂ő҂� �z
		// ������ GPU�R�A�� �����Ƃ����� dx12 �ł�
		// GPU�R�A �Ŏg�p����郊�\�[�X�Ƀo���A�𒣂�炵��
		// �Ⴆ�� �Ƃ��� GPU�R�A �Ŏg�p���̃��\�[�X�𑼂� GPU�R�A ������ɐG����Ȃ��悤�ɂ��鏈�u���낤��
		// ���̏ꍇ�̓����_�[�^�[�Q�b�g( �`��Ώۂ̃o�b�N�o�b�t�@ )�Ƀo���A�𒣂��Ă���
		setResourceBarrier(rtv->getBuffer().Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

		// �����_�[�^�[�Q�b�g�̐ݒ�
		command_list_->OMSetRenderTargets(1, &rtv->getHandle().getCpuHandle(), FALSE, &dsv->getHandle().getCpuHandle());

		// �[�x�X�e���V���r���[�ƃ����_�[�^�[�Q�b�g�r���[�̃N���A
		command_list_->ClearDepthStencilView(dsv->getHandle().getCpuHandle(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
		command_list_->ClearRenderTargetView(rtv->getHandle().getCpuHandle(), rtv->getClearColor().c, 0, nullptr);

	}

	void GraphicsManager::renderAfter(const std::shared_ptr<RenderTargetView>& rtv) {
		// �o�b�N�o�b�t�@�̕`�抮����҂��߂̃o���A��ݒu
		setResourceBarrier(rtv->getBuffer().Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
	}

	bool GraphicsManager::executeCommandList() {

		if (FAILED(command_list_->Close())) return false;

		// �R�}���h���X�g�����s
		ID3D12CommandList* ppCommandLists[] = { command_list_.Get() };
		command_queue_->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

		return true;
	}

	bool GraphicsManager::presentSwapChain() {
		return (!FAILED(swap_chain_->Present(1, 0)));
	}

}
