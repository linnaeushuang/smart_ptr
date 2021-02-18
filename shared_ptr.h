
#ifndef __SHARED_PTR_HEAD
#define __SHARED_PTR_HEAD

#include <functional>

template<typename T>
class shared_ptr{
private:
	T *ptr_;
	long *shared_count_;
public:
	template<typename U> friend class shared_ptr;

	//construct
	explicit shared_ptr(T *ptr=nullptr) noexcept :ptr_(ptr), shared_count_(new long(1)){}

	//destruct
	~shared_ptr() noexcept {
		if(ptr_ && !(--(*shared_count_))){
			delete ptr_;
			delete shared_count_;
			shared_count_=nullptr;
			ptr_=nullptr;
		}
	}
	T &operator*() const noexcept { return *ptr_; }
	T *operator->() const noexcept { return ptr_; }
	operator bool() const noexcept { return ptr_!=nullptr; }
	T *get() const noexcept { return ptr_; }

	//copy construct, for smae type
	/*
	shared_ptr(const shared_ptr &other) noexcept: ptr_(other.ptr_),shared_count_(other.shared_count_){
		if(ptr_) (*shared_count_)++;
	}
	*/

	//copy construct, for diff type
	template<typename U>
	shared_ptr(const shared_ptr<U> &other) noexcept: ptr_(other.ptr_),shared_count_(other.shared_count_){
		if(ptr_) (*shared_count_)++;
	}

	// move construct
	/*
	shared_ptr(shared_ptr &&other) noexcept {
		ptr_ = other.ptr_;
		if(ptr_){
			shared_count_ = other.shared_count_;
			other.ptr_ = nullptr;
			other.shared_count_ = nullptr;
		}
	}
	*/

	template<typename U>
	shared_ptr(shared_ptr<U> &&other) noexcept {
		ptr_ = other.ptr_;
		if(ptr_){
			shared_count_ = other.shared_count_;
			other.ptr_ = nullptr;
			other.shared_count_ = nullptr;
		}
	}

	void swap(shared_ptr &rhs) noexcept {
		// swap pointer;
		T *tmp_ptr_;
		tmp_ptr_ = ptr_;
		ptr_ = rhs.ptr_;
		rhs.ptr_ = tmp_ptr_;

		// swap count
		long *tmp_count_;
		tmp_count_ = shared_count_;
		shared_count_ = rhs.shared_count_;
		rhs.shared_count_ = tmp_count_;
	}

	// copy assignment
	shared_ptr& operator=(const shared_ptr &rhs) noexcept{
		// TODO:self in operator=
		(*rhs.shared_count_)++;

		if(!(--(*shared_count_))){
			delete ptr_;
			delete shared_count_;
		}
		shared_count_ = rhs.shared_count_;
		ptr_=rhs.ptr_;
		return *this;
	}

	long use_count() const noexcept {
		if(ptr_){
			return *shared_count_;
		}else{
			return 0;
		}
	}

	template<typename U>
	shared_ptr(const shared_ptr<U> &other, T *ptr) noexcept{
		// for type cast
		ptr_ = ptr;
		if(ptr_){
			(*other.shared_count_)++;
			shared_count_=other.shared_count_;
		}
	}
};

template<typename T>
void swap(shared_ptr<T> &lhs, shared_ptr<T> &rhs) noexcept{
	lhs.swap(rhs);
}

template<typename T, typename U>
shared_ptr<T> dynamic_pointer_cast(const shared_ptr<U> &other) noexcept {
	T *ptr = dynamic_cast<T *>(other.get());
	return shared_ptr<T>(other, ptr);
}

template<typename T, typename U>
shared_ptr<T> static_pointer_cast(const shared_ptr<U> &other) noexcept {
	T *ptr = static_cast<T *>(other.get());
	return shared_ptr<T>(other, ptr);
}

template<typename T, typename U>
shared_ptr<T> const_pointer_cast(const shared_ptr<U> &other) noexcept {
	T *ptr = const_cast<T *>(other.get());
	return shared_ptr<T>(other, ptr);
}

template<typename T, typename U>
shared_ptr<T> reinterpret_pointer_cast(const shared_ptr<U> &other) noexcept {
	T *ptr = reinterpret_cast<T *>(other.get());
	return shared_ptr<T>(other, ptr);
}

template<typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args){
	shared_ptr<T> sp(new T(std::forward<Args>(args)...));
	return sp;
}
#endif
