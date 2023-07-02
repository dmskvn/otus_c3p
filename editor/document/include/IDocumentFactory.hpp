#pragma once

#include "IDocument.hpp"

namespace editor
{

enum class EDocumentType :  int
{
    XML,
    JSON,
    YAML
};

/**
 * @brief  Фабрика для создания документа
 * 
 */
struct IDocumentFactory
{
    /**
     * @brief Создает документ для чтения объектов
     * 
     * @param type Тип документа
     * @param path Путь к документу
     * @return std::unique_ptr<IDocument> Документ
     */
    virtual std::unique_ptr<IDocument> Create (const EDocumentType type, const std::string& path) = 0;
};

};