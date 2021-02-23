#include <iostream>
#include <string>

struct Base;

template <typename From, typename To>
class Conversion{
    public:
    class Big{
        char a[2];
    };
    class Small{};
    static From From_Gen();
    static Small convert(To);
    static Big convert(...);
    static const bool convert_ = sizeof(Small) == sizeof(convert(From_Gen()));
    static const bool same_ = 0;
};

template <typename From>
class Conversion<From, From>{
    public:
    static const bool convert_ = 1;
    static const bool same_ = 1;
};

#define SUPERSUBCLASS(Child,Parent) (Conversion<const Child*, const Parent*>::convert_ && !(Conversion<const Parent*, void*>::same_))
#define STRICKSUPERSUBCLASS(Child,Parent) (SUPERSUBCLASS(Child,Parent)&&(!(Conversion<const Child,const Parent>::same_)))

struct Base{};
struct Derived:Base{};

int main(int, char**) {
    std::cout << STRICKSUPERSUBCLASS(const Derived, Derived);
}
