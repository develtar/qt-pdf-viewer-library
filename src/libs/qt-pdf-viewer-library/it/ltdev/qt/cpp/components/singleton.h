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
