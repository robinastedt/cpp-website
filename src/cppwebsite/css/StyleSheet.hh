#pragma once

#include <cppwebsite/css/Style.hh>
#include <cppwebsite/css/TagState.hh>

namespace cppwebsite::css
{
    class StyleSheet {
        std::vector<Style> m_styles;

    public:
        StyleSheet();

        /**
         * @brief Applies a style connected to the unique id of the tag.
         * Examples: <a id="my_id"> -> "a:hover #my_id",
         *           <p id="my_id"> -> "p #my_id"
         * 
         * @param properties The properties applies to the style.
         * @param tag The unique tag instance which the style is applied to.
         * @param state The state of the tag during which the style is applied.
         */
        void addUniqueTag(
            Properties properties,
            const dom::Tag& tag,
            TagState state = TagState::Default);

        /**
         * @brief Applies a style connected to all tags of the same type.
         * Examples: <a id="my_id"> -> "a:hover",
         *           <p id="my_id"> -> "p"
         * 
         * @param properties The properties applies to the style.
         * @param tag The tag of which type the style is applied to.
         * @param state The state of the tags during which the style is applied.
         */
        void addTagType(
            Properties properties,
            const dom::Tag& tag,
            TagState state = TagState::Default);

        // Creates Style object connected to a specific

        /**
         * @brief Applies a style connected to all objects belonging to a class.
         * 
         * @param properties The properties applies to the style.
         * @param clazz The class whose member tags the style is applied to.
         * @param state The state of the tags during which the style is applied.
         */
        void addClass(
            Properties properties,
            const dom::Class& clazz,
            TagState state = TagState::Default);

        void append(dom::Document& document) const;
    };
} // namespace cppwebsite::css
