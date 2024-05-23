#ifndef ICONTAINER_HPP
#define ICONTAINER_HPP

class IContainer {
public:
    virtual ~IContainer() = default;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
};

#endif // ICONTAINER_HPP