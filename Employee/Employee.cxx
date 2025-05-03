#include "Employee.hxx"

Date::Date (void) noexcept {
    this->day = 1;
    this->month = 1;
    this->year = 1;
}

Date::Date (const unsigned short day, const unsigned short month, const unsigned short year) {
    if (1 <= day && day <= 31) this->day = day;
    else this->day = 1;

    if (1 <= month && month <= 12) this->month = month;
    else this->month = 1;

    if (1 <= year) this->year = year;
    else this->year = 1;
}

unsigned short Date::getDay (void) const noexcept {
    return this->day;
}

unsigned short Date::getMonth (void) const noexcept {
    return this->month;
}

unsigned short Date::getYear (void) const noexcept {
    return this->year;
}

void Date::setDay (const unsigned short day) noexcept {
    this->day = day;
}

void Date::setMonth (const unsigned short month) noexcept {
    this->month = month;
}

void Date::setYear (const unsigned short year) noexcept {
    this->year = year;
}
    
Employee::Employee (const std::string full_name, const unsigned short day, const unsigned short month, const unsigned short year, const unsigned short day_e, const unsigned short month_e, const unsigned short year_e, const Education education, const std::string department, const std::string post, const std::string phone) noexcept {
    this->full_name = full_name;
    this->birth_date.setDay(day);
    this->birth_date.setMonth(month);
    this->birth_date.setYear(year);
    this->employement_date.setDay(day_e);
    this->employement_date.setMonth(month_e);
    this->employement_date.setYear(year_e);
    this->education = education;
    this->department = department;
    this->post = post;
    this->phone = phone;
}

Employee& Employee::operator= (const Employee& unit) noexcept {
    this->full_name = unit.full_name;
    this->birth_date.setDay(unit.birth_date.getDay());
    this->birth_date.setMonth(unit.birth_date.getMonth());
    this->birth_date.setYear(unit.birth_date.getYear());
    this->employement_date.setDay(unit.employement_date.getDay());
    this->employement_date.setMonth(unit.employement_date.getMonth());
    this->employement_date.setYear(unit.employement_date.getYear());
    this->education = unit.education;
    this->department = unit.department;
    this->post = unit.post;
    this->phone = unit.phone;
    return *this;
}
std::ostream& operator<< (std::ostream& os, const Employee& unit) {
    os << 
        unit.full_name << ", " <<
        unit.dateToString(unit.birth_date) << ", " <<
        unit.dateToString(unit.employement_date) << ", " <<
        unit.educationToString(unit.education) << ", " <<
        unit.department << ", " <<
        unit.post << ", " <<
        unit.phone
    ;
    return os;
}

std::string Employee::getFullName (void) const noexcept {
    return this->full_name;
}

Date Employee::getBirthDate (void) const noexcept {
    return this->birth_date;
}

Date Employee::getEmployementDate (void) const noexcept {
    return this->employement_date;
}
    
Education Employee::getEducation (void) const noexcept {
    return this->education;
}
    
std::string Employee::getDepartment (void) const noexcept {
    return this->department;
}
    
std::string Employee::getPost (void) const noexcept {
    return this->post;
}
    
std::string Employee::getPhone (void) const noexcept {
    return this->phone;
}
    
void Employee::setFullName (const std::string& full_name) noexcept {
    this->full_name = full_name;
}
    
void Employee::setBirthDate (const unsigned short day, const unsigned short month, const unsigned short year) noexcept {
    this->birth_date.setDay(day);
    this->birth_date.setMonth(month);
    this->birth_date.setYear(year);
}
    
void Employee::setEmployementDate (const unsigned short day, const unsigned short month, const unsigned short year) noexcept {
    this->employement_date.setDay(day);
    this->employement_date.setMonth(month);
    this->employement_date.setYear(year);
}
    
void Employee::setEducation (const Education education) noexcept {
    this->education = education;
}
    
void Employee::setDepartment (const std::string& department) noexcept {
    this->department = department;
}
    
void Employee::setPost (const std::string& post) noexcept {
    this->post = post;
}
    
void Employee::setPhone (const std::string& phone) noexcept {
    this->phone = phone;
}

std::string Employee::educationToString (const Education edu) noexcept {
    switch (edu) {
        case Education::Secondary: return "Secondary";
        case Education::SecondarySpecial: return "Secondary Special";
        case Education::SecondaryTechnical: return "Secondary Technical";
        case Education::Higher: return "Higher";
        default: return "Unknown";
    }
}

std::string Employee::dateToString (const Date& unit) noexcept {
    std::string toOut = std::to_string(unit.getDay()) + '.' + std::to_string(unit.getMonth()) + '.' + std::to_string(unit.getYear());
    return toOut;
}
