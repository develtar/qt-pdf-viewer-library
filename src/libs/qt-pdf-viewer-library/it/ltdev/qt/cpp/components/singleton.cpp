/*
 *
 *  Copyright 2022 Leonardo Tarollo (LTDev) <develtar@gmail.com>
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
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
