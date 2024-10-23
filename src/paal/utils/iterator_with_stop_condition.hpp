//=======================================================================
// Copyright (c) 2013 Piotr Wygocki
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
/**
 * @file iterator_with_stop_condition.hpp
 * @brief
 * @author Piotr Wygocki
 * @version 1.0
 * @date 2014-02-10
 */
#ifndef PAAL_ITERATOR_WITH_STOP_CONDITION_HPP
#define PAAL_ITERATOR_WITH_STOP_CONDITION_HPP

#include <boost/iterator/iterator_facade.hpp>

namespace paal {

/**
 * @brief On each increment/decrement of the iterator the StopCondition is
 *          checked. If it is satisfied the underlying iterator is "moved" to
* the end.
 *          In other words when StopCondition is fulfilled, the range becomes
* empty.
 *
 * @tparam Iterator
 * @tparam StopCondition
 */
template <typename Iterator, typename StopCondition>
class iterator_with_stop_condition : public boost::iterator_facade<
    iterator_with_stop_condition<Iterator, StopCondition>,
    typename std::iterator_traits<Iterator>::value_type,
    typename std::iterator_traits<Iterator>::iterator_category,
    typename std::iterator_traits<Iterator>::reference,
    typename std::iterator_traits<Iterator>::difference_type> {
    typedef typename std::iterator_traits<Iterator>::reference reference;

    /**
     * @brief private constructor. Use make_beginiterator_with_stop_condition,
     *              make_enditerator_with_stop_condition.
     *
     * @param begin
     * @param end
     * @param stop_condition
     */
    iterator_with_stop_condition(Iterator begin, Iterator end,
                                 StopCondition stop_condition)
        : m_begin(begin), m_end(end), m_stop_condtion(stop_condition) {}

    friend class boost::iterator_core_access;
    template <typename I, typename SC>
    friend iterator_with_stop_condition<I, SC>
        make_beginiterator_with_stop_condition(I, I, SC);

    template <typename I, typename SC>
    friend iterator_with_stop_condition<I, SC>
        make_enditerator_with_stop_condition(I, SC);

    /**
     * @brief checked if stop_condition is fullfiled
     *        moves m_begin to m_end if yes.
     */
    void check_stop() {
        if (m_stop_condtion()) {
            m_begin = m_end;
        }
    }

    /**
     * @brief increment
     */
    void increment() {
        ++m_begin;
        check_stop();
    }

    /**
     * @brief decrement
     */
    void decrement() {
        --m_begin;
        check_stop();
    }

    /**
     * @brief equal
     *
     * @param other
     *
     * @return
     */
    bool equal(iterator_with_stop_condition const &other) const {
        return this->m_begin == other.m_begin;
    }

    /**
     * @brief dereference
     *
     * @return
     */
    reference dereference() const { return *m_begin; }

    /**
     * @brief advance
     *
     * @param n
     */
    void advance(typename std::iterator_traits<Iterator>::difference_type n) {
        m_begin += n;
        check_stop();
    }

    /**
     * @brief distance_to
     *
     * @param other
     *
     * @return
     */
    std::size_t distance_to(iterator_with_stop_condition other) {
        return other.m_begin - m_begin;
    }

    Iterator m_begin;
    Iterator m_end;
    StopCondition m_stop_condtion;
};

/**
 * @brief function to create begin of iterator_with_stop_condition
 *
 * @tparam Iterator
 * @tparam StopCondition
 * @param begin
 * @param end
 * @param stop_condition
 *
 * @return
 */
template <typename Iterator, typename StopCondition>
iterator_with_stop_condition<Iterator, StopCondition>
make_beginiterator_with_stop_condition(Iterator begin, Iterator end,
                                       StopCondition stop_condition) {
    return iterator_with_stop_condition<Iterator, StopCondition>(
        begin, end, stop_condition);
}

/**
 * @brief function to create end of iterator_with_stop_condition
 *
 * @tparam Iterator
 * @tparam StopCondition
 * @param end
 * @param stop_condition
 *
 * @return
 */
template <typename Iterator, typename StopCondition>
iterator_with_stop_condition<Iterator, StopCondition>
make_enditerator_with_stop_condition(Iterator end,
                                     StopCondition stop_condition) {
    return iterator_with_stop_condition<Iterator, StopCondition>(
        end, end, stop_condition);
}

} //!paal

#endif // PAAL_ITERATOR_WITH_STOP_CONDITION_HPP
