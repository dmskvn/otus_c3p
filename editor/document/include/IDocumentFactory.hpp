#pragma once

#include "IDocument.hpp"

namespace editor
{

struct IDocumentFactory
{
    virtual std::unique_ptr<IDocument> Create () = 0;
};

};