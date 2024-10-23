#pragma once
#include <initializer_list>
#include <memory>

template <typename T>
inline T *dereference(const std::shared_ptr<std::shared_ptr<T>> &pp) {
  return pp.get()->get();
}
template <typename T>
inline T *dereference(const std::shared_ptr<T> &p) {
  return p.get();
}

template <typename T>
inline std::shared_ptr<std::shared_ptr<T>> generatePtrPtr(T *pp) {
  return std::make_shared<std::shared_ptr<T>>(pp);
}
template <typename T> inline std::shared_ptr<T> generatePtr(T *p) {
  return std::shared_ptr<T>(p);
}
template <typename T, typename... Args>
inline std::shared_ptr<T> generatePtr(Args &&...args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
inline std::shared_ptr<std::shared_ptr<T>>
generatePtrPtr(Args &&...args) {
  return std::make_shared<std::shared_ptr<T>>(
      std::make_shared<T>(std::forward<Args>(args)...));
}

template <typename T, typename Base>
inline std::shared_ptr<T>
generatePtr(const std::initializer_list<Base> &initList) {
  return std::make_shared<T>(initList);
}

