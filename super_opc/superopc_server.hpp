#ifndef SUPEROPC_SERVER_HPP
#define SUPEROPC_SERVER_HPP

#undef _UNICODE

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "open62541/open62541.h"
#include "opcda/LocalSyncOPCCLient.h"
#include "exception"
#include "opcda/opcda.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::exception;
using std::make_tuple;

class SuperOPC_Server
{
    private:
      enum{DATA_TYPE,DATA_QUALITY,DATA_ACCESSLEVEL};
      UA_Server* server;
      UA_ServerConfig* config;

      LocalSyncOPCCLient* client ;

      SuperOPC_Server(){
          //config=UA_ServerConfig_new_default();//Creates a server config on the default port 4840 with no server
          config=UA_ServerConfig_new_minimal(4840,NULL);
          server=UA_Server_new(config);


          client = new LocalSyncOPCCLient;

            client->Init();
      }
public:

   static SuperOPC_Server& get_server_instance()
   {
       static SuperOPC_Server instance;
       return instance;
   }

   SuperOPC_Server(const SuperOPC_Server& sos)=delete;

  ~SuperOPC_Server(){
       cout<<"SuperOPC_Serverdestructor called "<<endl;

       UA_Server_delete(server);
       UA_ServerConfig_delete(config);

 //UA_Server_run(server,&server_state);

       client->DisConnect();
       client->Stop();
       delete client;
   }

   SuperOPC_Server& operator=(const SuperOPC_Server& sos)=delete;


   UA_StatusCode addVariable_float(const char* id);
   UA_StatusCode addVariable_bool(const char* id);
   UA_StatusCode addVariable_int16(const char* id);

   UA_StatusCode run_server(UA_Boolean& run)
   {

        UA_StatusCode retval=UA_Server_run(server,&run);
        if(retval!=UA_STATUSCODE_GOOD)
        {
            cout<<"opc ua server run fail code: "<<retval<<endl;
            return retval;
        }

       return UA_STATUSCODE_GOOD;
   }

   void init(const char* da_server_name="Matrikon.OPC.Simulation.1")
   {
       int res=client->Connect(da_server_name);
       if(!res)
       {
           cout<<"connect to opc da server fail"<<endl;
           return ;
       }
      cout<<"connect to opc da server ok"<<endl;

      const map<string,tuple<short,short,long>> item_property=client->get_item_property();
       for(auto it=item_property.begin();it!=item_property.end();it++)
       {
           cout<<(*it).first<<" : "<<get<0>((*it).second)<<" "<<get<1>((*it).second)<<" "<<get<2>((*it).second)<<endl;
           switch (get<DATA_TYPE>((*it).second))
           {
             case VT_I2: addVariable_int16((*it).first.c_str());
             case VT_BOOL: addVariable_bool((*it).first.c_str());
             case VT_R4: addVariable_float((*it).first.c_str());
             default:
               cout<<"unsupported data type "<<(*it).first.c_str()<<endl;
               break;
           }
       }
       cout<<string(8,'*')<<"add opc ua server item ok!"<<string(8,'*')<<endl;

   }
   const map<string,tuple<short,short,long> >& get_item_property()const
   {
       return client->get_item_property();
   }
// set public to user can access opcda data
   UA_Int16 readVariable_int16(const char* id)const
   {
       return client->Readint16(id);
   }

   UA_Float readVariable_float(const char* id)const
   {
       return client->ReadFloat(id);
   }
   UA_Boolean readVariable_bool(const char* id)const
   {
       return client->ReadBool(id);
   }
   void writeVariable_int16(const char* id,const UA_Int16& value)
   {
       client->Writeint16(id,value);
   }
   void writeVariable_float(const char* id,const UA_Float& value)
   {
       client->WirteFloat(id,value);
   }
   void writeVariable_bool(const char* id,const UA_Boolean& value)
   {
       client->WriteBool(id,value);
   }
   long read_accessleveel(const char* id)
   {
        auto m=client->get_item_property();
       return get<DATA_ACCESSLEVEL>(m[id]);// tuple 0=datatype/1=quality/2=accesslevel
   }
   short read_datatype(const char* id)
   {
        auto m=client->get_item_property();
       return get<DATA_TYPE>(m[id]);// tuple 0=datatype/1=quality/2=accesslevel
   }
   short read_dataquality(const char* id)
   {
        auto m=client->get_item_property();
       return get<DATA_QUALITY>(m[id]);// tuple 0=datatype/1=quality/2=accesslevel
   }

 public:
   friend  UA_StatusCode opcda_readfloat(UA_Server *server,
                   const UA_NodeId *sessionId, void *sessionContext,
                   const UA_NodeId *nodeId, void *nodeContext,
                   UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                   UA_DataValue *dataValue);
   friend UA_StatusCode opcda_writefloat(UA_Server *server,
                   const UA_NodeId *sessionId, void *sessionContext,
                   const UA_NodeId *nodeId, void *nodeContext,
                   const UA_NumericRange *range, const UA_DataValue *data);
   friend UA_StatusCode opcda_readbool(UA_Server *server,
                  const UA_NodeId *sessionId, void *sessionContext,
                  const UA_NodeId *nodeId, void *nodeContext,
                  UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                  UA_DataValue *dataValue);
   friend UA_StatusCode opcda_writebool(UA_Server *server,
                  const UA_NodeId *sessionId, void *sessionContext,
                  const UA_NodeId *nodeId, void *nodeContext,
                  const UA_NumericRange *range, const UA_DataValue *data);
   friend UA_StatusCode opcda_readint16(UA_Server *server,
                  const UA_NodeId *sessionId, void *sessionContext,
                  const UA_NodeId *nodeId, void *nodeContext,
                  UA_Boolean sourceTimeStamp, const UA_NumericRange *range,
                  UA_DataValue *dataValue);
   friend UA_StatusCode opcda_writeint16(UA_Server *server,
                 const UA_NodeId *sessionId, void *sessionContext,
                 const UA_NodeId *nodeId, void *nodeContext,
                 const UA_NumericRange *range, const UA_DataValue *data);

};
#endif // SUPEROPC_UA_SERVER_HPP
