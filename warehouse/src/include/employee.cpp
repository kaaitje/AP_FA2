#include "Employee.hpp"

Employee::Employee(const std::string& name, bool forkliftCertificate)
    : name(name), busy(false), forkliftCertificate(forkliftCertificate) {}

std::string Employee::getName() const {
    return name;
}

bool Employee::getBusy() const {
    return busy;
}

bool Employee::getForkliftCertificate() const {
    return forkliftCertificate;
}

void Employee::setBusy(bool busy) {
    this->busy = busy;
}

void Employee::setForkliftCertificate(bool forkliftCertificate) {
    this->forkliftCertificate = forkliftCertificate;
}