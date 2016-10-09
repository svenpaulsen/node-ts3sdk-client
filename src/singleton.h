/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#ifndef ADDON_SINGLETON_H
#define ADDON_SINGLETON_H

template <typename T>

class Singleton
{
    struct Watcher
    {
        T* m_object;
        
        Watcher()
        {
            m_object = 0;
        }
        
        ~Watcher()
        {
            if(m_object) delete m_object;
        }
    };
    
    static Watcher m_watcher;
    
public:
    static T* instance()
    {
        return ((m_watcher.m_object) ? m_watcher.m_object : m_watcher.m_object = new T);
    }
    
protected:
    Singleton() {}
    ~Singleton() {}
};

template <typename T> typename Singleton<T>::Watcher Singleton<T>::m_watcher;

#endif // ADDON_SINGLETON_H
