#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#include <D3Dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#include "dx12_manager.h"


using namespace Microsoft::WRL;

namespace sys {

	bool Dx12Manager::initialize() {

#if defined(_DEBUG)
		/* DirectX12�̃f�o�b�O���C���[��L���ɂ��� */ {
			ComPtr<ID3D12Debug>	debug_controller;
			if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debug_controller)))) {
				debug_controller->EnableDebugLayer();
			}
		}
#endif
		/* �f�o�C�X�̍쐬 */ {

			// DirectX12���T�|�[�g���闘�p�\�ȃn�[�h�E�F�A�A�_�v�^���擾
			if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&factory_)))) return false;

			// D3D12CreateDevice�����s����ꍇ�̓r�f�I�J�[�h��DirectX12�ɑΉ����Ă��Ȃ��̂� is_use_warp_device_ ��true�ɂ���
			bool is_use_warp_device = false;

			if (is_use_warp_device) {
				ComPtr<IDXGIAdapter> warp_adapter;
				if (FAILED(factory_->EnumWarpAdapter(IID_PPV_ARGS(&warp_adapter)))) return false;
				if (FAILED(D3D12CreateDevice(warp_adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device_)))) return false;
			}
			else {
				ComPtr<IDXGIAdapter1> hardware_adapter;
				ComPtr<IDXGIAdapter1> adapter;
				hardware_adapter = nullptr;

				for (UINT i = 0; DXGI_ERROR_NOT_FOUND != factory_->EnumAdapters1(i, &adapter); i++) {
					DXGI_ADAPTER_DESC1 desc;
					adapter->GetDesc1(&desc);
					if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) continue;
					// �A�_�v�^��DirectX12�ɑΉ����Ă��邩�m�F
					if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr))) break;
				}

				hardware_adapter = adapter.Detach();

				if (FAILED(D3D12CreateDevice(hardware_adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device_)))) return false;
			}
		}

		/* �����I�u�W�F�N�g�̍쐬 */ {

			if (FAILED(device_->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence_)))) return false;
			fence_value_ = 1;

			// �t���[�������Ɏg�p����C�x���g�n���h�����쐬
			fence_event_ = CreateEvent(nullptr, FALSE, FALSE, nullptr);
			if (fence_event_ == nullptr) {
				if (FAILED(HRESULT_FROM_WIN32(GetLastError()))) return false;
			}
		}

		return true;
	}

	void Dx12Manager::finalize() {
		CloseHandle(fence_event_);
	}

}
