#undef _UNICODE

#include <stdio.h>
#include "opcda.h"
#include "OPCClient.h"
#include "OPCHost.h"
#include "OPCServer.h"
#include "OPCGroup.h"
#include "OPCItem.h"
#include <sys\timeb.h>
#include "LocalSyncOPCCLient.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <ctime>
#include <exception>

using std::vector;
using std::string;
using std::endl;
using std::cout;
using std::map;
using std::exception;

void test()
{
        LocalSyncOPCCLient* client = new LocalSyncOPCCLient;
        client->Init();
        if (!client->Connect("Matrikon.OPC.Simulation.1"))
        {
             cout<<"connect error!"<<endl;
             return;
        }

        map<string,int> item_type=client->get_item_type();
        for(auto it=item_type.begin();it!=item_type.end();it++)
            cout<<(*it).first<<" : "<<(*it).second<<endl;

        // sync write and sync read
        client->WriteUint16("Bucket Brigade.UInt2", 998);
        std:std::cout << client->ReadUint16("Bucket Brigade.UInt2")<<endl;


        client->WirteFloat("ai.float1",3.56f);
        std::cout << client->ReadFloat("ai.float1")<<endl;

         cout<<"read write on data*********"<<endl;
         try {
              std::cout << client->ReadBool("Write Only.Boolean")<<endl;
         }
         catch (OPCException e) {
             cout<<e.reasonString()<<endl;
             cout<<"test"<<endl;
            return ;
         }



        // disconnect and stop
        client->DisConnect();
        client->Stop();
        delete client;

}
int main2()
{

    test();




    return 0;
}
