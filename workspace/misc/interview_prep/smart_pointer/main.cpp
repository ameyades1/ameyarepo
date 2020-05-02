#include <memory>
#include <iostream>
#include <thread>
#include <chrono>

int main(int argc, char* argv[]) {

    std::shared_ptr<uint32_t> s_ptr1 = std::make_shared<uint32_t>(10);
    std::cout << "s_ptr1 = " << *s_ptr1 << " Use count = " << s_ptr1.use_count() << "\n";

    std::shared_ptr<uint32_t> s_ptr2 = s_ptr1;
    std::cout << "s_ptr2 = " << *s_ptr2 << " Use count = " << s_ptr1.use_count() << "\n";

    std::cout << "s_ptr1 = " << *s_ptr1 << " Use count = " << s_ptr1.use_count() << "\n";
    return 0;
}


void thread_fn(std::shared_ptr<uint32_t> p) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
}


