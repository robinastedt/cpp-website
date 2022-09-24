#pragma once

#include <string>
#include <memory>
#include <vector>

namespace cppwebsite
{
    class Document;
} // namespace cppwebsite

namespace cppwebsite::dom
{

    class DocumentObject {
    protected:
        DocumentObject();

    public:
        using ptr = std::unique_ptr<DocumentObject>;

        virtual ~DocumentObject();

        virtual void append(Document& document) const = 0;
    };

    using DocumentObjects = std::vector<DocumentObject::ptr>;
} // namespace cppwebsite::dom
