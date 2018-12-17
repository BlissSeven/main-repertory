#ifndef MY_DATATYPE_HPP
#define MY_DATATYPE_HPP

template<typename T>
class DataValue
{
private:
    T data;
    UA_Variant value;
    string id;
    UA_Client* client;
public:
    DataValue(const UA_Client* _client,const string& _id,const T& _data)
        :id(_id),data(_data){


    }
    ~DataValue(){delete client;}
    DataValue(const DataValue& d)
    {

    }
    void operator=(const DataValue& d)
    {

    }
    operator int() const
    {
        return static_cast<int>(data);
    }
    operator float() const
    {
        return static_cast<float>(data);
    }
    operator bool() const
    {
        return static_cast<bool>(data);
    }
    void operator=(const T& _data)
    {
        data=static_cast<T>(_data);
        UA_NodeId NodeId2=UA_NODEID_STRING_ALLOC(1,"the.answer");
        UA_Variant uv;
        UA_Int32 i=14;
        UA_Variant_setScalar(&uv,&i,&UA_TYPES[UA_TYPES_INT32]);
        UA_Client_writeValueAttribute(client,NodeId2,&uv);
    }
};
void test()
{
    DataValue<UA_Boolean> d1("the.answer",false);

    int a=d1;
    float b=d1;
    cout<<a<<" :: "<<b<<endl;
}
#endif // MY_DATATYPE_HPP
