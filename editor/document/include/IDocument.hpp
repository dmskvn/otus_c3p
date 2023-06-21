#pragma once

#include <optional>
#include <functional>
#include <vector>
#include <objects/Item.hpp>

namespace editor
{

struct IDocument
{
    virtual void Open () = 0;

    virtual void Close () = 0;
    
    virtual std::vector<Item> GetAllItemsItems () const = 0;

    virtual std::vector<Item> GetItemsInSelection (const Item& selection, const bool includePartial) const = 0;

    virtual std::optional<Item> GetItemByHash (const std::hash<Item> hash) const = 0;
    
    virtual void AddItem (const Item& toAdd) = 0;

    virtual void RemoveItem (const Item& toAdd) = 0;
};

};