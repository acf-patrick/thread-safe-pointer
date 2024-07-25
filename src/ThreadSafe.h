#pragma once

#include <mutex>
#include <functional>
#include <shared_mutex>

template<typename T>
class ThreadSafe {
    using Self = ThreadSafePointer<T>;
    T _data;
    std::shared_mutex _mutex;

public:
    ThreadSafePointer() = default;

    ThreadSafePointer(const T& data) : _data(data) {}

    template<typename... Args>
    ThreadSafePointer(Args&&... args)
        : _data(std::forward<Args>(args)...)
    {}

    /* Prevent copy */

    ThreadSafePointer(const ThreadSafePointer&) = delete;
    ThreadSafePointer& operator= (const ThreadSafePointer&) = delete;
    ThreadSafePointer& operator= (ThreadSafePointer&&) = delete;

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

    ThreadSafePointer& operator= (const T& data) {
        std::unique_lock lock(_mutex);
        _data = data;
        return *this;
    }

    void set(const T& data) {
        std::unique_lock lock(_mutex);
        _data = data;
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