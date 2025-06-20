#include <iostream>
#include <thread>
#include <mutex>

#include <sstream>
#include <chrono>

namespace std::numbers  {
        inline constexpr double tau { pi * 2.0 };
}


using namespace std;

mutex cout_mutex;

void test_tau(void)   {

        ostringstream oss;

        oss << "Tau: " << numbers::tau << "\tThread ID: " << this_thread::get_id() << endl;

	this_thread::sleep_for(chrono::milliseconds(100));

        lock_guard<mutex> lock(cout_mutex);
        cout << oss.str();
}

void test_pi(void)    {

        ostringstream oss2;

        oss2 << "Pi: " << numbers::pi << "\tThread ID: "<< this_thread::get_id() << endl;
        
	this_thread::sleep_for(chrono::milliseconds(100));

        lock_guard<mutex> lock(cout_mutex);
        cout << oss2.str();
}


int main(void)  {

	auto start = chrono::steady_clock::now();

	thread thread_test_pi(test_pi);
	thread thread_test_tau(test_tau);
	
	thread_test_pi.join();
	thread_test_tau.join();

	auto end = chrono::steady_clock::now();
	cout << "Total time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;

	return 0;
} 
