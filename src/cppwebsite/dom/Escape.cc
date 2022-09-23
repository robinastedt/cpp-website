#include "Escape.hh"

#include <codecvt>
#include <locale>

namespace cppwebsite::dom
{
    namespace
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utf32convert;

        std::u32string
        toUtf32(std::string_view str) {
            return utf32convert.from_bytes(str.data(), str.data() + str.length());
        }

        std::string
        fromUtf32(std::u32string_view str) {
            return utf32convert.to_bytes(str.data(), str.data() + str.length());
        }

        bool
        isSafeForHtml(char32_t code) {
            switch (code) {
                case '"':
                case '&':
                case '\'':
                case '<':
                case '>': return false;
            }
            return code >= ' ' && code <= '~';
        }

    } // namespace

    std::string
    escapeForHtml(std::string_view str) {
        std::u32string str32{toUtf32(str)};

        using UniIter = std::u32string::iterator;
        UniIter begin = str32.begin();
        UniIter end = str32.end();

        std::string escaped;

        for (UniIter it = begin; it != end; ++it) {
            const char32_t code = *it;
            if (isSafeForHtml(code)) {
                continue;
            }
            std::u32string_view previous(begin, it);
            escaped.append(fromUtf32(previous))
                    .append("&#")
                    .append(std::to_string(code))
                    .append(";");
            begin = it + 1;
        }
        std::u32string_view rest(begin, end);
        escaped.append(fromUtf32(rest));

        return escaped;
    }

} // namespace cppwebsite::dom

