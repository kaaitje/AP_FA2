#include <iostream>

#include "src/include/Warehouse.hpp"
#include "src/include/Employee.hpp"
#include "src/include/Shelf.hpp"
#include "src/include/Pallet.hpp"

int main() {
    // Create a warehouse
    Warehouse warehouse;

    // Create shelves and pallets
    Shelf shelf1;
    Pallet pallet1("Boxes", 100, 90);
    Pallet pallet2("Clothes", 100, 10);
    Pallet pallet3("Junk", 100, 50);
    Pallet pallet4("Forgotten items", 100, 5);

    Shelf shelf2;
    Pallet pallet5("Lost and found", 100, 100);
    Pallet pallet6("Junk", 100, 100);
    Pallet pallet7("Boxes", 100, 100);
    Pallet pallet8("Forgotten items", 100, 100);

    Shelf shelf3;
    Pallet pallet9("Gold", 100, 0);
    Pallet pallet10("Valuables", 100, 0);
    Pallet pallet11("Diamonds", 100, 0);
    Pallet pallet12("RareElements", 100, 0);

    // Add pallets to the shelf
    shelf1.addPallet(&pallet1);
    shelf1.addPallet(&pallet2);
    shelf1.addPallet(&pallet3);
    shelf1.addPallet(&pallet4);

    shelf2.addPallet(&pallet5);
    shelf2.addPallet(&pallet6);
    shelf2.addPallet(&pallet7);
    shelf2.addPallet(&pallet8);

    shelf3.addPallet(&pallet9);
    shelf3.addPallet(&pallet10);
    shelf3.addPallet(&pallet11);
    shelf3.addPallet(&pallet12);

    // Add shelf to the warehouse
    warehouse.addShelf(shelf1);
    warehouse.addShelf(shelf2);
    warehouse.addShelf(shelf3);


    // create employees
    Employee employee1("Bob", false); 
    Employee employee2("Ross", false);

    // Set employee status to busy and without forklift certificate
    employee1.setForkliftCertificate(false);
    employee2.setForkliftCertificate(false);
    employee1.setBusy(true);
    employee2.setBusy(true);

    // Add employees to the warehouse
    warehouse.addEmployee(employee1);
    warehouse.addEmployee(employee2);

    std::cout << "\n\nTests isFull and isEmpty and shows arrangement before sorting" << std::endl;
    // Display initial state of the shelf
    std::cout << "Initial state of shelf 1: should not be ful and not empty" << std::endl;
    std::cout << "Is full: " << (shelf1.isFull() ? "Yes" : "No") << std::endl;
    std::cout << "Is empty: " << (shelf1.isEmpty() ? "Yes" : "No") << std::endl;

    std::cout << "Initial state of shelf 2 should be full and not empty:" << std::endl;
    std::cout << "Is full: " << (shelf2.isFull() ? "Yes" : "No") << std::endl;
    std::cout << "Is empty: " << (shelf2.isEmpty() ? "Yes" : "No") << std::endl;

    std::cout << "Initial state of shelf 3, should not be full but empty:" << std::endl;
    std::cout << "Is full: " << (shelf3.isFull() ? "Yes" : "No") << std::endl;
    std::cout << "Is empty: " << (shelf3.isEmpty() ? "Yes" : "No") << std::endl;

    std::cout << "\nPallets on shelf 1 before sorting" << std::endl;
    shelf1.printPallets();


    // testcase 1
    warehouse.editEmployee("Bob", true, false);
    warehouse.editEmployee("Ross", true, false);
    std::cout << "\nCase1: Attempting to rearrange shelf busy and without forklift certificate" << std::endl;
    warehouse.printEmployeeStatus();
    if (warehouse.rearrangeShelf(shelf1)) {
        std::cout << "Success. Shelf rearranged." << std::endl;
    } else {
        std::cout << "Failed. No available workers with forklift certificate." << std::endl;
    }

    // testcase 2
    warehouse.editEmployee("Bob", false, false);
    warehouse.editEmployee("Ross", false, false);

    std::cout << "\nCase2: Attempting to rearrange shelf not busy but without forklift certificate" << std::endl;
    warehouse.printEmployeeStatus();

    if (warehouse.rearrangeShelf(shelf1)) {
        std::cout << "Success. Shelf rearranged." << std::endl;
    } else {
        std::cout << "Failed. No available workers with forklift certificate." << std::endl;
    }

    // testcase 3
    warehouse.editEmployee("Bob", true, true);
    warehouse.editEmployee("Ross", true, true);

    std::cout << "\nCase3: Attempting to rearrange shelf busy but with forklift certificate" << std::endl;
    warehouse.printEmployeeStatus();

    if (warehouse.rearrangeShelf(shelf1)) {
        std::cout << "Success. Shelf rearranged." << std::endl;
    } else {
        std::cout << "Failed. No available workers with forklift certificate." << std::endl;
    }


    // testcase 4
    warehouse.editEmployee("Bob", false, true);
    warehouse.editEmployee("Ross", false, true);

    std::cout << "\nCase4: Attempting to rearrange shelf, workers not busy and with forklift certificate" << std::endl;
    warehouse.printEmployeeStatus();

    if (warehouse.rearrangeShelf(shelf1)) {
        std::cout << "Success. Shelf rearranged." << std::endl;
    } else {
        std::cout << "Failed. No available workers with forklift certificate." << std::endl;
    }

    std::cout << "\nItems on shelf 1 after sorting" << std::endl;
    shelf1.printPallets();

    return 0;
}
