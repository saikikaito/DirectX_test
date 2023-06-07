#pragma once
#include <wrl.h>
#include <d3d12.h>
#include "../../library/library.h"


namespace eng {

	class Shader final : public lib::SmartFactory {
		// �o�^���邽��
		friend class lib::SharedFlyweightMap<LPCWSTR, Shader>;
	private:
		template<class T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;
	public:
		using s_ptr = std::shared_ptr<Shader>;
		using w_ptr = std::weak_ptr<Shader>;

		struct CreateDesc {
			LPCWSTR file_path = L"engine/resources/default_shader.fx";
			std::string vertex_shader_name = "";
			std::string vertex_target = "";
			std::string pixel_shader_name = "";
			std::string pixel_target = "";
			D3D12_INPUT_ELEMENT_DESC* input_element_desc = nullptr;
			UINT input_element_size = 0;
			D3D12_ROOT_SIGNATURE_DESC root_signature_desc = {};
		};

	private:
		//====================================================================================================
		// �����o�ϐ�

		D3D12_INPUT_ELEMENT_DESC* input_element_desc_ = nullptr;	// ���_���̓��C�A�E�g
		UINT input_element_size_ = 0;								// ���_���̓��C�A�E�g�̗v�f��
		ComPtr<ID3DBlob> vertex_shader_;							// ���_�V�F�[�_�[
		ComPtr<ID3DBlob> pixel_shader_;								// �s�N�Z���V�F�[�_�[
		ComPtr<ID3D12RootSignature> root_signature_;				// ���[�g�V�O�l�`��

		//====================================================================================================
		// static�ϐ�

		inline static lib::SharedFlyweightMap<LPCWSTR, Shader> regist_map_;	// �o�^�}�b�v

		//====================================================================================================
		// static�֐�

		// SharedFlyweightMap�ł̐���
		static Shader::s_ptr loadOfFlyweight(const CreateDesc& desc);

		//====================================================================================================
	public:
		Shader() {}
		~Shader() {
			if (!input_element_desc_) return;
			delete[] input_element_desc_;
		}

		//====================================================================================================
		// �����o�֐�

		// �Q�b�^�[
		inline D3D12_INPUT_ELEMENT_DESC* getInputElementDesc() const { return input_element_desc_; }
		inline UINT getInputElementSize() const { return input_element_size_; }
		inline ComPtr<ID3DBlob> getVertexShader() const { return vertex_shader_; }
		inline ComPtr<ID3DBlob> getPixelShader() const { return pixel_shader_; }
		inline ComPtr<ID3D12RootSignature> getRootSignature() const { return root_signature_; }

		//====================================================================================================
		// static�֐�

		// ����
		static Shader::s_ptr create(const CreateDesc& desc);

		//====================================================================================================
	};

}
