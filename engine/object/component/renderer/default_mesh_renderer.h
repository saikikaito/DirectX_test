#pragma once
#include "renderer.h"


namespace eng {

	class Mesh;

	class DefaultMeshRenderer : public Renderer {
	public:
		using s_ptr = std::shared_ptr<DefaultMeshRenderer>;
		using w_ptr = std::weak_ptr<DefaultMeshRenderer>;
	private:
		//====================================================================================================
		// �����o�֐�

		// �`��
		void render(const std::shared_ptr<Camera>& camera) override;

		//====================================================================================================
	public:
		DefaultMeshRenderer() {}
		virtual ~DefaultMeshRenderer() {}

		//====================================================================================================
		// �����o�ϐ�

		std::vector<std::shared_ptr<Mesh>> meshs_;	// �`�悷�郁�b�V��

		//====================================================================================================
	};

}
