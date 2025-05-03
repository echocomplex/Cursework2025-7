#ifndef DATABASE_HXX
#define DATABASE_HXX


#include <List.hxx>
#include <Employee.hxx>
#include <Filer.hxx>
#include <map>
#include <iostream>
#include <Crypter.hxx>
#include <ctime>


class Database {
protected:
    Filer file;
    std::string filename;
    std::string filename_enc;
    List <Employee> data;
    Crypter crypter;
public:
    Database (void);
    Database (const std::string& filename);
    Database (const List <Employee>& unit, const std::string& filename);
    Database (const Database& unit);
    ~Database (void);
    Database& operator= (const Database& unit) noexcept;
    Employee& operator[] (const unsigned int index) noexcept;
    friend std::ostream& operator<< (std::ostream& os, const Database& unit);
    const Employee& operator[] (const unsigned int index) const noexcept;
    void append (const Employee& unit) noexcept;
    void remove (const unsigned int index) noexcept;
    unsigned int size (void) noexcept;
    void getEmployeesByDepartment (List <Employee>& unit, const std::string& department) const noexcept;
    void getEmployeesWithHigherEducation (List <Employee>& unit) const noexcept;
    unsigned short countOldEmployees (void) const noexcept;
};


#endif // DATABASE_HXX