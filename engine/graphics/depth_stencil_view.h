#pragma once
#include <wrl.h>
#include "../../library/library.h"
#include "descriptor_handle.h"


namespace eng {

	class DepthStencilView final : public lib::SmartFactory {
	private:
		template<class T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;
	public:
		using s_ptr = std::shared_ptr<DepthStencilView>;
		using w_ptr = std::weak_ptr<DepthStencilView>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		ComPtr<ID3D12Resource> buffer_;	// �o�b�t�@
		DescriptorHandle handle_;		// �n���h��

		//====================================================================================================
	public:
		DepthStencilView() {}
		~DepthStencilView();

		//====================================================================================================
		// �����o�֐�

		// �Q�b�^�[
		inline ComPtr<ID3D12Resource> getBuffer() { return buffer_; }
		inline DescriptorHandle getHandle() const { return handle_; }

		//====================================================================================================
		// static�֐�

		// ����
		static DepthStencilView::s_ptr create(const LONG width, const LONG height);

		//====================================================================================================
	};

}
