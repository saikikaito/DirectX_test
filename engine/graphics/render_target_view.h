#pragma once
#include <wrl.h>
#include <d3d12.h>
#include "../../library/library.h"
#include "descriptor_handle.h"


namespace eng {

	class RenderTargetView : public lib::SmartFactory {
	private:
		template<class T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;
	public:
		using s_ptr = std::shared_ptr<RenderTargetView>;
		using w_ptr = std::weak_ptr<RenderTargetView>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		ComPtr<ID3D12Resource> buffer_;	// �o�b�t�@
		DescriptorHandle handle_;		// �n���h��
		lib::Color clear_color_;		// �N���A����F

		//====================================================================================================
	public:
		RenderTargetView() {}
		~RenderTargetView();

		//====================================================================================================
		// �����o�֐�

		// �Q�b�^�[
		inline ComPtr<ID3D12Resource>& getBuffer() { return buffer_; }
		inline DescriptorHandle getHandle() const { return handle_; }
		inline lib::Color getClearColor() const { return clear_color_; }

		//====================================================================================================
		// static�֐�

		// ����
		static RenderTargetView::s_ptr create(const lib::Color& clear_color, const LONG width, const LONG height);

		//====================================================================================================
	};

}
