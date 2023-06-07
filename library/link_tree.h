#pragma once
#include <functional>
#include "link_linear.h"


namespace lib {

	template<class T>
	class LinkTree : public LinkLinear<T> {
	private:
		//====================================================================================================
		// �����o�ϐ�

		std::weak_ptr<T> parent_;	// �e
		std::weak_ptr<T> child_;	// �擪�̎q

		//====================================================================================================
	protected:
		LinkTree() {}

	public:
		virtual ~LinkTree() {}

		//====================================================================================================
		// �����o�֐�

		// ���̎擾
		inline std::shared_ptr<T> getRoot() {
			std::shared_ptr<T> root = getParent();
			if (!root) return SmartFactory::shared_from_this<T>();
			return root->getRoot();
		}

		// �e�̎擾
		inline std::shared_ptr<T> getParent() const {
			return (parent_.expired()) ? nullptr : parent_.lock();
		}

		// �擪�̎q�̎擾
		inline std::shared_ptr<T> getChild() const {
			return (child_.expired()) ? nullptr : child_.lock();
		}

		// �q���琔����count�Ԗڂ̎q�̎擾
		inline std::shared_ptr<T> getChild(const int count) const {
			std::shared_ptr<T> child = getChild();
			for (int i = 0; i < count; ++i) {
				if (!child) break;
				child = child->getNext();
			}
			return child;
		}

		// ���g���q�Ƃ��đO�ɒǉ�
		inline void pushPrev(const std::shared_ptr<T>& obj) {
			obj->pop();
			obj->parent_ = SmartFactory::shared_from_this<T>();
			LinkLinear<T>::pushPrev(obj);
		}

		// ���g���q�Ƃ��Č��ɒǉ�
		inline void pushNext(const std::shared_ptr<T>& obj) {
			obj->pop();
			obj->parent_ = SmartFactory::shared_from_this<T>();
			LinkLinear<T>::pushNext(obj);
		}

		// ���g���q�Ƃ��čőO�ɒǉ�
		inline void pushFront(const std::shared_ptr<T>& obj) {
			obj->pop();
			obj->parent_ = SmartFactory::shared_from_this<T>();
			LinkLinear<T>::pushFront(obj);
		}

		// ���g���q�Ƃ��čŌ���ɒǉ�
		inline void pushBack(const std::shared_ptr<T>& obj) {
			obj->pop();
			obj->parent_ = SmartFactory::shared_from_this<T>();
			LinkLinear<T>::pushBack(obj);
		}

		// �q�̍Ō���ɒǉ�
		inline void pushChild(const std::shared_ptr<T>& obj) {
			obj->pop();
			obj->parent_ = SmartFactory::shared_from_this<T>();
			std::shared_ptr<T> child = getChild();
			if (!child) {
				child_ = obj;
			}
			else {
				child->LinkLinear<T>::pushBack(obj);
			}
		}

		// �e���痣�E
		inline void pop() {
			std::shared_ptr<T> parent = getParent();
			if (!parent) return;
			LinkLinear<T>::pop();
			parent_.reset();
		}

		// ���g���牺�̃m�[�h�ɑ΂��Ċ֐������s
		inline void roundup(const std::function<void(std::shared_ptr<T>)>& func) {
			std::shared_ptr<T> ptr = SmartFactory::shared_from_this<T>();
			func(ptr);
			ptr = getChild();
			while (ptr) {
				ptr->roundup(func);
				ptr = ptr->getNext();
			}
		}

		// �������牺�ɑ��݂��邩
		inline bool isExist(const std::shared_ptr<T>& obj) {
			bool ret = false;
			roundup([obj, &ret](std::shared_ptr<T> node) {
				if (obj == node) ret = true;
			});
			return ret;
		}

		//====================================================================================================
	};

}
