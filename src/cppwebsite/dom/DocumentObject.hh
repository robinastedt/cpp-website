#pragma once

#include <string>
#include <memory>

namespace cppwebsite::dom
{
    class DocumentObject {
    protected:
        DocumentObject();

    public:
        using ptr = std::unique_ptr<DocumentObject>;

        virtual ~DocumentObject();

        virtual void append(std::string& document) const = 0;
    };
} // namespace cppwebsite::dom
