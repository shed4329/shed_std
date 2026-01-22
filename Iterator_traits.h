#ifndef ITERATOR_TRAITS_H
#define ITERATOR_TRAITS_H

#include "IteratorBase.h"

namespace shed_std{
    template <typename Iter>
    struct  iterator_traits
    {
        using iterator_category = typename Iter::iterator_category;
        using value_type        = typename Iter::value_type;
        using difference_type   = typename Iter::difference_type;
        using pointer           = typename Iter::point;
        using reference         = typename Iter::reference;
    };

    // 指针特化,因为没有成员类型
    template <typename T>
    struct iterator_traits<T*>
    {
        using iterator_category = random_access_iterator_tag;
        using value_type        = T;
        using difference_type   = long long;
        using pointer           = T*;
        using reference         = T&; 
    };
    
}

#endif