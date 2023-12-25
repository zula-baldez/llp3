#include "from_xml_server.h"


void freeRequest(struct request *request) {
    if (request->type == CREATE_TABLE) {
        free(request->createTableRequest.types);
        free(request->createTableRequest.names);
    }
    if (request->type == INSERT) {
        for (int i = 0; i < request->insertRequest.dataCount; i++) {
            free(request->insertRequest.data[i]);
        }
        free(request->insertRequest.data);
    }
    if (request->type == SELECT)
        free(request->selectRequest.conditions);

    if (request->type == DELETE) {
        free(request->deleteRequest.conditions);
    }
    if (request->type == UPDATE) {
        free(request->updateRequest.updateColumnValues);
        free(request->updateRequest.conditions);
    }
    if (request->type == JOIN) {
        free(request->joinRequest.selectColumns);
        free(request->joinRequest.joinTables);
        free(request->joinRequest.joinCondition);
        free(request->joinRequest.joinWhereCondition);
    }
}

enum DataType parse_data_type(xmlChar *name) {
    if (xmlStrcmp(name, (const xmlChar *) "INT") == 0) {
        return INT_TYPE;
    } else if (xmlStrcmp(name, (const xmlChar *) "DOUBLE") == 0) {
        return DOUBLE_TYPE;
    } else if (xmlStrcmp(name, (const xmlChar *) "BOOL") == 0) {
        return BOOL_TYPE;
    } else if (xmlStrcmp(name, (const xmlChar *) "STRING") == 0) {
        return STRING_TYPE;
    } else {
        return INVALID_TYPE;
    }
}

static xmlNodePtr getChildByName(xmlNodePtr parent, const char *childName) {
    if (parent == NULL || childName == NULL) {
        return NULL;
    }
    for (xmlNodePtr child = parent->children; child != NULL; child = child->next) {
        if (child->type == XML_ELEMENT_NODE && xmlStrcmp(child->name, (const xmlChar *) childName) == 0) {
            return child;
        }
    }
    return NULL;
}

static int validateXml(xmlDocPtr xmlDocument) {
    xmlSchemaPtr schema = NULL;
    xmlSchemaParserCtxtPtr parserCtxt = NULL;
    xmlSchemaValidCtxtPtr validCtxt = NULL;

    // Load and parse the XSD schema
    parserCtxt = xmlSchemaNewParserCtxt("./home/egor/CLionProjects/llp/parser/xml/query_schema.xsd");
    if (parserCtxt == NULL) {
        fprintf(stderr, "Failed to create XSD parser context.\n");
        return PARSE_ERROR;
    }

    schema = xmlSchemaParse(parserCtxt);
    if (schema == NULL) {
        fprintf(stderr, "Failed to parse XSD schema.\n");
        xmlSchemaFreeParserCtxt(parserCtxt);
        return PARSE_ERROR;
    }

    // Create a validation context
    validCtxt = xmlSchemaNewValidCtxt(schema);
    if (validCtxt == NULL) {
        fprintf(stderr, "Failed to create validation context.\n");
        xmlSchemaFree(schema);
        xmlSchemaFreeParserCtxt(parserCtxt);
        return PARSE_ERROR;
    }

    // Validate the XML document against the XSD schema
    if (xmlSchemaValidateDoc(validCtxt, xmlDocument) == 0) {
        printf("Validation successful.\n");
    } else {
        fprintf(stderr, "Validation failed.\n");
    }

    xmlSchemaFreeValidCtxt(validCtxt);
    xmlSchemaFree(schema);
    xmlSchemaFreeParserCtxt(parserCtxt);
    return 0;
}

static int parse_create_table(xmlNodePtr rootNode, struct request *request) {
    request->type = CREATE_TABLE;
    xmlNodePtr tableName = getChildByName(rootNode, "tableName");
    if (tableName == NULL) {
        return PARSE_ERROR;
    }
    request->createTableRequest.tableName = (char *) tableName->children->content;
    xmlNodePtr fields = getChildByName(rootNode, "fields");
    xmlNodePtr field = fields->children;
    int childCount = 0;
    while (field) {
        childCount++;
        field = field->next;
    }
    request->createTableRequest.columnNum = childCount;
    request->createTableRequest.types = malloc(sizeof(enum DataType) * childCount);
    request->createTableRequest.names = malloc(sizeof(char *) * childCount);
    field = fields->children;
    int i = 0;
    while (field) {
        xmlNodePtr name = getChildByName(field, "name");
        xmlNodePtr type = getChildByName(field, "type");
        if (name == NULL || type == NULL) {
            return PARSE_ERROR;
        }
        request->createTableRequest.names[i] = (char *) name->children->content;
        enum DataType dataType = parse_data_type(type->children->content);
        if (dataType == INVALID_TYPE) {
            return PARSE_ERROR;
        }
        request->createTableRequest.types[i] = dataType;
        field = field->next;
        i++;
    }
    return 0;
}

static void *parseValue(xmlNodePtr data, enum DataType dataType) {
    if (dataType == INT_TYPE) {
        int32_t *intData = malloc(sizeof(int32_t));
        *intData = atoi((char *) data->children->content);
        return intData;
    } else if (dataType == DOUBLE_TYPE) {
        double *doubleData = malloc(sizeof(double));
        *doubleData = atof((char *) data->children->content);
        return doubleData;
    } else if (dataType == BOOL_TYPE) {
        int32_t *boolData = malloc(sizeof(int32_t));
        *boolData = atoi((char *) data->children->content);
        return boolData;
    } else {
        return (char *) data->children->content;
    }
}

static int parse_insert(xmlNodePtr rootNode, struct request *request) {
    request->type = INSERT;
    xmlNodePtr tableName = getChildByName(rootNode, "tableName");
    if (tableName == NULL) {
        return PARSE_ERROR;
    }
    request->insertRequest.tableName = (char *) tableName->children->content;
    xmlNodePtr values = getChildByName(rootNode, "insertValues");
    xmlNodePtr value = values->children;
    int childCount = 0;
    while (value) {
        childCount++;
        value = value->next;
    }
    request->insertRequest.data = malloc(sizeof(void *) * childCount);
    request->insertRequest.dataCount = childCount;
    value = values->children;
    for (int i = 0; i < childCount; i++) {
        xmlNodePtr type = getChildByName(value, "type");
        if (type == NULL) {
            return PARSE_ERROR;
        }
        enum DataType dataType = parse_data_type(type->children->content);
        if (dataType == INVALID_TYPE) {
            return PARSE_ERROR;
        }
        xmlNodePtr name = getChildByName(value, "name");
        if (name == NULL) {
            return PARSE_ERROR;
        }
        xmlNodePtr data = getChildByName(value, "value");
        if (data == NULL) {
            return PARSE_ERROR;
        }
        request->insertRequest.data[i] = parseValue(data, dataType);
        value = value->next;
    }
    return 0;
}

static int parse_delete_table(xmlNodePtr rootNode, struct request *request) {
    request->type = DROP_TABLE;
    xmlNodePtr tableName = getChildByName(rootNode, "tableName");
    if (tableName == NULL) {
        return PARSE_ERROR;
    }
    request->dropTableRequest.tableName = (char *) tableName->children->content;
    return 0;
}

static enum DataType dataTypeFromStr(char *str) {
    if (strcmp(str, "INT") == 0) {
        return INT_TYPE;
    } else if (strcmp(str, "DOUBLE") == 0) {
        return DOUBLE_TYPE;
    } else if (strcmp(str, "BOOL") == 0) {
        return BOOL_TYPE;
    } else if (strcmp(str, "STRING") == 0) {
        return STRING_TYPE;
    } else {
        return INVALID_TYPE;
    }
}

static struct Operand *parse_operand(xmlNodePtr node) {
    struct Operand *operand = malloc(sizeof(struct Operand));
    xmlNodePtr isColumnName = getChildByName(node, "isColumnName");
    xmlNodePtr value = getChildByName(node, "value");

    if (xmlStrcmp(isColumnName->children->content, (const xmlChar *) "true") == 0) {
        operand->isOperandAName = true;
        operand->operandValue.columnName = (char *) value->children->content;
    } else {
        operand->isOperandAName = false;
        xmlNodePtr type = getChildByName(node, "type");
        struct FreeVariable *freeVariable = malloc(sizeof(struct FreeVariable));
        freeVariable->dataType = dataTypeFromStr((char *) type->children->content);
        freeVariable->operand = parseValue(value, freeVariable->dataType);
        operand->operandValue.freeVariable = freeVariable;
    }
    return operand;
}

static enum Operator parseOperator(xmlNodePtr node) {
    if (xmlStrcmp(node->children->content, (const xmlChar *) "&gt;") == 0) {
        return MORE;
    } else if (xmlStrcmp(node->children->content, (const xmlChar *) "&lt;") == 0) {
        return LESS;
    } else if (xmlStrcmp(node->children->content, (const xmlChar *) "==") == 0) {
        return EQUALS;
    } else {
        return INVALID_OPERATOR;
    }
}


static int parse_select(xmlNodePtr rootNode, struct request *request) {
    request->type = SELECT;
    xmlNodePtr unreadData = getChildByName(rootNode, "unreadData");
    xmlNodePtr blockPtr = getChildByName(rootNode, "blockPtr");

    if(unreadData != NULL) {
        request->selectRequest.unreadData = (char *) strtoull((char *) unreadData->children->content, NULL, 16);
        request->selectRequest.blockHeader = (char *) strtoull((char *) blockPtr->children->content, NULL, 16);
    }

    xmlNodePtr tableName = getChildByName(rootNode, "tableName");
    if (tableName == NULL) {
        return PARSE_ERROR;
    }
    request->selectRequest.tableName = (char *) tableName->children[0].content;
    xmlNodePtr conditions = getChildByName(rootNode, "filters");
    xmlNodePtr condition = conditions->children;
    int childCount = 0;
    while (condition) {
        childCount++;
        condition = condition->next;
    }
    request->selectRequest.conditions = malloc(sizeof(struct Condition) * childCount);
    request->selectRequest.conditionCount = childCount;
    condition = conditions->children;
    int i = 0;
    while (condition) {
        xmlNodePtr left = getChildByName(condition, "leftOp");
        xmlNodePtr right = getChildByName(condition, "rightOp");
        xmlNodePtr op = getChildByName(condition, "operator");

        struct Operand *leftOp = parse_operand(left);
        struct Operand *rightOp = parse_operand(right);
        enum Operator anOperator = parseOperator(op);
        request->selectRequest.conditions[i] = (struct Condition) {
                .left = *leftOp,
                .right = *rightOp,
                .op = anOperator
        };
        condition = condition->next;
    }
    return 0;
}

static int parse_delete(xmlNodePtr rootNode, struct request *request) {
    request->type = DELETE;
    xmlNodePtr tableName = getChildByName(rootNode, "tableName");
    if (tableName == NULL) {
        return PARSE_ERROR;
    }
    request->deleteRequest.tableName = (char *) tableName->children->content;
    xmlNodePtr conditions = getChildByName(rootNode, "filters");
    xmlNodePtr condition = conditions->children;
    int childCount = 0;
    while (condition) {
        childCount++;
        condition = condition->next;
    }
    request->deleteRequest.conditions = malloc(sizeof(struct Condition) * childCount);
    request->deleteRequest.conditionCount = childCount;
    condition = conditions->children;
    int i = 0;
    while (condition) {
        xmlNodePtr left = getChildByName(condition, "leftOp");
        xmlNodePtr right = getChildByName(condition, "rightOp");
        xmlNodePtr op = getChildByName(condition, "operator");

        struct Operand *leftOp = parse_operand(left);
        struct Operand *rightOp = parse_operand(right);
        enum Operator anOperator = parseOperator(op);
        request->deleteRequest.conditions[i] = (struct Condition) {
                .left = *leftOp,
                .right = *rightOp,
                .op = anOperator
        };
        condition = condition->next;
    }
    return 0;
}

static int parse_update(xmlNodePtr rootNode, struct request *request) {
    request->type = UPDATE;
    xmlNodePtr tableName = getChildByName(rootNode, "tableName");
    if (tableName == NULL) {
        return PARSE_ERROR;
    }
    request->updateRequest.tableName = (char *) tableName->children->content;
    xmlNodePtr conditions = getChildByName(rootNode, "filters");
    xmlNodePtr condition = conditions->children;
    int childCount = 0;
    while (condition) {
        childCount++;
        condition = condition->next;
    }
    request->updateRequest.conditions = malloc(sizeof(struct Condition) * childCount);
    request->updateRequest.conditionCount = childCount;
    condition = conditions->children;
    int i = 0;
    while (condition) {
        xmlNodePtr left = getChildByName(condition, "leftOp");
        xmlNodePtr right = getChildByName(condition, "rightOp");
        xmlNodePtr op = getChildByName(condition, "operator");

        struct Operand *leftOp = parse_operand(left);
        struct Operand *rightOp = parse_operand(right);
        enum Operator anOperator = parseOperator(op);
        request->updateRequest.conditions[i] = (struct Condition) {
                .left = *leftOp,
                .right = *rightOp,
                .op = anOperator
        };
        condition = condition->next;
    }
    xmlNodePtr updateValues = getChildByName(rootNode, "updateValues");
    xmlNodePtr updateValue = updateValues->children;
    int updateValuesCount = 0;
    while (updateValue) {
        updateValuesCount++;
        updateValue = updateValue->next;
    }
    request->updateRequest.updateColumnValues = malloc(sizeof(struct UpdateColumnValue) * updateValuesCount);
    request->updateRequest.updateColumnsCount = updateValuesCount;
    updateValue = updateValues->children;
    int j = 0;
    while (updateValue) {
        xmlNodePtr name = getChildByName(updateValue, "name");
        xmlNodePtr value = getChildByName(updateValue, "value");
        xmlNodePtr isValueColumnName = getChildByName(updateValue, "isValueColumnName");
        if (name == NULL || value == NULL || isValueColumnName == NULL) {
            return PARSE_ERROR;
        }
        if (xmlStrcmp(isValueColumnName->children->content, (const xmlChar *) "true") == 0) {
            request->updateRequest.updateColumnValues[j] = (struct UpdateColumnValue) {
                    .name = (char *) name->children->content,
                    .assignedValue = {
                            .isOperandAName = true,
                            .operandValue = {
                                    .columnName = (char *) value->children->content
                            }
                    }
            };
        } else {
            xmlNodePtr type = getChildByName(updateValue, "type");
            if (type == NULL) {
                return PARSE_ERROR;
            }
            struct FreeVariable *freeVariable = malloc(sizeof(struct FreeVariable));
            freeVariable->dataType = dataTypeFromStr((char *) type->children->content);
            freeVariable->operand = parseValue(value, freeVariable->dataType);
            request->updateRequest.updateColumnValues[j] = (struct UpdateColumnValue) {
                    .name = (char *) name->children->content,
                    .assignedValue = {
                            .isOperandAName = false,
                            .operandValue = {
                                    .freeVariable = freeVariable
                            }
                    }
            };
        }
        updateValue = updateValue->next;
        j++;
    }
    return 0;
}

static int parse_join(xmlNodePtr rootNode, struct request *request) {
    request->type = JOIN;
    xmlNodePtr join = getChildByName(rootNode, "join");
    xmlNodePtr aliases = getChildByName(join, "aliases");
    xmlNodePtr alias = aliases->children;
    int aliasesNum = 0;
    while (alias) {
        aliasesNum++;
        alias = alias->next;
    }
    request->joinRequest.joinTables = malloc(sizeof(struct JoinTable) * aliasesNum);
    int i = 0;
    alias = aliases->children;
    while (alias) {
        xmlNodePtr name = getChildByName(alias, "table");
        xmlNodePtr aliasName = getChildByName(alias, "al");
        if (name == NULL || aliasName == NULL) {
            return PARSE_ERROR;
        }
        request->joinRequest.joinTables[i].name = (char *) name->children->content;
        request->joinRequest.joinTables[i].alias = (char *) aliasName->children->content;
        alias = alias->next;
    }

    xmlNodePtr selectColumns = getChildByName(rootNode, "return");
    xmlNodePtr selectColumn = selectColumns->children;
    int selectColumnsCount = 0;
    while (selectColumn) {
        selectColumnsCount++;
        selectColumn = selectColumn->next;
    }
    request->joinRequest.selectColumns = malloc(sizeof(struct TableAliasAndColumn) * selectColumnsCount);
    request->joinRequest.selectColumnsNum = selectColumnsCount;
    selectColumn = selectColumns->children;
    int k = 0;
    while (selectColumn) {
        xmlNodePtr tableAlias = getChildByName(selectColumn, "tableAlias");
        xmlNodePtr columnName = getChildByName(selectColumn, "field");
        if (tableAlias == NULL || columnName == NULL) {
            return PARSE_ERROR;
        }
        request->joinRequest.selectColumns[k] = (struct TableAliasAndColumn) {
                .aliasName = (char *) tableAlias->children->content,
                .columnName = (char *) columnName->children->content
        };
        selectColumn = selectColumn->next;
    }


    xmlNodePtr joinConditions = getChildByName(rootNode, "joinConditions");
    xmlNodePtr joinCondition = joinConditions->children;
    int joinConditionsCount = 0;
    while (joinCondition) {
        joinConditionsCount++;
        joinCondition = joinCondition->next;
    }
    request->joinRequest.joinCondition = malloc(sizeof(struct JoinCondition) * joinConditionsCount);
    request->joinRequest.joinConditionNum = joinConditionsCount;
    joinCondition = joinConditions->children;
    int j = 0;
    while (joinCondition) {
        xmlNodePtr operator = getChildByName(joinCondition, "operator");
        request->joinRequest.joinCondition[j] = (struct JoinCondition) {
                .leftOperand = {
                        .tableAlias = (char *) getChildByName(joinCondition, "leftAlias")->children->content,
                        .columnName = (char *) getChildByName(joinCondition, "leftColumn")->children->content
                },
                .rightOperand = {
                        .tableAlias = (char *) getChildByName(joinCondition, "rightAlias")->children->content,
                        .columnName = (char *) getChildByName(joinCondition, "rightColumn")->children->content
                },
                .operator = parseOperator(operator)
        };
        joinCondition = joinCondition->next;
    }
    xmlNodePtr whereConditions = getChildByName(rootNode, "filterConditions");
    xmlNodePtr whereCondition = whereConditions->children;
    int whereConditionsCount = 0;
    while (whereCondition) {
        whereConditionsCount++;
        whereCondition = whereCondition->next;
    }
    request->joinRequest.joinWhereCondition = malloc(sizeof(struct JoinWhereCondition) * whereConditionsCount);
    request->joinRequest.filtersNum = whereConditionsCount;
    whereCondition = whereConditions->children;
    int l = 0;
    while (whereCondition) {
        xmlNodePtr operator = getChildByName(whereCondition, "operator");
        struct TableAliasAndColumn *nameAndColumn = malloc(sizeof(struct TableAliasAndColumn));
        nameAndColumn->columnName = (char *) getChildByName(whereCondition, "columnName")->children->content;
        nameAndColumn->aliasName = (char *) getChildByName(whereCondition, "tableAlias")->children->content;
        struct FreeVariable *freeVariable = malloc(sizeof(struct FreeVariable));
        freeVariable->dataType = dataTypeFromStr((char *) getChildByName(whereCondition, "type")->children->content);
        freeVariable->operand = parseValue(getChildByName(whereCondition, "value"), freeVariable->dataType);

        request->joinRequest.joinWhereCondition[l] = (struct JoinWhereCondition) {
                .leftOperand = {
                        .isOperandAName = true,
                        .operandValue = {
                                .nameAndColumn = nameAndColumn
                        }
                },
                .rightOperand = {
                        .isOperandAName =
                        xmlStrcmp(getChildByName(whereCondition, "isRightColumnName")->children->content,
                                  (const xmlChar *) "true") == 0,
                        .operandValue = {
                                .freeVariable = freeVariable,
                        }
                },
                .operator = parseOperator(operator)
        };

    }
    return 0;

}

int parseXml(xmlDocPtr xmlDocument, struct request *request) {
//    int validateError = validateXml(xmlDocument);
//    if (validateError != 0) {
//        return validateError;
//    }
    xmlNodePtr rootNode = xmlDocGetRootElement(xmlDocument);
    xmlNodePtr type = getChildByName(rootNode, "requestType");
    if (type == NULL) {
        return PARSE_ERROR;
    }
    if (xmlStrcmp(type->children->content, (const xmlChar *) "CREATE_TABLE") == 0) {
        parse_create_table(rootNode, request);
    } else if (xmlStrcmp(type->children->content, (const xmlChar *) "DROP_TABLE") == 0) {
        parse_delete_table(rootNode, request);
    } else if (xmlStrcmp(type->children->content, (const xmlChar *) "INSERT") == 0) {
        parse_insert(rootNode, request);
    } else if (xmlStrcmp(type->children->content, (const xmlChar *) "SELECT") == 0) {
        parse_select(rootNode, request);
    } else if (xmlStrcmp(type->children->content, (const xmlChar *) "DELETE") == 0) {
        parse_delete(rootNode, request);
    } else if (xmlStrcmp(type->children->content, (const xmlChar *) "UPDATE") == 0) {
        parse_update(rootNode, request);
    } else if (xmlStrcmp(type->children->content, (const xmlChar *) "JOIN") == 0) {
        parse_join(rootNode, request);
    } else {
        return PARSE_ERROR;
    }
    return 0;
}
