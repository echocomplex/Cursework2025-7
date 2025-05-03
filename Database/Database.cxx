#include "Database.hxx"

Database::Database (void) {
    this->filename = "database.txt";
    this->filename_enc = "database.enc";
    this->crypter.decrypt(this->filename_enc, this->filename);
    this->file.open(this->filename, true);
    this->file.readToList(this->data);
}

Database::Database (const std::string& filename) {
    this->filename = filename + ".txt";
    this->filename_enc = filename + ".enc";
    this->crypter.encrypt(this->filename_enc, this->filename);
    this->file.open(filename);
    this->file.readToList(this->data);
}

Database::Database (const List <Employee>& unit, const std::string& filename) {
    this->data = unit;
    this->filename = filename + ".txt";
    this->filename_enc = filename + ".enc";
    this->file.open(this->filename);
}

Database::Database (const Database& unit) {
    this->data = unit.data;
    this->file.open(unit.filename);
    this->filename = unit.filename;
    this->filename_enc = unit.filename_enc;
}

Database::~Database (void) {
    this->file.rewriteFromList(this->data);
    this->crypter.encrypt(this->filename, this->filename_enc);
}

Database& Database::operator= (const Database& unit) noexcept {
    if (this == &unit) return *this;
    this->data = unit.data;
    this->filename = unit.filename;
    this->filename_enc = unit.filename_enc;
    this->file.open(unit.filename);
    return *this;
}

Employee& Database::operator[] (const unsigned int index) noexcept {
    return this->data[index];
}

std::ostream& operator<< (std::ostream& os, const Database& unit) {
    for (unsigned int i = 0; i < unit.data.length(); ++i) os << i + 1 << ' ' << unit[i] << std::endl;
    return os;
}

const Employee& Database::operator[] (const unsigned int index) const noexcept {
    return this->data[index];
}

void Database::append (const Employee& unit) noexcept {
    this->data.append(unit);
}

void Database::remove (const unsigned int index) noexcept {
    this->data.remove(index);
}

unsigned int Database::size () noexcept {
    return this->data.length();
}

void Database::getEmployeesByDepartment (List <Employee>& unit, const std::string& department) const noexcept {
    for (unsigned int i = 0; i < this->data.length(); ++i) {
        const Employee& u = this->data[i];
        if (u.getDepartment() == department) unit.append(u);
    }
}
    
void Database::getEmployeesWithHigherEducation (List <Employee>& unit) const noexcept {
    for (unsigned int i = 0; i < this->data.length(); ++i) {
        const Employee& u = this->data[i];
        if (u.getEducation() == Education::Higher) unit.append(u);
    }
}
    
unsigned short Database::countOldEmployees (void) const noexcept {
    std::time_t now = std::time(nullptr);
    std::tm* local = std::localtime(&now);
    unsigned short current_year = local->tm_year + 1900;

    double avg = 0.0;
    for (unsigned int i = 0; i < this->data.length(); ++i) {
        avg += current_year - this->data[i].getBirthDate().getYear();
    }
    avg /= this->data.length();

    unsigned short count = 0;
    for (unsigned int i = 0; i < this->data.length(); ++i) {
        if (current_year - this->data[i].getBirthDate().getYear() > avg) ++count;
    }
    
    return count;
}