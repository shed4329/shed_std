#ifndef ITERATOR_BASE_H
#define ITERATOR_BASE_H

namespace shed_std{
    // 迭代器标志
    struct input_iterator_tag{};
    struct output_iterator_tag{};
    struct forward_itertor_tag          : public input_iterator_tag{};
    struct bidirectional_iterator_tag   : public forward_itertor_tag{};
    struct random_access_iterator_tag   : public bidirectional_iterator_tag{}; 
}

#endif // ITERATOR_BASE_H