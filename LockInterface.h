#ifndef LOCKINTERFACE_H
#define LOCKINTERFACE_H

class LockInterface {
public:
    virtual void lock() = 0;
    virtual void unlock() = 0;
    virtual bool isLocked() const = 0;
    virtual ~LockInterface() = default;
};

#endif