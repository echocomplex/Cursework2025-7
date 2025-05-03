#include "Interface.hxx"

void Interface::clearInputBuffer (void) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void Interface::getEmployee (Employee& unit) {
    std::string temp;
    unsigned short temp_number1 = 1, temp_number2 = 1, temp_number3 = 1;

    std::cout << "Enter the Employee Name: ";
    std::getline(std::cin, temp);
    unit.setFullName(temp);
    std::cout << "Enter the Birth Day: ";
    std::cin >> temp_number1;
    this->clearInputBuffer();
    std::cout << "Enter the Birth Month: ";
    std::cin >> temp_number2;
    this->clearInputBuffer();
    std::cout << "Enter the Birth Year: ";
    std::cin >> temp_number3;
    this->clearInputBuffer();
    unit.setBirthDate(temp_number1, temp_number2, temp_number3);
    temp_number1 = 1, temp_number2 = 1, temp_number3 = 1;
    std::cout << "Enter the Employement Day: ";
    std::cin >> temp_number1;
    this->clearInputBuffer();
    std::cout << "Enter the Employement Month: ";
    std::cin >> temp_number2;
    this->clearInputBuffer();
    std::cout << "Enter the Employement Year: ";
    std::cin >> temp_number3;
    this->clearInputBuffer();
    unit.setEmployementDate(temp_number1, temp_number2, temp_number3);
    while (true) {
        std::cout << "Enter Employer Education 1-4\n(1 - Secondary, 2 - Secondary Special, 3 - Secondary Technical, 4 - Higher): ";  
        if (!(std::cin >> temp_number1)) {
            std::cin.clear();
            this->clearInputBuffer();
            std::cerr << "Error: Please enter a number\n\n";
            continue;
        }
        if (temp_number1 >= 1 && temp_number1 <= 4) {
            unit.setEducation(static_cast<Education>(temp_number1 - 1));
            break;
        }
        std::cerr << "Error: Number must be between 1 and " << this->unit.size() << "\n\n";
    }
    this->clearInputBuffer();
    std::cout << "Enter the Department: ";
    std::getline(std::cin, temp);
    unit.setDepartment(temp);
    std::cout << "Enter the Post: ";
    std::getline(std::cin, temp);
    unit.setPost(temp);
    std::cout << "Enter the Phone: ";
    std::getline(std::cin, temp);
    unit.setPhone(temp);
}

int Interface::removeEmployee (void) {
    int number;
    while (true) {
        std::cout << "Enter Employee number to delete (1-" << this->unit.size() << "): ";
        
        if (!(std::cin >> number)) {
            std::cin.clear();
            this->clearInputBuffer();
            std::cerr << "Error: Please enter a number\n\n";
            continue;
        }

        if (number > 0 && number <= this->unit.size()) {
            return number - 1;
        }
        
        std::cerr << "Error: Number must be between 1 and " << this->unit.size() << "\n\n";
    }
}

void Interface::displayMenu (void) {
    std::cout << "\n\n=== Employee Database Menu ===" << std::endl;
    std::cout << "1. Display all records" << std::endl;
    std::cout << "2. Add new Employee" << std::endl;
    std::cout << "3. Remove Employee" << std::endl;
    std::cout << "4. Display Employees By Department" << std::endl;
    std::cout << "5. Display Employees With Higher Education" << std::endl;
    std::cout << "6. Count Old Employees" << std::endl;
    std::cout << "7. Exit program" << std::endl;
    std::cout << "Enter your choice (1-7): ";
}

void Interface::pool (void) {
    short choice = 0;
    std::string temp;
    List <Employee> collected;
    Employee new_Employee;
    while (true) {
        this->displayMenu();

        while (!(std::cin >> choice) || choice < 1 || choice > 7) {
            std::cout << "Invalid input. Please enter 1-7: ";
            this->clearInputBuffer();
        }

        this->clearInputBuffer();

        switch (choice) {
            case 1:
                std::cout << "\n[Displaying all records]\n";
                std::cout << this->unit << std::endl;
                break;
            case 2:
                std::cout << "\n[Adding new Employee]\n";
                this->getEmployee(new_Employee);
                this->unit.append(new_Employee);
                break;
            case 3:
                std::cout << "\n[Removing Employee]\n";
                this->unit.remove(this->removeEmployee());
                break;
            case 4: 
                std::cout << "Enter Department: ";
                std::getline(std::cin, temp);
                std::cout << "\n[Displaying Employees By Department]\n";
                this->unit.getEmployeesByDepartment(collected, temp);
                for (int i = 0; i < collected.length(); ++i) std::cout << collected[i] << std::endl;
                collected.clear();
                break;
            case 5:
                std::cout << "\n[Displaying Employees With Higher Education]\n";
                this->unit.getEmployeesWithHigherEducation(collected);
                for (int i = 0; i < collected.length(); ++i) std::cout << collected[i] << std::endl;
                collected.clear();
                break;
            case 6:
                std::cout << "There's " << this->unit.countOldEmployees() << " Employees > avg" << std::endl;
                break;
            case 7:
                std::cout << "\nExiting program...\n";
                return;
        }

        std::cout << "\nOperation completed. Press Enter to continue...";
        this->clearInputBuffer();
    }
}