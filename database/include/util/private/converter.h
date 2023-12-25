//
// Created by moyak on 19.09.2023.
//

#ifndef LAB1_CONVERTER_H
#define LAB1_CONVERTER_H

#include "../../file-work/private/block.h"
#include "../../structures/private/table_structures.h"

struct TableHeader *convertFileNodeToTableHeader(struct FileNode *fileNode);

void *getBlockData(struct BlockHeader *blockHeader);

struct BlockHeader *convertTableHeaderToBlockHeader(struct TableHeader *tableHeader);

struct FileNode *convertBlockHeaderToFileNode(struct BlockHeader *blockHeader);

#endif //LAB1_CONVERTER_H
