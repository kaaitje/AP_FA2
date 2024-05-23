#ifndef PALLET_HPP
#define PALLET_HPP

#include <string>
#include "IContainer.hpp"

class Pallet : public IContainer {
public:
    Pallet(const std::string& itemName, int capacity, int itemCount);
    Pallet();

    std::string getItemName() const;
    int getItemCount() const;
    int getRemainingSpace() const;
    int getItemCapacity() const;
    

    bool relocateEmptyPallet(const std::string& itemName, int itemCapacity);
    bool takeOne();
    bool putOne();

    bool isEmpty() const override;
    bool isFull() const override;

    
private:
    std::string itemName;
    int itemCount;
    int itemCapacity;
    
};

#endif // PALLET_HPP