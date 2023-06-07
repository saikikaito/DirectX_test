#pragma once
#include <stdint.h>
#include <vector>
#include <string>


namespace lib {

	class Utility final {
	private:
		// �����̋֎~
		Utility() = delete;
		Utility(const Utility&) = delete;
		Utility(const Utility&&) = delete;
		Utility& operator =(const Utility&) = delete;
		Utility& operator =(const Utility&&) = delete;

	public:
		//====================================================================================================
		// static�֐�

		// uint64_t�^��10�i���\�L�̃f�[�^�����ۂ̃o�C�i���f�[�^�ɕϊ�
		// ��F10�i�� 1101 �� 10�i�� 13 (2�i�� 1011)
		template<class Tuint>
		inline static Tuint binaryIntTo(uint64_t binary) {
			Tuint ret = 0;
			int add = 1;
			for (int i = 0; i < (sizeof(Tuint) * 8); ++i) {
				ret += (binary & 1) ? add : 0;
				binary /= 10;
				if (binary == 0) break;
				add *= 2;
			}
			return ret;
		}

		// string�^��10�i���\�L�̃f�[�^�����ۂ̃o�C�i���f�[�^�ɕϊ�
		// ��Fstring�^ "1101" �� 10�i�� 13 (2�i�� 1011)
		template<class Tuint>
		inline static Tuint binaryStrTo(const std::string& binary) {
			return binaryIntTo<Tuint>(std::stoull(binary));
		}

		// �o�C�i���f�[�^��uint32_t�^��10�i���\�L�ɕϊ�
		// ��F2�i�� 1101 �� 10�i�� 1101
		template<class Tuint>
		inline static uint64_t integerToBinaryInt(Tuint integer) {
			uint64_t ret = 0;
			int add = 1;
			for (int i = 0; i < (sizeof(Tuint) * 8); ++i) {
				ret += (integer & 1) ? add : 0;
				integer >>= 1;
				if (integer == 0) break;
				add *= 10;
			}
			return ret;
		}

		// �o�C�i���f�[�^��string�^��10�i���\�L�ɕϊ�
		// ��F2�i�� 1101 �� string�^ "1101"
		template<class Tuint>
		inline static std::string integerToBinaryStr(Tuint integer) {
			std::string ret;
			for (int i = 0; i < (sizeof(Tuint) * 8); ++i) {
				std::string add = (integer & 1) ? "1" : "0";
				ret = add + ret;
				integer >>= 1;
			}
			return ret;
		}

		// �w�蕶���ŕ���
		static std::vector<std::string> split(const std::string& origin, const char div_ch);

		// CSV�t�@�C���̃��[�h
		static std::vector<std::vector<std::string>> loadCSV(const std::string& file_path, const char div_ch = ',');

		//====================================================================================================
	};

}
