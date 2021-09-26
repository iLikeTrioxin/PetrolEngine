#include <Aliases.h>

// TODO add boundary checks in debug mode

// length of array is length of type passed to  template
template<typename T>
class BoolArray{
    T container;

    void setBool(uint8 index, bool value) {
        container |= (value ? 0b1 : 0b0) << index;
    }

    bool getBool(uint8 index){
        return container & (0b1 << index);
    }

    const bool operator[](uint8 index){
        return getBool(index);
    }
};