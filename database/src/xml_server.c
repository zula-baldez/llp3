#include "../include/aggregator/public/database.h"
#include "../include/xml/from_xml_server.h"
#include "../include/net/public/server_socket_operations.h"
#include "../include/xml/to_xml_server.h"
#include <pthread.h>

static void *handle_client(void *socket_desc) {
    int clientSocket = *(int *) socket_desc;
    free(socket_desc);
    struct TableHeader* selectTableHeader;
    struct RecordData* selectRecordData;

    while (1) {
        char *buffer = malloc(MAX_BUFFER_SIZE); //todo array
        int err;
        err = receiveData(clientSocket, buffer);
        if (err != 0) {
            printf("Unable to receive data");
            close(clientSocket);
            pthread_exit(NULL);
        }

        printf("Received data: %s\n", buffer);
        xmlDocPtr doc = xmlParseMemory(buffer, strlen(buffer));
        xmlDocPtr serverResponse = xmlNewDoc(BAD_CAST "1.0");
        xmlNodePtr xmlNodeSqlResp = xmlNewNode(NULL, BAD_CAST "sqlResponse");
        xmlDocSetRootElement(serverResponse, xmlNodeSqlResp);

        struct request request;
        err = parseXml(doc, &request);
        if (err != 0) {
            addMessage(xmlNodeSqlResp, "Unable to parse xml");
            close(clientSocket);
            pthread_exit(NULL);

        }
        printf("Request type: %d\n", request.type);
        if (request.type == CREATE_TABLE) {
            struct createTableRequest createTableRequest = request.createTableRequest;
            err = createTable(createTableRequest.tableName, createTableRequest.columnNum, createTableRequest.types,
                              createTableRequest.names);
            if (err != 0) {
                addMessage(xmlNodeSqlResp, "Unable to create table");
            }
            addMessage(xmlNodeSqlResp, "Table successfully created!");

        } else if (request.type == DROP_TABLE) {
            struct dropTableRequest dropTableRequest = request.dropTableRequest;
            err = deleteTable(dropTableRequest.tableName);
            if (err != 0) {
                addMessage(xmlNodeSqlResp, "Unable to drop table");
            }
            addMessage(xmlNodeSqlResp, "Table successfully dropped!");
        } else if (request.type == INSERT) {
            struct insertRequest insertRequest = request.insertRequest;
            struct TableHeader *insertTableHeader;
            err = getTable(&insertTableHeader, insertRequest.tableName);
            if (err != 0) {
                addMessage(xmlNodeSqlResp, "Unable to find table");
            }
            struct RecordData *insertRecordData = prepareRecordDataStructure(insertTableHeader);
            for (int i = 0; i < insertRequest.dataCount; ++i) {
                insertRecordData->data[i] = insertRequest.data[i];
            }
            err = addRow(insertTableHeader, insertRecordData, NULL);
            if (err != 0) {
                addMessage(xmlNodeSqlResp, "Unable to insert");
            }
            addMessage(xmlNodeSqlResp, "Successfully inserted");
            freeTable(insertTableHeader);
        } else if (request.type == SELECT) {
            struct selectRequest selectRequest = request.selectRequest;
            if(selectRecordData == NULL) {
                err = getTable(&selectTableHeader, selectRequest.tableName);
                if (err != 0) {
                    addMessage(xmlNodeSqlResp, "Unable to find table");
                }
                selectRecordData = prepareRecordDataStructure(selectTableHeader);
            }
            if (selectWithConditions(selectRecordData, selectTableHeader, selectRequest.conditionCount,
                                     selectRequest.conditions) == 0) {
                addRecordData(xmlNodeSqlResp, selectRecordData);
            } else {
                addMessage(xmlNodeSqlResp, "End of table");
                freeTable(selectTableHeader);
                freeRecordData(selectRecordData);

                selectTableHeader = NULL;
                selectRecordData = NULL;
            }
        } else if (request.type == DELETE) {
            struct deleteRequest deleteRequest = request.deleteRequest;
            struct TableHeader *tableHeader;
            err = getTable(&tableHeader, deleteRequest.tableName);
            if (err != 0) {
                addMessage(xmlNodeSqlResp, "Unable to find table");
            }
            err = deleteRow(tableHeader, deleteRequest.conditionCount, deleteRequest.conditions);
            if (err != 0) {
                addMessage(xmlNodeSqlResp, "Unable to delete");
            }
            freeTable(tableHeader);
            addMessage(xmlNodeSqlResp, "Successfully deleted");
        } else if (request.type == UPDATE) {
            struct updateRequest updateRequest = request.updateRequest;
            struct TableHeader *tableHeader;
            err = getTable(&tableHeader, updateRequest.tableName);
            if (err != 0) {
                addMessage(xmlNodeSqlResp, "Unable to find table");
            }
            struct UpdateColumnValue c = updateRequest.updateColumnValues[1];
            err = updateRow(tableHeader, updateRequest.updateColumnsCount, updateRequest.updateColumnValues,
                            updateRequest.conditionCount, updateRequest.conditions);
            if (err != 0) {
                addMessage(xmlNodeSqlResp, "Unable to update");
            }
            freeTable(tableHeader);
            addMessage(xmlNodeSqlResp, "Successfully updated");
        } else if (request.type == JOIN) {
            struct joinRequest joinRequest = request.joinRequest;
            struct JoinResult joinResult;
            int32_t selectColumnsNum = joinRequest.selectColumnsNum;
            struct TableAliasAndColumn *selectColumns = joinRequest.selectColumns;
            int32_t joinTablesNum = joinRequest.joinTablesNum;
            struct JoinTablesHeaders *joinTableHeaders = malloc(
                    sizeof(struct JoinTablesHeaders) * joinRequest.joinTablesNum);
            for (int i = 0; i < request.joinRequest.joinTablesNum; i++) {
                struct TableHeader *tableHeader;
                err = getTable(&tableHeader, joinRequest.joinTables[i].name);
                if (err != 0) {
                    addMessage(xmlNodeSqlResp, "Unable to find table");
                }
                joinTableHeaders[i].tableHeader = tableHeader;
            }
            int32_t joinConditionNum = joinRequest.joinConditionNum;
            struct JoinCondition *joinCondition = joinRequest.joinCondition;
            int32_t filtersNum = joinRequest.filtersNum;
            struct JoinWhereCondition *joinWhereCondition = joinRequest.joinWhereCondition;
            joinTables(&joinResult, selectColumnsNum, selectColumns, joinTablesNum, joinTableHeaders, joinConditionNum,
                       joinCondition, filtersNum, joinWhereCondition);

            while (readRecord(joinResult.recordData, joinResult.tableHeader)) {
                addRecordData(xmlNodeSqlResp, joinResult.recordData);
            }
            for (int i = 0; i < request.joinRequest.joinTablesNum; i++) {
                freeTable(joinTableHeaders[i].tableHeader);
            }
            freeRecordData(joinResult.recordData);
            freeTable(joinResult.tableHeader);
            free(joinTableHeaders);
        } else {
            addMessage(xmlNodeSqlResp, "Unknown request type");
        }
        xmlChar *xmlBuffer = malloc(MAX_BUFFER_SIZE * sizeof(xmlChar));
        int size;
        xmlDocDumpFormatMemory(serverResponse, &xmlBuffer, &size, 1);
        printf("Response: %s\n", xmlBuffer);
        err = sendData(clientSocket, (char *) xmlBuffer);
        if (err != 0) {
            printf("Unable to send data");
        }
        freeRequest(&request);
        free(xmlBuffer);
        free(buffer);
    }
}

int main(int argc, char **argv) {
    printf("START");

    ++argv;
    --argc;
    if (argc != 3) {
        printf("Wrong arguments");
        return 1;
    }
    char *addr = argv[0];
    int port = atoi(argv[1]);
    char *file = argv[2];
    int fd = initializeServerSocket(addr, port);
    if (fd < 0) {
        printf("Unable to initialize socket");
        return -fd;
    }
    int err = listenForConnections(fd);
    if (err != 0) {
        printf("Unable to listen for connections");
        return -err;
    }
    printf("PEPE\n");
    openDatabaseFileOrCreate(file);

    while (1) {
        printf("ACCEPTING CONNECTIONS\n");
        int clientSocket = acceptConnection(fd);
        if (clientSocket < 0) {
            printf("Unable to accept connection");
        }
        int *clientSocketPtr = malloc(sizeof(int));
        *clientSocketPtr = clientSocket;
        pthread_t tid;
        if (pthread_create(&tid, NULL, handle_client, (void *) clientSocketPtr) != 0) {
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }
        pthread_detach(tid);
    }
}
