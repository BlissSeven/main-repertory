#ifndef ABSTRACT_FACTORY_EMPLOYEE1_HPP
#define ABSTRACT_FACTORY_EMPLOYEE1_HPP



class EmployeeDAO{

public:
    vector<EmployeeDO> GetEmployees(){
        SqlConnection* connection =
            new SqlConnection();
        connection->ConnectionString = "...";

        SqlCommand* command =
            new SqlCommand();
        command->CommandText="...";
        command->SetConnection(connection);

        SqlDataReader* reader = command->ExecuteReader();
        while (reader->Read()){

        }

    }
};


#endif // ABSTRACT_FACTORY_EMPLOYEE1_HPP
