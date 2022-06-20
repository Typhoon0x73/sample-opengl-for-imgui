#ifndef PARAMETERMAP_H_
#define PARAMETERMAP_H_

#include <cassert>
#include <unordered_map>
#include <string>
#include <memory>

using ParameterMapKeyType = std::string;

template < typename T >
class ParameterMap
{
public:

    using Parameter = T;

public:

    ParameterMap() : m_Parameters() {}

	~ParameterMap() { m_Parameters.clear(); }

    ParameterMap& add(const ParameterMapKeyType& key, Parameter& value)
    {
        m_Parameters.insert(std::pair<ParameterMapKeyType, Parameter&>(key, value));
        return *this;
    }

    ParameterMap& erase(const ParameterMapKeyType& key)
    {
        m_Parameters.erase(key);
        return *this;
    }

    Parameter& get(const ParameterMapKeyType& key)
    {
        auto it = m_Parameters.find(key);
        assert(it != m_Parameters.end());
        return it->second;
    }

    const Parameter& get(const ParameterMapKeyType& key) const
    {
        auto it = m_Parameters.find(key);
        assert(it != m_Parameters.end());
        return it->second;
    }

    Parameter& operator[] (const ParameterMapKeyType& key)
    { 
        return get(key);
    }

    const Parameter& operator[] (const ParameterMapKeyType& key) const 
    {
        return get(key);
    }

    size_t getSize() const
    { 
        return m_Parameters.size();
    }

    std::unordered_map<ParameterMapKeyType, Parameter>& parameters()
    { 
        return m_Parameters;
    }

private:

    std::unordered_map< ParameterMapKeyType, Parameter > m_Parameters;
};

template < typename T > 
using ParameterMapPtr = std::unique_ptr<ParameterMap<T>>;

#endif // !PARAMETERMAP_H_
