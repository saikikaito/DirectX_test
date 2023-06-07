#pragma once
#include <wrl.h>
#include <d3d12.h>
#include "../../library/library.h"
#include "descriptor_handle.h"


namespace eng {

	class Texture final : public lib::SmartFactory {
		// �o�^���邽��
		friend class lib::SharedFlyweightMap<std::string, Texture>;
	private:
		template<class T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;
	public:
		using s_ptr = std::shared_ptr<Texture>;
		using w_ptr = std::weak_ptr<Texture>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		uint32_t width_ = 0;				// ��
		uint32_t height_ = 0;				// ����
		ComPtr<ID3D12Resource> resource_;	// �e�N�X�`��
		DescriptorHandle handle_;			// �n���h��

		//====================================================================================================
		// static�ϐ�

		inline static lib::SharedFlyweightMap<std::string, Texture> regist_map_;	// �o�^�}�b�v

		//====================================================================================================
		// static�֐�

		// SharedFlyweightMap�ł̐���
		static Texture::s_ptr loadOfFlyweight(const std::string& file_path);

		//====================================================================================================
	public:
		Texture() {}
		~Texture() {}

		//====================================================================================================
		// �����o�֐�

		// �Q�b�^�[
		inline uint32_t getWidth() const { return width_; }
		inline uint32_t getHeight() const { return height_; }
		inline ComPtr<ID3D12Resource> const getResource() { return resource_; }
		inline DescriptorHandle getHandle() const { return handle_; }

		//====================================================================================================
		// static�֐�

		// ���[�h
		static Texture::s_ptr loadFromFile(const std::string& file_path);

		// ��̕`��e�N�X�`���̐���
		static Texture::s_ptr createEmpty(const uint32_t width, const uint32_t height);

		//====================================================================================================
	};

}
