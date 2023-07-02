#pragma once

#include <plot/IPlot.hpp>
#include <functional>

namespace editor
{
    /**
     * @brief Объект документа
     * 
     */
    struct IItem
    {
        /**
         * @brief Рисует документ на поверхности
         * 
         * @param plot Поверхность рисования
         */
        virtual void draw(const IPlot& plot) = 0;

        /**
         * @brief Возвращает хеш объекта
         * 
         * @return std::hash<Item> Хеш объекта
         */
        virtual std::hash<Item> get_hash() = 0;
    };
}