/*
    The Nixy Library
    Code covered by the MIT License

    Author: mutouyun (http://darkc.at)
*/

#pragma once

#include "nixycore/memory/alloc.h"
#include "nixycore/memory/std_alloc.h"
#include "nixycore/memory/cache_pool.h"
#include "nixycore/memory/mem_pool.h"
#include "nixycore/memory/center_heap.h"

#include "nixycore/thread/tls_ptr.h"
#include "nixycore/thread/thread_model.h"
#include "nixycore/pattern/singleton.h"
#include "nixycore/algorithm/series.h"

#include "nixycore/general/general.h"

//////////////////////////////////////////////////////////////////////////
NX_BEG
//////////////////////////////////////////////////////////////////////////

/*
    The thread local storage singleton
*/

template <typename T, class AllocT>
class TLSSingleton
{
    typedef tls_ptr<T> tls_t;

    static void destroy(pvoid p)
    {
        nx::free<AllocT>(static_cast<T*>(p));
    }

public:
    static T& instance(void)
    {
        T* p = singleton<tls_t>(destroy);
        if (p) return (*p);
        singleton<tls_t>() = p = nx::alloc<AllocT, T>();
        return (*p);
    }
};

/*
    memory alloc policy model
*/

struct pool_alloc_model
{
    typedef cache_pool
        <
            use::alloc_std,
            use::thread_single,
            use::alloc_center_heap
        > cache_pool_t;

    typedef mem_pool<cache_pool_t> mem_pool_t;

    static mem_pool_t& instance(void)
    {
        use::alloc_center_heap::instance(); // Make center heap run first
        return TLSSingleton<mem_pool_t, use::alloc_std>::instance();
    }

    static pvoid alloc(size_t size)
    {
        return instance().alloc(size);
    }

    static void free(pvoid p, size_t size)
    {
        instance().free(p, size);
    }

    static pvoid realloc(pvoid p, size_t old_size, size_t new_size)
    {
        return instance().realloc(p, old_size, new_size);
    }
};

namespace use
{
    typedef alloc_model<pool_alloc_model> alloc_pool;
}

//////////////////////////////////////////////////////////////////////////
NX_END
//////////////////////////////////////////////////////////////////////////
