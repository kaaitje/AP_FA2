#include "Pallet.hpp"

Pallet::Pallet(const std::string& itemName, int capacity, int itemCount)
    : itemName(itemName), itemCapacity(capacity), itemCount(itemCount) {}

Pallet::Pallet() : itemName(""), itemCapacity(0), itemCount(0) {}

std::string Pallet::getItemName() const {
    return itemName;
}

int Pallet::getItemCount() const {
    return itemCount;
}

int Pallet::getRemainingSpace() const {
    return itemCapacity - itemCount;
}

bool Pallet::relocateEmptyPallet(const std::string& newItemName, int newItemCapacity) {
    if (itemCount == 0) {
        itemName = newItemName;
        itemCapacity = newItemCapacity;
        return true;
    }
    return false;
}

bool Pallet::takeOne() {
    if (itemCount > 0) {
        --itemCount;
        return true;
    }
    return false;
}

bool Pallet::putOne() {
    if (itemCount < itemCapacity) {
        ++itemCount;
        return true;
    }
    return false;
}

bool Pallet::isEmpty() const {
    return itemCount == 0;
}

bool Pallet::isFull() const {
    return itemCount >= itemCapacity;
}

int Pallet::getItemCapacity() const {
    return itemCapacity;
}

