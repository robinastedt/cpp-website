#include "UniqueBase.hh"

#include <cppwebsite/dom/Property.hh>
#include <map>
#include <stdexcept>

namespace cppwebsite::dom
{
    namespace
    {
        constexpr size_t _anon_index = 0;

        template<typename T>
        std::map<std::string, size_t> _indices {
            {"", _anon_index}
        };

        template<typename T>
        std::vector<std::string> _names{
            {""}
        };

        size_t
        getIndex(std::map<std::string, size_t>& indices, std::vector<std::string>& names, std::string name) {
            size_t index = indices.insert({name, indices.size()}).first->second;
            names.resize(std::max(names.size(), index + 1));
            names[index] = std::move(name);
            return index;
        }

    } // namespace

    
    template<typename T>
    UniqueBase<T>::UniqueBase(std::string name)
    : m_index(getIndex(_indices<T>, _names<T>, name))
    {}

    template<typename T>
    bool
    UniqueBase<T>::isAnonymous() const {
        return m_index == _anon_index;
    }
    
    template<typename T>
    Property
    UniqueBase<T>::getProperty() const {
        if (m_index >= _names<T>.size()) {
            throw std::runtime_error{"Index out of bounds: index=" + std::to_string(m_index) + ", size=" + std::to_string(_names<T>.size())};
        }
        return Property{getPropertyName(), _names<T>[m_index]};
    }

    template<typename T>
    T UniqueBase<T>::anonymous() {
        return T{""};
    }
    
} // namespace cppwebsite::dom
