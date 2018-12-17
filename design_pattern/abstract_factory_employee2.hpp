#ifndef ABSTRACT_FACTORY_EMPLOYEE2_HPP
#define ABSTRACT_FACTORY_EMPLOYEE2_HPP

class IDBconnection{};
class IDBcommand{};
class IDBdatareader{};


class IDBFactory{
public:
    virtual IDBconnection* CreateConnection()=0;
    virtual IDBcommand* CreateCommand()=0;
    virtual IDBdatareader* CreateDataReader()=0;
};

class SQLFactory:public IDBFactory{
public:
    virtual IDBconnection* CreateConnection()=0;
    virtual IDBcommand* CreateCommand()=0;
    virtual IDBdatareader* CreateDataReader()=0;
};

class SQLconnection:public IDBconnection{};
class SQLcommand:public IDBcommand{};
class SQLdatareader:public IDBdatareader{};


class EmployeeDAO{
    IDBFactory* factory;
public:
    vector<EmployeeDO> GetEmployees()
    {
        IDBconnection* connection =
            factory->CreateConnection();
        connection->ConnectionString = "...";

        IDBcommand* command =
            factory->CreateCommand();

        command->CommandText="...";
        command->SetConnection(connection);

        IDBdatareader* reader = command->ExecuteReader();
        while (reader->Read()){

        }

    }
};


#endif // ABSTRACT_FACTORY_EMPLOYEE2_HPP
