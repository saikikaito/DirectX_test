#pragma once
#include "../component.h"


namespace eng {

	class Camera;

	class Renderer : public Component {
		// render���ĂԂ���
		friend class GameObject;
	public:
		using s_ptr = std::shared_ptr<Renderer>;
		using w_ptr = std::weak_ptr<Renderer>;
	private:


	protected:
		//====================================================================================================
		// �����o�֐�

		// �`��
		// TODO: Layer������������Layer�ɕς���
		virtual void render(const std::shared_ptr<Camera>& camera) {}

		//====================================================================================================
	public:
		Renderer() {}
		virtual ~Renderer() {}


	};

}
