#include <iostream>
#include <thread>
#include <mutex>

#include <sstream>

namespace std::numbers  {
        inline constexpr double tau { pi * 2.0 };
}


using namespace std;

mutex cout_mutex;

void test_tau(void)   {

        ostringstream oss;

        oss << "Tau: " << numbers::tau << endl;
        
        lock_guard<mutex> lock(cout_mutex);
        cout << oss.str();
}

void test_pi(void)    {

        ostringstream oss2;

        oss2 << "Pi: " << numbers::pi <<  endl;
        
        lock_guard<mutex> lock(cout_mutex);
        cout << oss2.str();
}


int main(void)  {

        thread thread_test_pi(test_pi);
        thread thread_test_tau(test_tau);

        thread_test_pi.join();
        thread_test_tau.join();

        return 0;
}
