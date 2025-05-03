#ifndef EMPLOYEE_HXX
#define EMPLOYEE_HXX


#include <string>
#include <iostream>


class Date {
private: 
    unsigned short day, month, year;
public:
    Date (void) noexcept;
    Date (const unsigned short day, const unsigned short month, const unsigned short year);
    unsigned short getDay (void) const noexcept;
    unsigned short getMonth (void) const noexcept;
    unsigned short getYear (void) const noexcept;
    void setDay (const unsigned short day) noexcept;
    void setMonth (const unsigned short month) noexcept;
    void setYear (const unsigned short year) noexcept;
};

enum class Education {
    Secondary,
    SecondarySpecial,
    SecondaryTechnical,
    Higher
};


class Employee {
private:
    std::string full_name;
    Date birth_date;
    Date employement_date;
    Education education;
    std::string department;
    std::string post;
    std::string phone;
public:
    Employee (void) noexcept = default;
    Employee (const std::string full_name, const unsigned short day, const unsigned short month, const unsigned short year, const unsigned short day_e, const unsigned short month_e, const unsigned short year_e, const Education education, const std::string department, const std::string post, const std::string phone) noexcept;
    ~Employee (void) noexcept = default;
    Employee& operator= (const Employee& unit) noexcept;
    friend std::ostream& operator<< (std::ostream& os, const Employee& unit);
    std::string getFullName (void) const noexcept;
    Date getBirthDate (void) const noexcept;
    Date getEmployementDate (void) const noexcept;
    Education getEducation (void) const noexcept;
    std::string getDepartment (void) const noexcept;
    std::string getPost (void) const noexcept;
    std::string getPhone (void) const noexcept;
    void setFullName (const std::string& full_name) noexcept;
    void setBirthDate (const unsigned short day, const unsigned short month, const unsigned short year) noexcept;
    void setEmployementDate (const unsigned short day, const unsigned short month, const unsigned short year) noexcept;
    void setEducation (const Education education) noexcept;
    void setDepartment (const std::string& department) noexcept;
    void setPost (const std::string& post) noexcept;
    void setPhone (const std::string& phone) noexcept;
    static std::string educationToString (const Education edu) noexcept;
    static std::string dateToString (const Date& unit) noexcept;
};

#endif // EMPLOYEE_HXX