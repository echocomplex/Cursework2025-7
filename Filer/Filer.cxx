#include "Filer.hxx"

Filer::Filer (const std::string& path, const bool createNew) {
    if (createNew) {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) {
            this->file.open(path, std::ios::out);
            this->file.close();
            this->file.open(path, std::ios::in);
            if (!this->file.is_open()) throw std::runtime_error("Failed to create the file.");
        }
    }
    else {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) throw std::runtime_error("File cannot be opened or does not exists");
    }
    this->path = path;
}

Filer::~Filer (void) noexcept {
    if (this->file.is_open()) this->file.close();
}

void Filer::open (const std::string& path, const bool createNew) {
    if (createNew) {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) {
            this->file.open(path, std::ios::out);
            this->file.close();
            this->file.open(path, std::ios::in);
            if (!this->file.is_open()) throw std::runtime_error("Failed to create the file.");
        }
    }
    else {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) throw std::runtime_error("File cannot be opened or does not exists");
    }
    this->path = path;
}

void Filer::read (std::string& str) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    
    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::in);

    this->file.seekg(0, std::ios::beg);
    std::string temp;

    this->file.seekp(0, std::ios::beg);
    while (std::getline(this->file, temp)) str += temp + '\n';
    
    this->mutex.unlock();
}

void Filer::readToList (List <Employee>& unit) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    
    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::in);

    this->file.seekg(0, std::ios::beg);
    std::string temp;
    Employee node;
    while (std::getline(this->file, temp)) {
        node = Employee();
        this->stringToEmployee(node, temp);
        unit.append(node);
    }

    this->mutex.unlock();
}

void Filer::writeBack (std::string& string) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    else if (string.empty()) return;

    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::app);

    this->file << string << '\n';
    this->file.flush();
    this->mutex.unlock();
}

void Filer::writeBackFromEmployee (const Employee& unit) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");

    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::app);

    this->file << 
        unit.getFullName() << "$$" <<
        unit.getBirthDate().getDay() << "$$" <<
        unit.getBirthDate().getMonth() << "$$" <<
        unit.getBirthDate().getYear() << "$$" <<
        unit.getEmployementDate().getDay() << "$$" <<
        unit.getEmployementDate().getMonth() << "$$" <<
        unit.getEmployementDate().getYear() << "$$" <<
        static_cast<unsigned short>(unit.getEducation()) << "$$" <<
        unit.getDepartment() << "$$" <<
        unit.getPost() << "$$" <<
        unit.getPhone() << '\n'
    ;
    this->file.flush();
    
    this->mutex.unlock();
}

void Filer::rewrite (std::string& string) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    else if (string.empty()) return;

    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::trunc);

    this->file << string << '\n';
    this->file.flush();

    this->mutex.unlock();
}

void Filer::rewriteFromList (const List <Employee>& unit) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    else if (unit.length() == 0) return;

    this->mutex.lock();

    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::trunc);

    this->file.seekg(0, std::ios::beg);

    for (unsigned int i = 0; i < unit.length(); ++i) {
        this->file << 
            unit[i].getFullName() << "$$" <<
            unit[i].getBirthDate().getDay() << "$$" <<
            unit[i].getBirthDate().getMonth() << "$$" <<
            unit[i].getBirthDate().getYear() << "$$" <<
            unit[i].getEmployementDate().getDay() << "$$" <<
            unit[i].getEmployementDate().getMonth() << "$$" <<
            unit[i].getEmployementDate().getYear() << "$$" <<
            static_cast<unsigned short>(unit[i].getEducation()) << "$$" <<
            unit[i].getDepartment() << "$$" <<
            unit[i].getPost() << "$$" <<
            unit[i].getPhone() << '\n'
        ;
    }
    this->file.flush();

    this->mutex.unlock();
}

void Filer::stringToEmployee (Employee& unit, const std::string& str) {
    if (str.empty()) return;

    std::string arr[11];
    unsigned short count = 0;
    for (size_t i = 0; i < (str.size() - 1) && count < 11; ++i) {
        if (str[i] == '$' && str[i + 1] == '$') {
            ++count, ++i;
        } 
        else arr[count].push_back(str[i]);
    }
    if (count < 11) arr[count].push_back(str[str.size() - 1]);

    unit.setFullName(arr[0]);
    try {
        unit.setBirthDate(std::stoul(arr[1]), std::stoul(arr[2]), std::stoul(arr[3]));
    } 
    catch (std::exception) {
        unit.setBirthDate(1, 1, 1); 
    }
    try {
        unit.setEmployementDate(std::stoul(arr[4]), std::stoul(arr[5]), std::stoul(arr[6]));
    } 
    catch (std::exception) {
        unit.setEmployementDate(1, 1, 1); 
    }
    try {
        unit.setEducation(static_cast<Education>(std::stoul(arr[7])));
    } 
    catch (std::exception) {
        unit.setEducation(Education::Secondary); 
    }
    unit.setDepartment(arr[8]);
    unit.setPost(arr[9]);
    unit.setPhone(arr[10]);
}
