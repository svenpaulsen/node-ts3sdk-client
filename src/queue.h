/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#ifndef ADDON_QUEUE_H
#define ADDON_QUEUE_H

template <typename T>

class Queue
{
    list<T>         m_queue;
    pthread_mutex_t m_mutex;
    pthread_cond_t  m_cond;
    
public:
    Queue()
    {
        pthread_mutex_init(&m_mutex, nullptr);
        pthread_cond_init(&m_cond, nullptr);
    }
    
    ~Queue()
    {
        pthread_mutex_destroy(&m_mutex);
        pthread_cond_destroy(&m_cond);
    }
    
    void add(T item)
    {
        pthread_mutex_lock(&m_mutex);
        
        m_queue.push_back(item);
        
        pthread_cond_signal(&m_cond);
        pthread_mutex_unlock(&m_mutex);
    }
    
    T get()
    {
        pthread_mutex_lock(&m_mutex);
        
        while(m_queue.size() == 0)
        {
            pthread_cond_wait(&m_cond, &m_mutex);
        }
        
        T item = m_queue.front();
        m_queue.pop_front();
        
        pthread_mutex_unlock(&m_mutex);
        
        return item;
    }
    
    int size()
    {
        pthread_mutex_lock(&m_mutex);
        
        unsigned int size = m_queue.size();
        
        pthread_mutex_unlock(&m_mutex);
        
        return size;
    }
};

#endif // ADDON_QUEUE_H
