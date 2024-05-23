#include "Shelf.hpp"
#include <iostream>

Shelf::Shelf() : pallets{} {}

bool Shelf::addPallet(Pallet* pallet) {
    for (auto& slot : pallets) {
        if (slot == nullptr) {
            slot = pallet;
            return true;
        }
    }
    return false;
}

bool Shelf::swapPallet(int slot1, int slot2) {
    if (slot1 < 0 || slot1 >= pallets.size() || slot2 < 0 || slot2 >= pallets.size()) {
        return false;
    }
    std::swap(pallets[slot1], pallets[slot2]);
    return true;
}

std::array<Pallet*, 4>& Shelf::getPallets() {
    return pallets;
}

const std::array<Pallet*, 4>& Shelf::getPallets() const {
    return pallets;
}

bool Shelf::isEmpty() const {
    for (const auto& pallet : pallets) {
        if (pallet != nullptr && !pallet->isEmpty()) {
            return false;
        }
    }
    return true;
}

bool Shelf::isFull() const {
    for (const auto& pallet : pallets) {
        if (pallet == nullptr || !pallet->isFull()) {
            return false;
        }
    }
    return true;
}

int Shelf::getTotalItemCount(const std::string& itemName) const {
    int totalItemCount = 0;
    for (const auto& pallet : pallets) {
        if (pallet != nullptr && pallet->getItemName() == itemName) {
            totalItemCount += pallet->getItemCount();
        }
    }
    return totalItemCount;
}

bool Shelf::takeItems(const std::string& itemName, int itemCount) {
    for (auto& pallet : pallets) {
        if (pallet != nullptr && pallet->getItemName() == itemName) {
            while (itemCount > 0 && pallet->takeOne()) {
                --itemCount;
            }
            if (itemCount == 0) {
                return true;
            }
        }
    }
    return itemCount == 0;
}

void Shelf::printPallets() const {
    for (const auto& pallet : pallets) {
        if (pallet != nullptr) {
            std::cout << "Item: " << pallet->getItemName() << ", Count: " << pallet->getItemCount() << ", Capacity: " << pallet->getItemCapacity() << std::endl;
        }
    }
}