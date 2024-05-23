#ifndef SHELF_HPP
#define SHELF_HPP

#include <array>
#include "Pallet.hpp"


class Shelf : public IContainer {
public:
    Shelf();
    bool addPallet(Pallet* pallet);
    bool swapPallet(int slot1, int slot2);
    
    std::array<Pallet*, 4>& getPallets();
    const std::array<Pallet*, 4>& getPallets() const;

    bool isEmpty() const override;
    bool isFull() const override;
    int getTotalItemCount(const std::string& itemName) const;
    bool takeItems(const std::string& itemName, int itemCount);

    void printPallets() const;

private:
    std::array<Pallet*, 4> pallets;
};

#endif // SHELF_HPP
