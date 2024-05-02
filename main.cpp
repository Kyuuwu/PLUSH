#include <iostream>

#include "DiceGame.h"
#include "PLUSH_core_Exceptions.h"

int main(int, char**) {
    std::cout << "Hello, world!\n";
    
    try{
        DiceGame dg;
        dg.run();
    } catch (PLUSH::Exception e){
        PLUSH::elaborateException(e);
    }

    return 0;

}
