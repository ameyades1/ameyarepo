#include <memory>
#include <iostream>
#include <cstring>
#include <algorithm>

uint16_t *custom_allocator(size_t n);

int main(int argc, char* argv[]) {

    /* Raw pointer */
    std::cout << "----- Raw Pointer -----\n";
    uint64_t* p_raw_int = new uint64_t(10);
    std::cout << "p_raw_int = " << p_raw_int << " *p_raw_int = " << *p_raw_int << "\n";   
    std::cout <<"\n";
    delete p_raw_int;

    /* Unique pointer */
    std::cout << "----- Unique Pointer -----\n";
    std::unique_ptr<uint64_t> p_uniq_ptr_int = std::make_unique<uint64_t>(10);
    std::cout << "p_uniq_ptr_int = " << p_uniq_ptr_int.get() << " *p_uniq_ptr_int = " << *p_uniq_ptr_int << "\n";   
    
    /* Move it with move semantics. unique_ptr cannot be copied ! */
    //auto q_uniq_ptr_int = p_uniq_ptr_int;
    auto q_uniq_ptr_int = std::move(p_uniq_ptr_int);
    
    std::cout << "q_uniq_ptr_int = " << q_uniq_ptr_int.get() << " *q_uniq_ptr_int = " << *q_uniq_ptr_int << "\n"; 
    std::cout << "p_uniq_ptr_int = " << p_uniq_ptr_int.get() << "\n";
    std::cout <<"\n";

    /* Shared pointer */
    std::cout << "----- Shared Pointer -----\n";
    std::shared_ptr<uint64_t> p_shared_ptr_int = std::make_shared<uint64_t>(10);
    std::cout << "p_shared_ptr_int = " << p_shared_ptr_int.get() << " *p_shared_ptr_int = " << *p_shared_ptr_int << " ref_count = " << p_shared_ptr_int.use_count() << "\n";   
    
    {
        auto q_shared_ptr_int = p_shared_ptr_int;
        std::cout << "q_shared_ptr_int = " << q_shared_ptr_int.get() << " *q_shared_ptr_int = " << *q_shared_ptr_int << " ref_count = " << q_shared_ptr_int.use_count() << "\n"; 
        std::cout << "p_shared_ptr_int = " << p_shared_ptr_int.get() << " *p_shared_ptr_int = " << *p_shared_ptr_int << " ref_count = " << p_shared_ptr_int.use_count() << "\n";
    }
    std::cout << "p_shared_ptr_int = " << p_shared_ptr_int.get() << " *p_shared_ptr_int = " << *p_shared_ptr_int << " ref_count = " << p_shared_ptr_int.use_count() << "\n";   
    std::cout <<"\n";

    /* Shared pointer to an array */
    std::cout << "----- Shared pointer to an array -----\n";
    std::unique_ptr<uint16_t[]> p_uniq_ptr_arr_int(new uint16_t[10]); // array_deleter());
    std::fill_n(&p_uniq_ptr_arr_int[0], 10, 25);
    std::cout << "p_uniq_ptr_arr_int = " << p_uniq_ptr_arr_int.get() << " *p_uniq_ptr_arr_int = " << p_uniq_ptr_arr_int[5] << "\n";
    std::cout <<"\n";

    /* Custom deleter */
    struct array_deleter {
        void operator()(uint16_t *p) {
            std::cout << "-- Using custom deleter --\n";
            delete[] p;
        };
    };

    struct custom_deleter_free {
        void operator()(uint16_t *p)
        {
            std::cout << "-- Using custom deleter free --\n";
            free(p);
        };
    };

    {
        std::cout << "----- Custom deleter -----\n";
        std::shared_ptr<uint16_t[]> p_shared_ptr_int_cdel(new uint16_t[10], array_deleter());
        std::generate_n(&p_shared_ptr_int_cdel[0], 10, [](){static uint16_t i; return i++;} );
        std::cout << "p_shared_ptr_int_cdel = " << p_shared_ptr_int_cdel.get() << " *p_shared_ptr_int_cdel = " << p_shared_ptr_int_cdel[9] << "\n";
        std::cout <<"\n";
    }
    std::cout <<"\n";

    {
        std::cout << "----- Custom allocator -----\n";
        std::shared_ptr<uint16_t[]> p_shared_ptr_int_calloc((uint16_t*)custom_allocator(10));
    
        std::generate_n(&p_shared_ptr_int_calloc[0], 10, [](){static uint16_t i; return i++;} );
        std::cout << "p_shared_ptr_int_calloc = " << p_shared_ptr_int_calloc.get() << " *p_shared_ptr_int_calloc = " << p_shared_ptr_int_calloc[9] << "\n";
        std::cout <<"\n";
    }

    /* Custom allocator and deleter */
    std::cout << "----- Custom allocator and deleter -----\n";
    std::shared_ptr<uint16_t[]> p_shared_ptr_int_calloc_dalloc((uint16_t *)custom_allocator(10), custom_deleter_free());

    std::generate_n(&p_shared_ptr_int_calloc_dalloc[0], 10, []() {static uint16_t i; return i++; });
    std::cout << "p_shared_ptr_int_calloc_dalloc = " << p_shared_ptr_int_calloc_dalloc.get() << " *p_shared_ptr_int_calloc_dalloc = " << p_shared_ptr_int_calloc_dalloc[9] << "\n";
    std::cout << "\n";

    return 0;
}

/* Custom allocator */
uint16_t *custom_allocator(size_t n)
{
    std::cout << "-- Using custom allocator --\n";
    return (uint16_t *)calloc(n, sizeof(uint16_t));
}

class MyString
{
private:
        char* m_ptr;

public:
    MyString() : m_ptr(NULL) {};

    MyString (char* ptr) {
        size_t len = strlen((const char*)ptr);
        m_ptr = new char [len + 1];
        strcpy(m_ptr, ptr);            
    };

    ~MyString() {
        if(m_ptr) {
            delete[] m_ptr;
            }
    };
};
