#pragma once
#include <wrl.h>
#include <d3d12.h>
#include "../../library/library.h"


namespace eng {

	class Shader;

	class PipelineState final : public lib::SmartFactory {
		friend class lib::SharedFlyweightMap<std::string, PipelineState>;
	private:
		template<class T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;
	public:
		using s_ptr = std::shared_ptr<PipelineState>;
		using w_ptr = std::weak_ptr<PipelineState>;

		struct CreateDesc {
			std::string regist_name = "default";
			std::shared_ptr<Shader> shader = nullptr;
			D3D12_GRAPHICS_PIPELINE_STATE_DESC pso_desc = {};
		};

	private:
		//====================================================================================================
		// �����o�ϐ�

		ComPtr<ID3D12PipelineState> pso_;			// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
		std::shared_ptr<Shader> shader_ = nullptr;	// �V�F�[�_�[

		//====================================================================================================
		// static�ϐ�

		inline static lib::SharedFlyweightMap<std::string, PipelineState> regist_map_;	// �o�^�}�b�v

		//====================================================================================================
		// static�֐�

		// SharedFlyweightMap�ł̐���
		static PipelineState::s_ptr loadOfFlyweight(const CreateDesc& desc);

		//====================================================================================================
	public:
		PipelineState() {}
		~PipelineState() {}

		//====================================================================================================
		// �����o�֐�

		// �Q�b�^�[
		inline ComPtr<ID3D12PipelineState> getPSO() { return pso_; }
		inline std::shared_ptr<Shader> getShader() { return shader_; }

		//====================================================================================================
		// static�֐�

		// ����
		static PipelineState::s_ptr create(const CreateDesc& desc);

		//====================================================================================================
	};

}
