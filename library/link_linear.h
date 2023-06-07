#pragma once
#include "smart_factory.h"


namespace lib {

	template<class T>
	class LinkLinear : public SmartFactory {
	private:
		//====================================================================================================
		// �����o�ϐ�

		std::weak_ptr<T> prev_;	// �O
		std::weak_ptr<T> next_;	// ���

		//====================================================================================================
	protected:
		LinkLinear() {}

	public:
		virtual ~LinkLinear() {}

		//====================================================================================================
		// �����o�֐�

		// �O�̎擾
		inline std::shared_ptr<T> getPrev() const {
			return (prev_.expired()) ? nullptr : prev_.lock();
		}

		// ���̎擾
		inline std::shared_ptr<T> getNext() const {
			return (next_.expired()) ? nullptr : next_.lock();
		}

		// �őO�̎擾
		inline std::shared_ptr<T> getFront() {
			std::shared_ptr<T> prev = getPrev();
			if (!prev) return shared_from_this<T>();
			return prev->getFront();
		}

		// �Ō���̎擾
		inline std::shared_ptr<T> getBack() {
			std::shared_ptr<T> next = getNext();
			if (!next) return shared_from_this<T>();
			return next->getBack();
		}

		// �O�ɒǉ�
		inline void pushPrev(const std::shared_ptr<T>& obj) {
			obj->pop();
			std::shared_ptr<T> s_this = shared_from_this<T>();
			std::shared_ptr<T> prev = getPrev();
			if (prev) {
				obj->prev_ = prev;
				prev->next_ = obj;
			}
			obj->next_ = s_this;
			s_this->prev_ = obj;
		}

		// ���ɒǉ�
		inline void pushNext(const std::shared_ptr<T>& obj) {
			obj->pop();
			std::shared_ptr<T> s_this = shared_from_this<T>();
			std::shared_ptr<T> next = getNext();
			if (next) {
				obj->next_ = next;
				next->prev_ = obj;
			}
			obj->prev_ = s_this;
			s_this->next_ = obj;
		}

		// �őO�ɒǉ�
		inline void pushFront(const std::shared_ptr<T>& obj) {
			std::shared_ptr<T> front = getFront();
			front->pushPrev(obj);
		}

		// �Ō���ɒǉ�
		inline void pushBack(const std::shared_ptr<T>& obj) {
			std::shared_ptr<T> back = getBack();
			back->pushNext(obj);
		}

		// ���E
		inline void pop() {
			std::shared_ptr<T> prev = getPrev();
			std::shared_ptr<T> next = getNext();
			if (prev) prev->next_ = next;
			if (next) next->prev_ = prev;
			prev_.reset();
			next_.reset();
		}

		//====================================================================================================
	};

}
