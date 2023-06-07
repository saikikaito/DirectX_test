#pragma once
#include <string>


namespace lib {

	class BitFlag final {
	private:
		//====================================================================================================
		// �����o�ϐ�

		uint8_t* array_ = nullptr;	// �r�b�g�t���O�Ǘ�����z��
		uint32_t array_size_ = 0;	// �z��̗v�f��
		uint32_t size_ = 0;			// �Ǘ����Ă���r�b�g�̐�

		//====================================================================================================
	public:
		explicit BitFlag(const uint32_t size = 0);
		explicit BitFlag(const std::string& bit_flag);
		BitFlag(const BitFlag& other);
		~BitFlag();

		//====================================================================================================
		// �����o�֐�

		// �e�퉉�Z�q
		BitFlag& operator =(const BitFlag& other);
		BitFlag operator &(const BitFlag& other) const;
		BitFlag& operator &=(const BitFlag& other);
		BitFlag operator |(const BitFlag& other) const;
		BitFlag& operator |=(const BitFlag& other);
		BitFlag operator ^(const BitFlag& other) const;
		BitFlag& operator ^=(const BitFlag& other);
		BitFlag operator ~() const;
		operator bool();

		// �w��ʒu�̃t���O��ݒ�
		void set(const uint32_t index, const bool value);

		// �w��ʒu�̃t���O���擾
		bool get(const uint32_t index) const;

		// �T�C�Y�̕ύX
		void resize(const uint32_t size);

		// �T�C�Y�̕ύX
		void resize(const std::string& bit_flag);

		// ������ɕϊ�
		std::string toString() const;

		// �폜
		void clear();

		// �T�C�Y�̎擾
		inline uint32_t size() const { return size_; }

		//====================================================================================================
	};

}
