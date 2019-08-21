//
//  cqueue.hpp
//  dev-kege
//
//  Created by Kenneth A Esdaile on 5/13/19.
//  Copyright © 2019 Kenneth A Esdaile. All rights reserved.
//

#ifndef cqueue_hpp
#define cqueue_hpp
#include <mutex>
#include "queue.hpp"
namespace kege{
    
    template< typename tvar > class cqueue
    {
    public:
        
        void push(tvar element)
        {
            std::lock_guard<std::mutex> guard(lock);
            que.push( element );
        }
        tvar top()
        {
            std::lock_guard<std::mutex> guard(lock);
            return que.top();
        }
        bool empty()
        {
            std::lock_guard<std::mutex> guard(lock);
            return que.empty();
        }
        void pop()
        {
            std::lock_guard<std::mutex> guard(lock);
            que.pop();
        }
        ~ cqueue()
        {
            que.clear();
        }
        
    private:
        
        ds::queue< tvar > que;
        std::mutex lock;
    };
}
#endif /* cqueue_hpp */
