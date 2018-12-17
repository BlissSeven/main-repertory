#include <iostream>
#include "open62541/open62541.h"


using namespace std;

#pragma comment(lib, "ws2_32.lib")


UA_Int16 read_int16(UA_Client* client,const char* id)
{
    UA_Variant value;
    UA_Variant_init(&value);
    UA_StatusCode retval;
    UA_NodeId NodeId2=UA_NODEID_STRING_ALLOC(1,id);

    retval = UA_Client_readValueAttribute(client, NodeId2, &value);
    if(retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_INT16]))
    {
        UA_Int16 result=*(UA_Int16* )value.data;
         UA_Variant_deleteMembers(&value);
        return result;
    }
    return retval;
}
UA_Float read_float(UA_Client* client,const char* id)
{
    UA_Variant value;
    UA_Variant_init(&value);
    UA_StatusCode retval;
    UA_NodeId NodeId2=UA_NODEID_STRING_ALLOC(1,id);

    retval = UA_Client_readValueAttribute(client, NodeId2, &value);
    if(retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_FLOAT]))
    {
        UA_Float result=*(UA_Float* )value.data;
        UA_Variant_deleteMembers(&value);
        return result;
    }
    return retval;
}
UA_Boolean read_bool(UA_Client* client,const char* id)
{
    UA_Variant value;
    UA_Variant_init(&value);
    UA_StatusCode retval;
    UA_NodeId NodeId2=UA_NODEID_STRING_ALLOC(1,id);

    retval = UA_Client_readValueAttribute(client, NodeId2, &value);
    if(retval == UA_STATUSCODE_GOOD && UA_Variant_hasScalarType(&value, &UA_TYPES[UA_TYPES_BOOLEAN]))
    {

        UA_Boolean result=*(UA_Boolean* )value.data;
        UA_Variant_deleteMembers(&value);
        return result;
    }
    return false;
}
UA_StatusCode write_int16(UA_Client* client,const char* id,const UA_Int16& data)
{
    UA_Variant value;
    UA_Variant_init(&value);
    UA_Variant_setScalarCopy(&value, &data, &UA_TYPES[UA_TYPES_INT16]);

    UA_StatusCode retval;
    UA_NodeId NodeId2=UA_NODEID_STRING_ALLOC(1,id);

    retval = UA_Client_writeValueAttribute(client, NodeId2, &value);
    UA_Variant_deleteMembers(&value);
    if(retval == UA_STATUSCODE_GOOD)
         return true;
    return retval;
}
UA_StatusCode write_bool(UA_Client* client,const char* id,const UA_Boolean& data)
{
    UA_Variant value;
    UA_Variant_init(&value);
    UA_Variant_setScalarCopy(&value, &data, &UA_TYPES[UA_TYPES_BOOLEAN]);

    UA_StatusCode retval;
    UA_NodeId NodeId2=UA_NODEID_STRING_ALLOC(1,id);

    retval = UA_Client_writeValueAttribute(client, NodeId2, &value);
    UA_Variant_deleteMembers(&value);
    if(retval == UA_STATUSCODE_GOOD)
         return true;
    return retval;
}
UA_StatusCode write_float(UA_Client* client,const char* id,const UA_Float& data)
{
    UA_Variant value;
    UA_Variant_init(&value);
    UA_Variant_setScalarCopy(&value, &data, &UA_TYPES[UA_TYPES_FLOAT]);

    UA_StatusCode retval;
    UA_NodeId NodeId2=UA_NODEID_STRING_ALLOC(1,id);

    retval = UA_Client_writeValueAttribute(client, NodeId2, &value);
    UA_Variant_deleteMembers(&value);
    if(retval == UA_STATUSCODE_GOOD)
         return true;
    return retval;
}

int opc_ua_client_test()
{
    cout << "Super OPC OPC UA Client Test" << endl;

    UA_Client *client = UA_Client_new(UA_ClientConfig_default);
    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://localhost:4840");
    if(retval != UA_STATUSCODE_GOOD) {
    UA_Client_delete(client);
        return (int)retval;
    }

    cout<<"read_bool(client,\"bool_1\") : "<<read_bool(client,"bool_1")<<endl;
    cout<<"read_int16(client,\"int16_1\") : "<<read_int16(client,"int16_1")<<endl;
    cout<<"read_float(client,\"float1\") : "<<read_float(client,"float1")<<endl;

    write_bool(client,"bool_1",true);
    write_int16(client,"int16_1",7);
    write_float(client,"float1",7.77f);


    cout<<"read_bool(client,\"bool_1\") : "<<read_bool(client,"bool_1")<<endl;
    cout<<"read_int16(client,\"int16_1\") : "<<read_int16(client,"int16_1")<<endl;
    cout<<"read_float(client,\"float1\") : "<<read_float(client,"float1")<<endl;
    UA_Client_delete(client); /* Disconnects the client internally */
    return UA_STATUSCODE_GOOD;
}
int main2()
{
    cout << "Hello World!" << endl;

    UA_Client *client = UA_Client_new(UA_ClientConfig_default);
    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://localhost:4840");
    if(retval != UA_STATUSCODE_GOOD) {
    UA_Client_delete(client);
        return (int)retval;
    }
     cout<<"read_float(client,\"float1\") : "<<read_float(client,"float1")<<endl;

     write_float(client,"float1",7.77f);
     //Triangle Waves.Int2
/*
    cout<<"read_bool(client,\"bool_1\") : "<<read_bool(client,"bool_1")<<endl;
    cout<<"read_int16(client,\"int16_1\") : "<<read_int16(client,"int16_1")<<endl;
    cout<<"read_float(client,\"float1\") : "<<read_float(client,"float1")<<endl;

    write_bool(client,"bool_1",true);
    write_int16(client,"int16_1",7);
    write_float(client,"float1",7.77f);


    cout<<"read_bool(client,\"bool_1\") : "<<read_bool(client,"bool_1")<<endl;
    cout<<"read_int16(client,\"int16_1\") : "<<read_int16(client,"int16_1")<<endl;
    cout<<"read_float(client,\"float1\") : "<<read_float(client,"float1")<<endl;
*/

    char ch;
    cin>>ch;
    /* Clean up */

    UA_Client_delete(client); /* Disconnects the client internally */
    return UA_STATUSCODE_GOOD;
    return 0;
}
