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
#ifndef QSINGLETON_H
#define QSINGLETON_H

#include <QObject>
#include <QMutex>
#include <QDebug>

namespace LTDev {

/**
 * Qt does not support templates which contain the Q_OBJECT macro: a workaround to
 * this problem is:
 *
 * 1- create a subclass of QObject class and make our singleton class his child.
 *    (@see https://doc.qt.io/archives/qq/qq15-academic.html)
 *
 * 2- create a class which extends QObject AND out singleton class
 *    es.
 *      class MyClass: public QObject, public Singleton<MyClass> {
 *          Q_OBJECT
 *
 *          ....
 *      };
 *
 * The second solution is the preferred one, because it is more flexible.
 *
 */
template <class T>
class Singleton
{
public:
    /**
     * @brief Returns the singleton instance. This method is thread-safe.
     *
     * @note to prevent compilation errors when using a templated method
     * implemented in the source file (.cpp), it's necessary to include it
     * where this method is called (@see `C++ Linguaggio, libreria standard,
     * principi di programmazione. 3rd edition, Bjarne Stroustrup,
     * paragraph 13.7, page 398-399, Addison-Wesley`).
     *
     * @return T*
     */
    static T* getInstance();

    /**
     * @brief deletes the singleton instance.
     */
    static void deleteInstance();

    /*
     * Deleting the following methods and operators to prevent making a copy/move of the singleton instance.
     */
    Singleton<T>(const Singleton<T>&) = delete;
    Singleton<T>(Singleton<T>&&) = delete;
    Singleton<T>& operator=(const Singleton<T>&) = delete;
    Singleton<T>& operator=(Singleton<T>&&) = delete;

protected:
    /**
     * @brief The singleton instance
     */
    static T* _instance;

    /**
     * @brief Constructor.
     * It is declared as protected to prevent instantiation.
     */
    Singleton<T>(){};
};

}
#endif // QSINGLETON_H
