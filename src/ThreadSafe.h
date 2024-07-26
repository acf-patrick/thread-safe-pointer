#pragma once

#include <mutex>
#include <functional>
#include <shared_mutex>

template<typename T>
class ThreadSafe {
    using Self = ThreadSafe<T>;
    T _data;
    std::shared_mutex _mutex;

public:
    ThreadSafe() = default;

    ThreadSafe(const T& data) : _data(data) {}

    template<typename... Args>
    ThreadSafe(Args&&... args)
        : _data(std::forward<Args>(args)...)
    {}

    /* Prevent copy */

    ThreadSafe(const ThreadSafe&) = delete;
    ThreadSafe& operator= (const ThreadSafe&) = delete;
    ThreadSafe& operator= (ThreadSafe&&) = delete;

    T get() {
        std::shared_lock lock(_mutex);
        return _data;
    }

    operator T() {
        std::shared_lock lock(_mutex);
        return _data;
    }

    // Apply function on data without mutating
    template<typename Fn>
    auto access(Fn&& function) {
        std::shared_lock lock(_mutex);
        return function(T(_data));
    }

    T set(const T& data) {
        std::unique_lock lock(_mutex);
        _data = data;
        return data;
    }

    // Mutate data with given function 
    template<typename Fn>
    auto apply(Fn&& function) {
        std::unique_lock lock(_mutex);
        return function(_data);
    }

    // Mutate data and return reference to current object
    template<typename Fn>
    Self& mutate(Fn&& function) {
        apply(function);
        return *this;
    }
};