#ifndef WAREHOUSE_HPP
#define WAREHOUSE_HPP

#include <vector>
#include <string>
#include "Employee.hpp"
#include "Shelf.hpp"

class Warehouse {
public:
    Warehouse();

    void addEmployee(const Employee& employee);
    void editEmployee(const std::string& name, bool busy, bool forkliftCertificate);
    void addShelf(const Shelf& shelf);
    bool rearrangeShelf(Shelf& shelf);
    bool pickItems(const std::string& itemName, int itemCount);
    const std::vector<Shelf>& getShelves() const;
    void printEmployeeStatus() const;

    
private:
    std::vector<Employee> employees;
    std::vector<Shelf> shelves;
};

#endif // WAREHOUSE_HPP