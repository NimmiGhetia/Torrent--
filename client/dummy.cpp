#include <iostream>
#include <thread>
#include <string>

using namespace std ;

void thread_function(string s)
{
    cout << "thread function ";
    cout << "message is = " << s << endl;
}

int main()
{
    string s = "Kathy Perry";
    thread t(&thread_function, s);
    cout << "main thread message = " << s << endl;
    t.join();
    return 0;
}