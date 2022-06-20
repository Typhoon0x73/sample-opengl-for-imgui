#ifndef BLACKBOARD_H_
#define BLACKBOARD_H_

// INCLUDE
#include "ParameterMap.h"
#include <tuple>

template < typename... Types >
class Blackboard
{
public:

    Blackboard() : m_Elements() {}

    ~Blackboard() {}

    template < typename T >
    ParameterMapPtr<T>& get()
    {
        constexpr unsigned int INDEX = FindElement<ParameterMapPtr<T>>::value;
        auto& result = std::get<INDEX>(m_Elements);
        if (result == nullptr)
        {
            result = std::make_unique<ParameterMap<T>>();
        }
        return result;
    }

    template < typename T >
    const ParameterMapPtr<T>& get() const
    {
        return const_cast<Blackboard*>(this)->get<T>();
    }

    template < typename T >
    std::size_t getSize() const
    {
        return get<T>()->GetSize();
    }

private:

    std::tuple<ParameterMapPtr<Types>...> m_Elements;

    /*! データタイプ置き換え */
    template < unsigned int Index >
    using ElementType = typename std::tuple_element<Index, decltype(m_Elements)>::type;

    /*! エレメントチェック置き換え */
    template < typename T, unsigned int Index >
    using IsElement = std::is_same<ElementType<Index>, T>;

	/*! エレメントの検索構造体 */
    template < typename T, unsigned int Index = 0 >
    struct FindElement : public std::conditional_t<
        IsElement<T, Index>::value,
        std::integral_constant< decltype(Index), Index>,
        FindElement<T, Index + 1>
    >{};
};

template < typename... Types >
using BlackboardPtr = std::unique_ptr<Blackboard<Types...>>;

#endif // !BLACKBOARD_H_
