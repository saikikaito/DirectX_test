#pragma once
#include <unordered_map>
#include <memory>


namespace lib {

	//====================================================================================================
	// 
	// std::shared_ptr �ł̃t���C�E�F�C�g�ȊǗ��}�b�v
	// �Ǘ��������N���X�� static �ȃ����o�ϐ��ɂ��A
	// loadOfFlyweight(const Desc& desc) �����������
	// load(const Key& key, const Desc& desc) ���g�p�ł���
	// 
	//====================================================================================================
	template<class Key, class T>
	class SharedFlyweightMap final {
	private:
		//====================================================================================================
		// �����o�ϐ�

		std::unordered_map<Key, std::shared_ptr<T>> management_map_;	// �Ǘ��}�b�v

		//====================================================================================================
	public:
		SharedFlyweightMap() {}
		~SharedFlyweightMap() {}

		//====================================================================================================
		// �����o�֐�

		// �T�C�Y
		inline int size() { return management_map_.size(); }

		// �o�^����Ă��邩
		inline bool isExist(const Key& key) {
			return management_map_.find(key) != management_map_.end();
		}

		// �폜
		inline void erase(const Key& key) {
			auto it = management_map_.find(key);
			if (management_map_.end() == it) return;
			management_map_.erase(it);
		}

		// �擾
		inline std::shared_ptr<T> get(const Key& key) {
			auto it = management_map_.find(key);
			if (management_map_.end() == it) return nullptr;
			return it->second;
		}

		// �S�J��
		inline void clear() {
			management_map_.clear();
		}

		// ���̃}�b�v�݂̂ŊǗ����Ă���f�[�^�̉��
		inline void releaseUnique() {
			auto it = management_map_.begin();
			while (it != management_map_.end()) {
				if (1 < it->second.use_count()) {
					++it;
					continue;
				}
				management_map_.erase(it);
			}
		}

		// ���[�h
		// ���̊֐��̒��� T::loadOfFlyweight(const Desc& desc) ���Ă�ł���
		template<class Desc>
		inline std::shared_ptr<T> load(const Key& key, const Desc& desc) {
			std::shared_ptr<T> ptr = get(key);
			if (!ptr) {
				ptr = T::loadOfFlyweight(desc);
				management_map_.try_emplace(key, ptr);
			}
			return ptr;
		}

		//====================================================================================================
	};

}
