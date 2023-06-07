#pragma once
#include <wrl.h>
#include <d3d12.h>
#include "../../library/library.h"


namespace eng {

	struct Vertex3D {
		lib::Vector3 position;
		lib::Vector3 normal;
		lib::Vector2 uv;
	};

	class Shape final : public lib::SmartFactory {
		// �o�^���邽��
		friend class lib::SharedFlyweightMap<std::string, Shape>;
	private:
		template<class T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;
	public:
		using s_ptr = std::shared_ptr<Shape>;
		using w_ptr = std::weak_ptr<Shape>;

		enum class Angle {
			ANGLE_45,
			ANGLE_90,
			ANGLE_180,
			ANGLE_360,
		};

		struct CreateDesc {
			std::string regist_name = "";
			float width = 10.0f;
			float height = 10.0f;
			float depth = 10.0f;
			float radius = 5.0f;
			float thickness = 3.0f;
			float egge_lenght = 10.0f;
			int stacks = 10;
			int slices = 10;
			Angle angle = Angle::ANGLE_360;
		};

	private:
		//====================================================================================================
		// �����o�ϐ�

		ComPtr<ID3D12Resource> vbo_;	// ���_�o�b�t�@
		ComPtr<ID3D12Resource> ibo_;	// �C���f�b�N�X�o�b�t�@
		int vertex_num_ = 0;			// ���_��
		int index_num_ = 0;				// �C���f�b�N�X��

		//====================================================================================================
		// static�ϐ�

		inline static lib::SharedFlyweightMap<std::string, Shape> regist_map_;	// �o�^�}�b�v

		//====================================================================================================
		// �����o�֐�

		// ���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̍쐬
		bool createBuffers();

		// ���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�փR�s�[
		bool copyBuffers(Vertex3D* vertexs, uint32_t* indexs);

		// �C���f�b�N�X�̌v�Z
		void calcIndexs(uint32_t*& indexs, const int slices, const int stacks);

		//====================================================================================================
		// static�֐�

		// ���ɐ�������Ă��邩
		static bool isCreated(Shape::s_ptr& ret_obj, const std::string& regist_name);

		// SharedFlyweightMap�ł̐���
		static Shape::s_ptr loadOfFlyweight(void* none);

		//====================================================================================================
	public:
		Shape() {}
		~Shape() {}

		//====================================================================================================
		// �����o�֐�

		// �Q�b�^�[
		inline ComPtr<ID3D12Resource> const getVBO() { return vbo_; }
		inline ComPtr<ID3D12Resource> const getIBO() { return ibo_; }
		inline int getVertexNum() const { return vertex_num_; }
		inline int getIndexNum() const { return index_num_; }
		inline D3D12_VERTEX_BUFFER_VIEW getVertexView() const { return { vbo_->GetGPUVirtualAddress(), sizeof(Vertex3D) * vertex_num_, sizeof(Vertex3D) }; }
		inline D3D12_INDEX_BUFFER_VIEW getIndexView() const { return { ibo_->GetGPUVirtualAddress(), sizeof(uint32_t) * index_num_, DXGI_FORMAT_R32_UINT }; }

		//====================================================================================================
		// static�֐�

		// �l�p�`(X,Y��)
		static Shape::s_ptr createPlaneXY(const CreateDesc& desc);
		// �l�p�`(Y,Z��)
		static Shape::s_ptr createPlaneYZ(const CreateDesc& desc);
		// �l�p�`(Z,X��)
		static Shape::s_ptr createPlaneZX(const CreateDesc& desc);
		// �񓙕ӎO�p�`
		static Shape::s_ptr createTriangleIsosceles(const CreateDesc& desc);
		// ���p�O�p�`(�E�������p)
		static Shape::s_ptr createTriangleRight(const CreateDesc& desc);
		// ���p�O�p�`(���������p)
		static Shape::s_ptr createTriangleLeft(const CreateDesc& desc);
		// ���O�p�`
		static Shape::s_ptr createTriangleEquilateral(const CreateDesc& desc);
		// ����
		static Shape::s_ptr createSphere(const CreateDesc& desc);
		// �h�[��
		static Shape::s_ptr createDome(const CreateDesc& desc);
		// ��ʂȂ��̉~��
		static Shape::s_ptr createCone(const CreateDesc& desc);
		// �~��
		static Shape::s_ptr createDisk(const CreateDesc& desc);
		// �~�Տ�̃����O 
		static Shape::s_ptr createDiskRing(const CreateDesc& desc);
		// �~��
		static Shape::s_ptr createCylinder(const CreateDesc& desc);

		//====================================================================================================
	};

}
