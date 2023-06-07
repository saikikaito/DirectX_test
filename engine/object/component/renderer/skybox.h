#pragma once
#include "default_mesh_renderer.h"


namespace eng {

	class Texture;

	class Skybox final : public DefaultMeshRenderer {
	public:
		using s_ptr = std::shared_ptr<Skybox>;
		using w_ptr = std::weak_ptr<Skybox>;

		struct Textures {
			std::shared_ptr<Texture> right = nullptr;
			std::shared_ptr<Texture> left = nullptr;
			std::shared_ptr<Texture> up = nullptr;
			std::shared_ptr<Texture> down = nullptr;
			std::shared_ptr<Texture> forward = nullptr;
			std::shared_ptr<Texture> back = nullptr;
		};

	private:
		//====================================================================================================
		// �����o�֐�

		// ������
		bool onCreated() final override;

		// �`��
		void render(const std::shared_ptr<Camera>& camera) final override;

		//====================================================================================================
	public:
		Skybox() {}
		~Skybox() {}

		//====================================================================================================
		// �����o�֐�

		// �e�N�X�`���̐ݒ�
		void setTextures(const Textures& textures);

		//====================================================================================================
	};

}
