#include <thread>
#include <chrono>

volatile static bool stopped = false;

bool check_interrupted() { return stopped; }

void interrupt() { stopped = true; }

void thread_func()
{
    for(int i = 0; i < 100; ++i)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (check_interrupted()) return;
    }
}

int main()
{
    std::thread t(thread_func);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    interrupt();
    t.join();
    return 0;
}
