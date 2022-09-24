#include "Id.hh"

#include <cppwebsite/dom/Property.hh>
#include <map>
#include <stdexcept>

namespace cppwebsite::dom
{
    namespace
    {
        constexpr size_t _anon_index = 0;
        std::map<std::string, size_t> _indices{
            {"", 0}
        };
        std::vector<std::string> _names{
            {""}
        };

        size_t
        getIndex(std::string name) {
            size_t index = _indices.insert({name, _indices.size()}).first->second;
            _names.resize(std::max(_names.size(), index + 1));
            _names[index] = std::move(name);
            return index;
        }

        const std::string&
        getName(size_t index) {
            if (index >= _names.size()) {
                throw std::runtime_error{"Index out of bounds: index=" + std::to_string(index) + ", size=" + std::to_string(_names.size())};
            }
            return _names[index];
        }
    } // namespace
    

    Id::Id(std::string name)
    : m_index(getIndex(name))
    {}

    bool
    Id::isAnonymous() const {
        return m_index == _anon_index;
    }

    Property
    Id::getProperty() const {
        return Property{"id", getName(m_index)};
    }

    Id Id::anonymous() {
        return Id{""};
    }
    
} // namespace cppwebsite::dom
