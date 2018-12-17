#include <iostream>
#include "open62541/open62541.h"
#include "superopc_server.hpp"

#undef _UNICODE

#include <stdio.h>
#include "opcda/opcda.h"
#include "opcda/OPCClient.h"
#include "opcda/OPCHost.h"
#include "opcda/OPCServer.h"
#include "opcda/OPCGroup.h"
#include "opcda/OPCItem.h"
#include <sys\timeb.h>
#include "opcda/LocalSyncOPCCLient.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <signal.h>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

UA_Boolean running=true;
static void stopHandler(int sig)
{
    UA_LOG_INFO(UA_Log_Stdout,UA_LOGCATEGORY_USERLAND,"received ctrl-c");
    running=false;
}

int opc_ua_server_test()
{
    cout << "Hello World!" << endl;
    signal(SIGINT,stopHandler);
    signal(SIGTERM,stopHandler);

    UA_ServerConfig* config=UA_ServerConfig_new_default();
    UA_Server* server=UA_Server_new(config);



    UA_StatusCode retval=UA_Server_run(server,&running);
    UA_Server_delete(server);
    UA_ServerConfig_delete(config);
    return 0;
}

int opc_da_client_test()
{
       cout << "Super OPC OPC DA Client Test" << endl;
        LocalSyncOPCCLient* client = new LocalSyncOPCCLient;
        client->Init();
        if (!client->Connect("Matrikon.OPC.Simulation.1"))
        {
             cout<<"connect error!"<<endl;
             return -1;
        }


        auto m1=client->get_item_property();

        for(auto it=m1.begin();it!=m1.end();it++)
        {
            auto tt=(*it).second;
            cout<<(*it).first<<" : "<<get<0>(tt)<<" "<<get<1>(tt)<<" "<<get<2>(tt)<<endl;
        }

        // sync write and sync read
        client->WriteUint16("Bucket Brigade.UInt2", 998);
        std:std::cout << client->ReadUint16("Bucket Brigade.UInt2")<<endl;

        client->WirteFloat("ai.float_1",3.56f);
        std::cout << client->ReadFloat("ai.float_1")<<endl;


        // disconnect and stop
        client->DisConnect();
        client->Stop();
        delete client;
}

int main()
{
    signal(SIGINT,stopHandler);
    //signal(SIGTERM,stopHandler);

     SuperOPC_Server::get_server_instance().init();
    auto m1=SuperOPC_Server::get_server_instance().get_item_property();

    for(auto it=m1.begin();it!=m1.end();it++)
    {
        auto tt=(*it).second;
        cout<<(*it).first<<" : "<<get<0>(tt)<<" "<<get<1>(tt)<<" "<<get<2>(tt)<<endl;
    }

    SuperOPC_Server::get_server_instance().run_server(running);

   cout<<"server down"<<endl;
   char ch;
   cin>>ch;

    //opc_ua_server_test();
    //opc_da_client_test();

}
