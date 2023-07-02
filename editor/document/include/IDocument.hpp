#pragma once

#include <optional>
#include <functional>
#include <vector>
#include <objects/Item.hpp>

namespace editor
{

/**
 * @brief Интерфейс документа. Объявлены базовые функции для работы с объектами в документе 
 * 
 */
struct IDocument
{
    /**
     * @brief Открывает файл на редактирование
     * 
     */
    virtual void Open () = 0;

    /**
     * @brief Закрывает файл
     * 
     */
    virtual void Close () = 0;
    
    /**
     * @brief Возвращает все элементы в данном документе
     * 
     * @return std::vector<Item> все элементы данного документа
     */
    virtual std::vector<Item> GetAllItemsItems () const = 0;

    /**
     * @brief Возвращает все элементы в данной области
     * 
     * @param selection область выделения
     * @param includePartial включать ли частично попадающие под выделение 
     * @return std::vector<Item> элементы данной области
     */
    virtual std::vector<Item> GetItemsInSelection (const Item& selection, const bool includePartial) const = 0;

    /**
     * @brief Возвращает элемент по хешу
     * 
     * @param hash Хеш элемента
     * @return std::optional<Item> Элемент с данным хешом. Может отсутствовать
     */
    virtual std::optional<Item> GetItemByHash (const std::hash<Item> hash) const = 0;
    
    /**
     * @brief Добавляет элемент к документу
     * 
     * @param toAdd Элемент для добавления
     */
    virtual void AddItem (const Item& toAdd) = 0;

    /**
     * @brief Удаляет элемент из документа
     * 
     * @param toAdd Элемент для удаления
     */
    virtual void RemoveItem (const Item& toAdd) = 0;
};

};