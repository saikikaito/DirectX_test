#pragma once
#include "../../library/library.h"


namespace eng {

	class Object : public lib::SmartFactory {
	public:
		using s_ptr = std::shared_ptr<Object>;
		using w_ptr = std::weak_ptr<Object>;
	private:
		//====================================================================================================
		// �����o�ϐ�

		std::string name_ = "unknown";	// ���O
		bool is_alive_ = true;			// �����t���O
		bool is_active_ = true;			// �L���t���O
		UINT instance_id_ = 0;			// �B���ID

		//====================================================================================================
		// static�ϐ�

		inline static UINT instance_count_ = 0;	// ���܂Ő������ꂽ��

		//====================================================================================================
	public:
		Object() {}
		virtual ~Object() {}

		//====================================================================================================
		// �����o�֐�

		// �Z�b�^�[
		inline void setName(const std::string& name) { name_ = name; }
		inline void setActive(const bool is_active) { is_active_ = is_active; }
		inline void destroy() { is_alive_ = false; }

		// �Q�b�^�[
		inline std::string getName() const { return name_; }
		inline bool isAlive() const { return is_alive_; }
		inline bool isActive() const { return is_active_; }
		inline UINT getInstanceId() const { return instance_id_; }

		//====================================================================================================
		// static�֐�

		// �������̎擾
		inline static UINT getInstanceCount() { return instance_count_; }

		//====================================================================================================
	};

}
