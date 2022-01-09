/*
 *
 *  MIT License
 *
 *  Copyright (c) 2022 Leonardo Tarollo (LTDev) <develtar@gmail.com>
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 */
#ifndef QSINGLETON_CPP
#define QSINGLETON_CPP

#include "singleton.h"

namespace LTDev {

/**
 * The singleton instance instantiation.
 *
 * @note static members needs to be instantiated here
 */
template <class T>
T* Singleton<T>::_instance=nullptr;

/**
 * Returns the singleton instance. This method is thread-safe.
 *
 * @note to prevent compilation errors when using a templated method
 * implemented in the source file (.cpp), it's necessary to include it
 * where this method is called  (@see `C++ Linguaggio, libreria standard,
 * principi di programmazione. 3rd edition, Bjarne Stroustrup,
 * paragraph 13.7, page 398-399, Addison-Wesley`).
 *
 * @return T*
 */
template <class T>
T* Singleton<T>::getInstance()
{
    /**
     * @brief mutex: thread-safe implementation
     *
     * Using QMutex because it is faster then std::mutex
     * @see https://stackoverflow.com/questions/29170495/performance-of-stdmutex-and-qmutex-in-mingw-64-posix-thread-version
     *
     */
    static QMutex mutex;

    // Checks the instance status
    if (_instance==nullptr)
    {
        // Only the first thread may construct the class
        mutex.lock();

        // If the class isn't instantiated, construct a new instance
        if (_instance==nullptr) {
            _instance = new T();
        }

        mutex.unlock();
    }

    return _instance;
}

/**
 * @brief deletes the singleton instance.
 */
template<class T>
void Singleton<T>::deleteInstance()
{
    qDebug() << "Deleting instance " << typeid(T).name();

    static QMutex mutex;
    mutex.lock();

    delete _instance;
    _instance = nullptr;

    mutex.unlock();
}

}

#endif // QSINGLETON_CPP
