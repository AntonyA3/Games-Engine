#include <stdio.h>
#include <sqlite3.h>
#include <iostream>

static int my_callback(void *pass_into_value, int column, char **argv, char **azColName){
    std::cout << "Called Back" << std::endl;
    std::cout << *((int*)pass_into_value) << std::endl;

    std::cout << column << std::endl;

    return 0;

}



int main(int argc, char const *argv[])
{
    // I expect to find out how to use SQL with c++
    sqlite3 * sql_lite_3_handle = NULL;
     std::cout << "Opening sqlite" << std::endl;

    int sql_status = sqlite3_open("SampleDatabase.db", &sql_lite_3_handle);
    if(sql_status != SQLITE_OK){ 
        std::cout << "Cannot Open Database: " << 
            sqlite3_errmsg(sql_lite_3_handle) << "\n";
        sqlite3_close(sql_lite_3_handle); 
        return 1;
    }
    std::cout << "SDL successfully opened" << std::endl;
    char * sql_error_msg = NULL;

    //Drop table if it exists
    sql_status = sqlite3_exec(
        sql_lite_3_handle,
        "DROP TABLE IF EXISTS ExampleTable;",
        my_callback,
        0,
        &sql_error_msg
    );

    if(sql_status != SQLITE_OK){ 
        std::cout << "SQL Statement Failed: " << 
            sql_error_msg << " \n";
        sqlite3_close(sql_lite_3_handle); 
        return 1;
    }


    std::cout << "Table Successfully Dropped" << std::endl;



    //Create a table
    int pass_into = 101;
    sql_status = sqlite3_exec(
        sql_lite_3_handle,
        "CREATE TABLE ExampleTable(id int); INSERT INTO ExampleTable values(10);",
        my_callback,
        (void*)&pass_into,
        &sql_error_msg
    );

    if(sql_status != SQLITE_OK){ 
        std::cout << "SQL Statement Failed: " << 
            sql_error_msg << " \n";
        sqlite3_close(sql_lite_3_handle); 
        return 1;
    }


    //select from table
    // There will only be a callback if I have a select query
    sql_status = sqlite3_exec(
        sql_lite_3_handle,
        "SELECT * FROM ExampleTable",
        my_callback,
        (void*)&pass_into,
        &sql_error_msg
    );

    if(sql_status != SQLITE_OK){ 
        std::cout << "SQL Statement Failed: " << 
            sql_error_msg << " \n";
        sqlite3_close(sql_lite_3_handle); 
        return 1;
    }

  
    std::cout << "Table Successfully Created and inserted value" << std::endl;

    //Drop a table


    sqlite3_close(sql_lite_3_handle);
    std::cout << "closing sqlite" << std::endl;


    return 0;
}
