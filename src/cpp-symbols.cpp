#include <iostream>
#include <unistd.h>
#include <cxxopts.hpp> // cxxopts::

using namespace std;

static int symbols_times{1};

void foo(long int max_times)
{
    long int x = {0};
    int err = {0};
    for (int i = 0; i < max_times; i++)
    {
        x = x + 1;
    }
}

void bar(long int max_times)
{
    long int x = {0};
    for (int i = 0; i < max_times; i++)
    {
        x = x + i;
    }
    foo(max_times);
}

void parser_args(int argc, char *argv[])
{
    cxxopts::Options options("cpp-sym-table", "cpp debug program");
    options.add_options()("t,times", "循环次数", cxxopts::value<int>()->default_value("1"))("h,help", "打印帮忙文档");
    cxxopts::ParseResult result = options.parse(argc, argv);
    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }
    if (result.count("times"))
    {
        symbols_times = result["times"].as<int>();
    }
}

int main(int argc, char *args[])
{
    parser_args(argc, args);
    cout << "times = " << symbols_times << endl;
    for (int i = {0}; i < symbols_times; i++)
    {
        bar(200000000);
        foo(200000000);
        cout << "current trip = " << i << endl;
    }
    cout << "exit" << endl;
    return 0;
}