#include <iostream>
#include <string>
#include <unistd.h>

int global_int;
float global_float;

int main(void)
{
    static int bss_int;
    int stack_int {};
    int *heap_int = new int();

    
    static float bss_float;
    float stack_float {};
    float *heap_float = new float();

    while (true)
    {
        std::cout << "1) bss_int:     \t" << bss_int   << "\t"  << &bss_int    << std::endl;
        std::cout << "2) global_int:  \t" << global_int << "\t" << &global_int << std::endl;
        std::cout << "3) stack_int:   \t" << stack_int << "\t"  << &stack_int  << std::endl;
        std::cout << "4) heap_int:    \t" << *heap_int << "\t"  << heap_int    << std::endl;

        std::cout << std::endl;

        std::cout << "5) bss_float:   \t" << bss_float   << "\t"  << &bss_float    << std::endl;
        std::cout << "6) global_float:\t" << global_float << "\t" << &global_float << std::endl;
        std::cout << "7) stack_float: \t" << stack_float << "\t"  << &stack_float  << std::endl;
        std::cout << "8) heap_float:  \t" << *heap_float << "\t"  << heap_float    << std::endl;

        int choise {};
        float data {};
        std::cout << "choice: "; std::cin >> choise;
        std::cout << "data: ";   std::cin >> data;

        switch (choise)
        {
        case 1:
            bss_int += static_cast<int>(data);
            break;
        case 2:
            global_int += static_cast<int>(data);
            break;
        case 3:
            stack_int += static_cast<int>(data);
            break;
        case 4:
            *heap_int += static_cast<int>(data);
            break;
        case 5:
            bss_float += data;
            break;
        case 6:
            global_float += data;
            break;
        case 7:
            stack_float += data;
            break;
        case 8:
            *heap_float += data;
            break;

        default:
            break;
        }

        system("clear");
    }

    delete heap_int;
    delete heap_float;

    return 0;
}