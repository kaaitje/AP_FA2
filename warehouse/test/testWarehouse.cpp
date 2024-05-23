#include "include/catch.hpp"

#include "../src/include/warehouse.hpp"
#include <iostream>

///////////////////////////////////////////////////////////////
//                                                           //
//                    Warehouse unittests                    //
//                                                           //
///////////////////////////////////////////////////////////////
//                                                           //
// This file contains all testcases for the Warehouse class. //
// Currently it only contains tests for the rearranging of   //
// shelves. All other Warehouse functions will also need to  //
// be tested. You will have to do this yourself.             //
//                                                           //
// For information on how to write testcases with catch2,    //
// see https://github.com/catchorg/Catch2.                   //
//                                                           //
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
//                Functions used in testcases                //
///////////////////////////////////////////////////////////////

/// \brief 
/// Creates a mock Warehouse.
/// \return Warehouse with shelf of books.
/// \details
/// Creates a Warehouse with 3 unsorted shelves with a total of 100 Books, 60 Boxes, and 60 Toy Bears.
/// \n Adds forklift certified employee Bob.
/// \n This function can be used in testcases to avoid the repeated construction of Warehouse objects.

Warehouse createMockWarehouse() {
    Warehouse warehouse;
    Shelf shelf1;

    shelf1.addPallet(new Pallet("Books", 100, 40));
    shelf1.addPallet(new Pallet("Boxes", 100, 10));
    shelf1.addPallet(new Pallet("Books", 100, 20));
    shelf1.addPallet(new Pallet("Books", 100, 20));

    Shelf shelf2;
    shelf2.addPallet(new Pallet("Books", 100, 15));
    shelf2.addPallet(new Pallet("Boxes", 100, 20));
    shelf2.addPallet(new Pallet("Books", 100, 5));
    shelf2.addPallet(new Pallet("Boxes", 100, 30));
    
    Shelf shelf3;
    shelf3.addPallet(new Pallet("Toy Bears", 100, 20));
    shelf3.addPallet(new Pallet("Toy Bears", 100, 10));
    shelf3.addPallet(new Pallet());
    shelf3.addPallet(new Pallet("Toy Bears", 100, 30));
    
    warehouse.addShelf(shelf1);
    warehouse.addShelf(shelf2);
    warehouse.addShelf(shelf3);

    warehouse.addEmployee(Employee("Bob", true));

    return warehouse;
}


///////////////////////////////////////////////////////////////
//           Warehouse::rearrangeShelf test cases            //
///////////////////////////////////////////////////////////////

TEST_CASE("Rearrange empty shelf", "Warehouse::rearrangeShelf"){
    // Construct empty warehouse and add empty shelf and forklift certified Employee.
    Warehouse warehouse;
    warehouse.addShelf(Shelf());
    warehouse.addEmployee(Employee("Bob", true));

    // Check if shelf is already arranged.
    // Empty shelf should already be arranged.
    const auto& shelves = warehouse.getShelves();
    REQUIRE(shelves[0].getPallets()[0]->getItemCount() == 0);
    REQUIRE(shelves[0].getPallets()[1]->getItemCount() == 0);
    REQUIRE(shelves[0].getPallets()[2]->getItemCount() == 0);
    REQUIRE(shelves[0].getPallets()[3]->getItemCount() == 0);

    Shelf shelfCopy = shelves[0];
    bool successful = warehouse.rearrangeShelf(shelfCopy);
    // Should be successful
    REQUIRE(successful);

    // Check if shelf is now correctly arranged.
    // Empty shelf should still be arranged.
    const auto& shelvesAfterRearranging = warehouse.getShelves();
    REQUIRE(shelvesAfterRearranging[0].getPallets()[0]->getItemCount() == 0);
    REQUIRE(shelvesAfterRearranging[0].getPallets()[1]->getItemCount() == 0);
    REQUIRE(shelvesAfterRearranging[0].getPallets()[2]->getItemCount() == 0);
    REQUIRE(shelvesAfterRearranging[0].getPallets()[3]->getItemCount() == 0);

}

TEST_CASE("Rearrange full shelf", "Warehouse::rearrangeShelf") {
    // Construct warehouse with unsorted shelf of books.
    Warehouse warehouse;
    Shelf shelf1;
    shelf1.addPallet(new Pallet("Books", 100, 20));
    shelf1.addPallet(new Pallet("Books", 100, 40));
    shelf1.addPallet(new Pallet("Books", 100, 30));
    shelf1.addPallet(new Pallet("Books", 100, 10));
    warehouse.addShelf(shelf1);

    warehouse.addEmployee(Employee("Bob", true));
    warehouse.addShelf(shelf1);

    // Check if shelf is already arranged.
    // This shelf should not already be arranged.
    const auto& shelves = warehouse.getShelves();
    const auto& pallets = shelves[0].getPallets();
    REQUIRE(pallets[0]->getItemCount() == 20);
    REQUIRE(pallets[1]->getItemCount() == 40);
    REQUIRE(pallets[2]->getItemCount() == 30);
    REQUIRE(pallets[3]->getItemCount() == 10);

    // Rearrange the first and only shelf of the warehouse.
    Shelf& shelfRef = const_cast<Shelf&>(shelves[0]); // Remove constness from the reference
    bool successful = warehouse.rearrangeShelf(shelfRef);
    // Should be successful
    REQUIRE(successful);

    // Check if shelf is now correctly arranged.
    // Shelf should now be arranged.
    const auto& palletsAfterRearranging = shelves[0].getPallets(); // Ensure shelves is const
    REQUIRE(palletsAfterRearranging[0]->getItemCount() == 10);
    REQUIRE(palletsAfterRearranging[1]->getItemCount() == 20);
    REQUIRE(palletsAfterRearranging[2]->getItemCount() == 30);
    REQUIRE(palletsAfterRearranging[3]->getItemCount() == 40);
}

TEST_CASE("Rearrange half filled shelf", "Warehouse::rearrangeShelf") {
    // Construct empty warehouse and unsorted shelf of books.
    Warehouse warehouse;
    Shelf shelf1;
    shelf1.addPallet(new Pallet("Books", 100, 40));
    shelf1.addPallet(new Pallet("Books", 100, 20));
    shelf1.addPallet(new Pallet());
    shelf1.addPallet(new Pallet());
    warehouse.addEmployee(Employee("Bob", true));
    warehouse.addShelf(shelf1);

    // Check if shelf is already arranged.
    // This shelf should not already be arranged.
    const auto& shelves = warehouse.getShelves();
    const auto& palletsBeforeRearranging = shelves[0].getPallets();
    REQUIRE(palletsBeforeRearranging[0]->getItemCount() == 40);
    REQUIRE(palletsBeforeRearranging[1]->getItemCount() == 20);
    REQUIRE(palletsBeforeRearranging[2]->getItemCount() == 0); 
    REQUIRE(palletsBeforeRearranging[3]->getItemCount() == 0);

    // Rearrange the first and only shelf of the warehouse.
    Shelf& shelfRef = const_cast<Shelf&>(shelves[0]); 
    bool successful = warehouse.rearrangeShelf(shelfRef);
    
    // Should be successful
    REQUIRE(successful);

    // Check if shelf is now correctly arranged.
    // Shelf should now be arranged.
    const auto& shelvesAfterRearranging = warehouse.getShelves();
    const auto& palletsAfterRearranging = shelvesAfterRearranging[0].getPallets();
    REQUIRE(palletsAfterRearranging[0]->getItemCount() == 0);
    REQUIRE(palletsAfterRearranging[1]->getItemCount() == 0);
    REQUIRE(palletsAfterRearranging[2]->getItemCount() == 20);
    REQUIRE(palletsAfterRearranging[3]->getItemCount() == 40);
}

TEST_CASE("Rearrange shelf without qualified employee", "Warehouse::rearrangeShelf"){
    // Construct warehouse with unsorted shelf of books.
    Warehouse warehouse = Warehouse();
    Shelf shelf1;
    shelf1.addPallet(new Pallet("Books", 100, 20)); 
    shelf1.addPallet(new Pallet("Books", 100, 40)); 
    shelf1.addPallet(new Pallet("Books", 100, 30));
    shelf1.addPallet(new Pallet("Books", 100, 10));
    
    warehouse.addEmployee(Employee("Bert", false));
    warehouse.addShelf(shelf1);

    // Check if shelf is already arranged.
    // This shelf should not already be arranged.

    const auto& shelves = warehouse.getShelves();
    const auto& palletsBeforeRearranging = shelves[0].getPallets();
    REQUIRE(palletsBeforeRearranging[0]->getItemCount() == 20);
    REQUIRE(palletsBeforeRearranging[1]->getItemCount() == 40);
    REQUIRE(palletsBeforeRearranging[2]->getItemCount() == 30); 
    REQUIRE(palletsBeforeRearranging[3]->getItemCount() == 10);

    // Rearrange the first and only shelf of the warehouse.
    Shelf& shelfRef = const_cast<Shelf&>(shelves[0]); 
    bool successful = warehouse.rearrangeShelf(shelfRef);
    
    // Should fail
    REQUIRE(!successful);

    // Check if shelf is now correctly arranged.
    // Shelf should now still not be arranged.
    const auto& shelvesAfterRearranging = warehouse.getShelves();
    const auto& palletsAfterRearranging = shelvesAfterRearranging[0].getPallets();
    REQUIRE(palletsAfterRearranging[0]->getItemCount() == 20);
    REQUIRE(palletsAfterRearranging[1]->getItemCount() == 40);
    REQUIRE(palletsAfterRearranging[2]->getItemCount() == 30);
    REQUIRE(palletsAfterRearranging[3]->getItemCount() == 10);

}

TEST_CASE("Rearrange shelf with quallified, but busy, employee", "Warehouse::rearrangeShelf"){
    // Construct warehouse with unsorted shelf of books.
    Warehouse warehouse = Warehouse();
    Shelf shelf1;
    shelf1.addPallet(new Pallet("Books", 100, 20)); 
    shelf1.addPallet(new Pallet("Books", 100, 40)); 
    shelf1.addPallet(new Pallet("Books", 100, 30));
    shelf1.addPallet(new Pallet("Books", 100, 10));
    
    Employee bert = Employee("Bert", true);
    bert.setBusy(true);

    warehouse.addEmployee(bert);
    warehouse.addShelf(shelf1);

    // Check if shelf is already arranged.
    // This shelf should not already be arranged.
    const auto& shelves = warehouse.getShelves();
    const auto& palletsBeforeRearranging = shelves[0].getPallets();
    REQUIRE(palletsBeforeRearranging[0]->getItemCount() == 20);
    REQUIRE(palletsBeforeRearranging[1]->getItemCount() == 40);
    REQUIRE(palletsBeforeRearranging[2]->getItemCount() == 30);
    REQUIRE(palletsBeforeRearranging[3]->getItemCount() == 10);

    // Rearrange the first and only shelf of the warehouse.
    Shelf& shelfRef = const_cast<Shelf&>(shelves[0]); 
    bool successful = warehouse.rearrangeShelf(shelfRef);
    
    // Should fail
    REQUIRE(!successful);

    // Check if shelf is now correctly arranged.
    // Shelf should now still not be arranged.
    const auto& palletsAfterRearranging = shelves[0].getPallets();
    REQUIRE(palletsAfterRearranging[0]->getItemCount() == 20);
    REQUIRE(palletsAfterRearranging[1]->getItemCount() == 40);
    REQUIRE(palletsAfterRearranging[2]->getItemCount() == 30);
    REQUIRE(palletsAfterRearranging[3]->getItemCount() == 10);
}