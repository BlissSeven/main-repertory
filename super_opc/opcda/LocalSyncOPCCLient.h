#pragma once
#ifndef OPC_LOCAL_CLIENT_H
#define OPC_LOCAL_CLIENT_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdint>
#include <tuple>

#include "opcda.h"
#include "OPCClient.h"
#include "OPCHost.h"
#include "OPCServer.h"
#include "OPCGroup.h"
#include "OPCItem.h"

using std::map;
using std::tuple;
using std::get;
using std::cout;
using std::endl;
using std::string;
using std::make_tuple;

class LocalSyncOPCCLient
{
public:
	// constructor and destructor
	LocalSyncOPCCLient();
	virtual ~LocalSyncOPCCLient();

	// Controller actions
	bool Init();
	bool Connect(std::string serverName);
	bool DisConnect();
	bool IsConnected();
	bool Stop();

	// OPC API
	bool IsOPCRuning();
	virtual bool IsOPCConnectedPLC();// this function relis on the specific device
	virtual bool ItemNameFilter(std::string item_name);// if a item's name cannot pass the name fitler, it will not be added.

	// Basic Read Write API
	inline bool SyncWriteItem(std::string item_name, VARIANT* var);
	inline bool SyncReadItem(std::string item_name, VARIANT* var);

	bool ReadBool(std::string item_name);
	bool WriteBool(std::string item_name, bool item_value);

	float ReadFloat(std::string item_name);
	bool WirteFloat(std::string item_name, float item_value);

	uint16_t ReadUint16(std::string item_name);
	bool WriteUint16(std::string item_name, uint16_t item_value);
    
    int16_t Readint16(std::string item_name);
	bool Writeint16(std::string item_name, int16_t item_value);

	bool ReadUint16Array(std::string item_name, uint16_t* item_value_array, int array_size);
	bool WriteUint16Array(std::string item_name, uint16_t* item_value_array, int array_size);
    const std::vector<std::string>& get_items(){
        return items;
    }

    const  map<string,tuple<short,short,long> > & get_item_property()//datatype/quality/accesslevel
    {
        return item_property;
    }
protected:
	std::map<std::string, COPCItem *> name_item_map_;
    std::vector<std::string>items;


    map<string,tuple<short,short,long> > item_property;// item name/ data type/data quality/access level/
	COPCGroup* p_group_;
	unsigned long refresh_rate_;
	COPCHost* p_host_;

    COPCServer* p_opc_server_;//????

	bool is_env_ready;

	bool CleanOPCMember();
    bool DetectService(const char* ServiceName);
	VARIANT read_tmp_variant_;
};

#endif //OPCONTROLLER_H
