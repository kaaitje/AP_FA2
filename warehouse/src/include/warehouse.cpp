#include "Warehouse.hpp"
#include <algorithm>
#include <iostream>

Warehouse::Warehouse() {}

void Warehouse::addEmployee(const Employee& employee) {
    employees.push_back(employee);
}

void Warehouse::addShelf(const Shelf& shelf) {
    shelves.push_back(shelf);
}

const std::vector<Shelf>& Warehouse::getShelves() const {
    return shelves;
}

bool Warehouse::rearrangeShelf(Shelf& shelf) {
    // Find an available employee with a forklift certificate
    auto employeeIt = std::find_if(employees.begin(), employees.end(), [](const Employee& e) {
        return !e.getBusy() && e.getForkliftCertificate();
    });

    if (employeeIt != employees.end()) {
        // Set the found employee as busy
        employeeIt->setBusy(true);

        // Sort pallets in ascending order based on item count
        auto& pallets = shelf.getPallets();
        std::sort(pallets.begin(), pallets.end(), [](const Pallet* a, const Pallet* b) {
            if (!a && !b) return false;
            if (!a) return true;
            if (!b) return false;
            return a->getItemCount() < b->getItemCount();
        });

        // Set the employee as not busy after rearranging the shelf
        employeeIt->setBusy(false);
        return true;
    }

    // No available employee found with a forklift certificate
    return false;
}

// bool Warehouse::rearrangeShelf(Shelf& shelf) {
//     // Find an available employee with a forklift certificate
//     auto employeeIt = std::find_if(employees.begin(), employees.end(), [](const Employee& e) {
//         return !e.getBusy() && e.getForkliftCertificate();
//     });

//     if (employeeIt != employees.end()) {
//         // Set the found employee as busy
//         employeeIt->setBusy(true);

//         // Store the initial state of the shelf
//         std::array<Pallet*, 4> initialPallets = shelf.getPallets();

//         // Rearrange the shelf based on initial pallet positions
//         bool rearranged = false;
//         for (size_t i = 0; i < initialPallets.size(); ++i) {
//             if (shelf.getPallets()[i] != initialPallets[i]) {
//                 // Find the index of the pallet in the initial state
//                 auto it = std::find(initialPallets.begin() + i, initialPallets.end(), shelf.getPallets()[i]);
//                 if (it != initialPallets.end()) {
//                     // Calculate the index difference
//                     size_t indexDiff = std::distance(initialPallets.begin() + i, it);
//                     // Swap pallets
//                     shelf.swapPallet(i, i + indexDiff);
//                     rearranged = true;
//                 }
//             }
//         }

//         // Set the employee as not busy after rearranging the shelf
//         employeeIt->setBusy(false);
        
//         return rearranged;
//     }
//     return false;
// }

bool Warehouse::pickItems(const std::string& itemName, int itemCount) {
    int itemsToPick = itemCount;

    for (Shelf& shelf : shelves) {
        if (shelf.takeItems(itemName, itemsToPick)) {
            return true;
        }
    }
    return false;
}

void Warehouse::editEmployee(const std::string& name, bool busy, bool forkliftCertificate) {
    for (Employee& employee : employees) {
        if (employee.getName() == name) {
            employee.setBusy(busy);
            employee.setForkliftCertificate(forkliftCertificate);
            return; // Exit the loop after modifying the employee
        }
    }
    // If the employee with the given name is not found, you can throw an error or handle it as needed
}

void Warehouse::printEmployeeStatus() const {
    for (const auto& employee : employees) {
        std::cout << "Employee: " << employee.getName() << ", Busy: " << employee.getBusy() << ", Certified: " << employee.getForkliftCertificate() << std::endl;
    }
}