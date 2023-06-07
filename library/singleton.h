#pragma once
#include <memory>


namespace lib {

	template<class T>
	class Singleton {
	private:
		// �R�s�[�A����̋֎~
		Singleton(const Singleton&) = delete;
		Singleton(const Singleton&&) = delete;
		Singleton& operator = (const Singleton&) = delete;
		Singleton& operator = (const Singleton&&) = delete;

		//====================================================================================================
		// static�ϐ�
		
		inline static T* instance_ = nullptr;	// �B��̃C���X�^���X

		//====================================================================================================
	protected:
		Singleton() {}

	public:
		virtual ~Singleton() {}

		//====================================================================================================
		// static�֐�

		// �C���X�^���X�̎擾
		inline static T& getInstance() {
			if (!instance_) {
				instance_ = new T();
			}
			return *instance_;
		}

		// �C���X�^���X�̍폜
		inline static void destroy() {
			if (!instance_) return;
			delete instance_;
			instance_ = nullptr;
		}

		//====================================================================================================
	};

}
