#pragma once
#include <wrl.h>
#include <d3d12.h>
#include "object.h"
#include "../transform.h"


namespace eng {

	class Shape;
	class Material;
	class PipelineState;

	class Mesh final : public Object {
	private:
		template<class T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;
	public:
		using s_ptr = std::shared_ptr<Mesh>;
		using w_ptr = std::weak_ptr<Mesh>;
	private:
		//====================================================================================================
		// �����o�֐�

		// �萔�o�b�t�@�̍쐬
		bool createCbv();

		//====================================================================================================
	public:
		Mesh() {}
		~Mesh() {}

		//====================================================================================================
		// �����o�ϐ�

		ComPtr<ID3D12Resource> cbv_;					// �萔�o�b�t�@
		std::shared_ptr<Shape> shape_ = nullptr;		// �`��f�[�^
		std::shared_ptr<Material> material_ = nullptr;	// �}�e���A��
		std::shared_ptr<PipelineState> pso_ = nullptr;	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
		Transform<Mesh>::s_ptr transform_ = nullptr;	// �e�q�֌W

		//====================================================================================================
		// static�֐�

		// ����
		static Mesh::s_ptr createFromShape(std::shared_ptr<Shape> shape, const std::string& texture_file_path = "");

		//====================================================================================================
	};

}
