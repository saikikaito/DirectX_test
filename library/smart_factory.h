#pragma once
#include <memory>
#include <any>


namespace lib {

	//====================================================================================================
	// 
	// �X�}�[�g�|�C���^�ł̐�������������N���X
	// ���̃|�C���^����new�ł̐������֎~
	// ���̃|�C���^����z��I�u�W�F�N�g�̐������֎~
	// �R���X�g���N�^���g�p����ۂ� constructor ���z�֐����I�[�o�[���C�h����
	// 
	//====================================================================================================
	class SmartFactory : public std::enable_shared_from_this<SmartFactory> {
	private:
		//====================================================================================================

		// new�ł̐������֎~
		// _mm_malloc ... �A���C�����g��������̒l���ƒ������ă������m�ۂ���
		inline static void* operator new(std::size_t size) { return _mm_malloc(size, 16); }

		// �z��I�u�W�F�N�g�̐������֎~
		static void* operator new[](std::size_t) = delete;
		static void operator delete[](void*) = delete;

		//====================================================================================================
	protected:
		SmartFactory() {}

		//====================================================================================================
		// �����o�֐�

		// �����Ȃ��R���X�g���N�^
		virtual bool constructor() { return true; }

		// ��������R���X�g���N�^
		virtual bool constructor(std::any args) { return true; }

		//====================================================================================================
	public:
		virtual ~SmartFactory() {}

		// _mm_free ... _mm_malloc�œ��I�m�ۂ������������������ۂɎg�p����
		inline static void operator delete(void* p) { _mm_free(p); }

		//====================================================================================================
		// static�֐�

		template<class T>
		inline std::shared_ptr<T> shared_from_this() {
			return (!std::is_base_of<SmartFactory, T>::value) ? nullptr : std::static_pointer_cast<T>(std::enable_shared_from_this<SmartFactory>::shared_from_this());
		}

		// shared_ptr<T>�̐����i�����Ȃ��j
		template<class T>
		inline static std::shared_ptr<T> createShared() {
			if (!std::is_base_of<SmartFactory, T>::value) return nullptr;
			std::shared_ptr<T> ptr = std::make_shared<T>();
			if (!ptr->constructor()) return nullptr;
			return ptr;
		}

		// shared_ptr<T>�̐����i��������j
		template<class T, class Desc>
		inline static std::shared_ptr<T> createShared(Desc desc) {
			if (!std::is_base_of<SmartFactory, T>::value) return nullptr;
			std::shared_ptr<T> ptr = std::make_shared<T>();
			if (!ptr->constructor(desc)) return nullptr;
			return ptr;
		}

		// unique_ptr<T>�̐����i�����Ȃ��j
		template<class T>
		inline static std::unique_ptr<T> createUnique() {
			if (!std::is_base_of<SmartFactory, T>::value) return nullptr;
			std::unique_ptr<T> ptr = std::make_unique<T>();
			if (!ptr->constructor()) return nullptr;
			return ptr;
		}

		// unique_ptr<T>�̐����i��������j
		template<class T, class Desc>
		inline static std::unique_ptr<T> createUnique(Desc desc) {
			if (!std::is_base_of<SmartFactory, T>::value) return nullptr;
			std::unique_ptr<T> ptr = std::make_unique<T>();
			if (!ptr->constructor(desc)) return nullptr;
			return ptr;
		}

		//====================================================================================================
	};

}
