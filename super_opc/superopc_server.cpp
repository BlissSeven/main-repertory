
#include "superopc_server.hpp"


 UA_StatusCode opcda_readfloat(UA_Server *server,
                const UA_NodeId *sessionId, void *sessionContext,
                const UA_NodeId *nodeId, void *nodeContext,
                UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                UA_DataValue *dataValue)
{
    UA_StatusCode res=0;
    const int len=static_cast<int>(nodeId->identifier.string.length);
    UA_Byte* const ch=nodeId->identifier.string.data;
    string id(ch,ch+len);
    cout<<id<<" call read float"<<endl;

    long access=SuperOPC_Server::get_server_instance().read_accessleveel(id.c_str());
    if(! bool(access & OPC_READABLE))
    {
        cout<<id.c_str()<<" can not read"<<endl;
        return UA_STATUSCODE_BADNOTREADABLE;
    }

    float test;
    try {
        test=SuperOPC_Server::get_server_instance().readVariable_float(id.c_str());//readVariable_float(id.c_str());
    } catch (OPCException& e) {
        cout<<e.reasonString()<<endl;
        return UA_STATUSCODE_BADUNEXPECTEDERROR;

    }


    res=UA_Variant_setScalarCopy(&dataValue->value, &test,&UA_TYPES[UA_TYPES_FLOAT]);
    dataValue->hasValue = true;
    return res;
}
 UA_StatusCode opcda_writefloat(UA_Server *server,
                const UA_NodeId *sessionId, void *sessionContext,
                const UA_NodeId *nodeId, void *nodeContext,
                const UA_NumericRange *range, const UA_DataValue *data)
{
    const int len=static_cast<int>(nodeId->identifier.string.length);
    UA_Byte* const ch=nodeId->identifier.string.data;
    string id(ch,ch+len);
    cout<<id<<" call write float ";

    long access=SuperOPC_Server::get_server_instance().read_accessleveel(id.c_str());
    if(! bool(access & OPC_WRITEABLE))
    {
        cout<<id.c_str()<<" can not write"<<endl;
        return UA_STATUSCODE_BADNOTWRITABLE;
    }

    float test=*static_cast<float*>(data->value.data);
    cout<<"write value= "<<test<<endl;
    try {
        SuperOPC_Server::get_server_instance().writeVariable_float(id.c_str(),test);

    } catch (OPCException& e) {
        cout<<e.reasonString()<<endl;
        return UA_STATUSCODE_BADUNEXPECTEDERROR;
    }

    return UA_STATUSCODE_GOOD;
}

  UA_StatusCode opcda_readbool(UA_Server *server,
                const UA_NodeId *sessionId, void *sessionContext,
                const UA_NodeId *nodeId, void *nodeContext,
                UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                UA_DataValue *dataValue)
{
    UA_StatusCode res=0;
    const int len=static_cast<int>(nodeId->identifier.string.length);
    UA_Byte* const ch=nodeId->identifier.string.data;
    string id(ch,ch+len);
    cout<<id<<" call read bool"<<endl;

    long access=SuperOPC_Server::get_server_instance().read_accessleveel(id.c_str());
    if(! bool(access & OPC_READABLE))
    {
        cout<<id.c_str()<<" can not read"<<endl;
        return UA_STATUSCODE_BADNOTREADABLE;
    }

    bool test;
    try {
         test=SuperOPC_Server::get_server_instance().readVariable_bool(id.c_str());
    } catch (OPCException& e) {
        cout<<e.reasonString()<<endl;
        return UA_STATUSCODE_BADUNEXPECTEDERROR;

    }

    res=UA_Variant_setScalarCopy(&dataValue->value, &test,&UA_TYPES[UA_TYPES_BOOLEAN]);
    dataValue->hasValue = true;
    return res;
}
  UA_StatusCode opcda_writebool(UA_Server *server,
                const UA_NodeId *sessionId, void *sessionContext,
                const UA_NodeId *nodeId, void *nodeContext,
                const UA_NumericRange *range, const UA_DataValue *data)
{
    const int len=static_cast<int>(nodeId->identifier.string.length);
    UA_Byte* const ch=nodeId->identifier.string.data;
    string id(ch,ch+len);
    cout<<id<<" call write bool ";

    long access=SuperOPC_Server::get_server_instance().read_accessleveel(id.c_str());
    if(! bool(access & OPC_WRITEABLE))
    {
        cout<<id.c_str()<<" can not write"<<endl;
        return UA_STATUSCODE_BADNOTWRITABLE;
    }

    bool test=*static_cast<bool*>(data->value.data);
    cout<<"write value= "<<test<<endl;
    try {
        SuperOPC_Server::get_server_instance().writeVariable_bool(id.c_str(),test);
    } catch (OPCException& e) {
        cout<<e.reasonString()<<endl;
        return UA_STATUSCODE_BADUNEXPECTEDERROR;

    }

    return UA_STATUSCODE_GOOD;
}
  UA_StatusCode opcda_readint16(UA_Server *server,
                const UA_NodeId *sessionId, void *sessionContext,
                const UA_NodeId *nodeId, void *nodeContext,
                UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                UA_DataValue *dataValue)
{
    UA_StatusCode res=0;
    const int len=static_cast<int>(nodeId->identifier.string.length);
    UA_Byte* const ch=nodeId->identifier.string.data;
    string id(ch,ch+len);
    cout<<id<<" call read int16"<<endl;

    long access=SuperOPC_Server::get_server_instance().read_accessleveel(id.c_str());
    if(! bool(access & OPC_READABLE))
    {
        cout<<id.c_str()<<" can not read"<<endl;
        return UA_STATUSCODE_BADNOTREADABLE;
    }

   UA_Int16 test;
    try {
        test=SuperOPC_Server::get_server_instance().readVariable_int16(id.c_str());
    } catch (OPCException& e) {
       cout<<e.reasonString()<<endl;
       return UA_STATUSCODE_BADUNEXPECTEDERROR;

   }

    res=UA_Variant_setScalarCopy(&dataValue->value, &test,&UA_TYPES[UA_TYPES_INT16]);
    dataValue->hasValue = true;
    return res;
}
   UA_StatusCode opcda_writeint16(UA_Server *server,
                const UA_NodeId *sessionId, void *sessionContext,
                const UA_NodeId *nodeId, void *nodeContext,
                const UA_NumericRange *range, const UA_DataValue *data)
{
    const int len=static_cast<int>(nodeId->identifier.string.length);
    UA_Byte* const ch=nodeId->identifier.string.data;
    string id(ch,ch+len);
    cout<<id<<" call write int16 ";

    long access=SuperOPC_Server::get_server_instance().read_accessleveel(id.c_str());
    if(! bool(access & OPC_WRITEABLE))
    {
        cout<<id.c_str()<<" can not write"<<endl;
        return UA_STATUSCODE_BADNOTWRITABLE;
    }

    UA_Int16 test=*static_cast<UA_Int16*>(data->value.data);
    cout<<"write value= "<<test<<endl;
    try {
        SuperOPC_Server::get_server_instance().writeVariable_int16(id.c_str(),test);
    } catch (OPCException& e) {
        cout<<e.reasonString()<<endl;
        return UA_STATUSCODE_BADUNEXPECTEDERROR;

    }

    return UA_STATUSCODE_GOOD;
}
UA_StatusCode SuperOPC_Server::addVariable_float(const char* id)
{
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT_ALLOC("en-US", id);
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_NodeId currentNodeId = UA_NODEID_STRING_ALLOC(1, id);
    UA_QualifiedName currentName = UA_QUALIFIEDNAME_ALLOC(1, id);
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);

    UA_DataSource DataSource;
    DataSource.read = opcda_readfloat;
    DataSource.write = opcda_writefloat;
    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId,
    parentReferenceNodeId, currentName,
    variableTypeNodeId, attr,
    DataSource, NULL, NULL);
    return UA_STATUSCODE_GOOD;
}
UA_StatusCode SuperOPC_Server::addVariable_bool(const char* id)
{
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT_ALLOC("en-US", id);
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_NodeId currentNodeId = UA_NODEID_STRING_ALLOC(1, id);
    UA_QualifiedName currentName = UA_QUALIFIEDNAME_ALLOC(1, id);
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);

    UA_DataSource DataSource;
    DataSource.read = opcda_readbool;
    DataSource.write = opcda_writebool;
    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId,
    parentReferenceNodeId, currentName,
    variableTypeNodeId, attr,
    DataSource, NULL, NULL);
    return UA_STATUSCODE_GOOD;
}
UA_StatusCode SuperOPC_Server::addVariable_int16(const char* id)
{
    UA_VariableAttributes attr = UA_VariableAttributes_default;
    attr.displayName = UA_LOCALIZEDTEXT_ALLOC("en-US", id);
    attr.accessLevel = UA_ACCESSLEVELMASK_READ | UA_ACCESSLEVELMASK_WRITE;
    UA_NodeId currentNodeId = UA_NODEID_STRING_ALLOC(1, id);
    UA_QualifiedName currentName = UA_QUALIFIEDNAME_ALLOC(1, id);
    UA_NodeId parentNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_OBJECTSFOLDER);
    UA_NodeId parentReferenceNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_ORGANIZES);
    UA_NodeId variableTypeNodeId = UA_NODEID_NUMERIC(0, UA_NS0ID_BASEDATAVARIABLETYPE);

    UA_DataSource DataSource;
    DataSource.read = opcda_readint16;
    DataSource.write = opcda_writeint16;
    UA_Server_addDataSourceVariableNode(server, currentNodeId, parentNodeId,
    parentReferenceNodeId, currentName,
    variableTypeNodeId, attr,
    DataSource, NULL, NULL);
    return UA_STATUSCODE_GOOD;
}

