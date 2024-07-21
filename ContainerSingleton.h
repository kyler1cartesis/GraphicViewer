#pragma once

template <typename Container>
class ContainerSingleton {
public:
	static Container& Get() {
		// if (!s_instance)
		// 	s_instance = std::shared_ptr<Object>(new Object());
		return s_instance;
	}
	static void Set(Container&& container) {
		s_instance = std::move(container);
	}
	static void Reset() {
		s_instance.clear();
	}
	ContainerSingleton(const ContainerSingleton&) = delete;
	ContainerSingleton& operator=(ContainerSingleton&) = delete;

protected:
	inline static Container s_instance = {};
	ContainerSingleton() = default;
};
