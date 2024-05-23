#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <string>

class Employee {
public:
    Employee(const std::string& name, bool forkliftCertificate);

    std::string getName() const;
    
    bool getBusy() const;
    bool getForkliftCertificate() const;
    
    void setBusy(bool busy);
    void setForkliftCertificate(bool forkliftCertificate);

private:
    const std::string name;
    bool busy;
    bool forkliftCertificate;
};

#endif // EMPLOYEE_HPP