#include <unistd.h>    // sleep
#include <pthread.h>   // pthread_reate pthread_join
#include <iostream>    // cout endl
#include <cxxopts.hpp> // cxxopts::

using namespace std;

// 声明用于保存命令行参数的静态变量
static int cpp_debugs_threads{2}, cpp_debugs_index{3};

/*
 *
 */
struct FabArgs
{
    int index;
    int result;
};

/*
 * 计算斐波那契数列的第 n 位的值
 * 第一位 1
 * 第二位 1
 * 第三位 2
 * 第四们 3
 * ...
 * ...
 */
void *fibonacci(void *args)
{
    int i{1}, j{1}, k{3};
    FabArgs *p = (FabArgs *)args;

    // 如果是前两项就直接返回 1
    if (p->index <= 2)
    {
        p->result = 1;
        return NULL;
    }
    while (k <= p->index)
    {
        p->result = i + j;
        i = j;
        j = p->result;

        // 为了方便调试这里加一个 sleep 1s
        sleep(1);
        k = k + 1;
    }
    return NULL;
}

/*
 * 处理命令行参数
 */
void parser_args(int argc, char *argv[])
{
    cxxopts::Options options("cpp-debugs", "cpp debug program");
    options.add_options()("t,thread", "并发的线程数量", cxxopts::value<int>()->default_value("2"))("i,index", "计算斐波那契数列的第 index 位", cxxopts::value<int>()->default_value("3"))("h,help", "打印帮忙文档");
    cxxopts::ParseResult result = options.parse(argc, argv);
    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }
    cout << "开始进行命令行参数处理" << endl;

    // 处理 thread 参数
    if (result.count("thread"))
    {
        int t = result["thread"].as<int>();
        if (t >= 4)
        {
            cout << "thread 参数大于 4, 调整到 4" << endl;
            t = 4;
        }
        cpp_debugs_threads = t;
        cout << "    --thread=" << t << endl;
    }
    // 处理 index 参数
    if (result.count("index"))
    {
        int t = result["index"].as<int>();
        if (t >= 100)
        {
            cout << "index 参数大于 100, 调整到 100" << endl;
            t = 100;
        }
        cpp_debugs_index = t;
        cout << "    --index=" << t << endl;
    }
}

int main(int argc, char *argv[])
{
    // 处理命令行参数
    parser_args(argc, argv);

    // 线程、函数参数、返回码
    pthread_t threads[cpp_debugs_threads];
    FabArgs args[cpp_debugs_threads];
    int errs[cpp_debugs_threads];

    // 启动线程
    for (int i = 0; i < cpp_debugs_threads; i++)
    {
        args[i].index = cpp_debugs_index;
        errs[i] = pthread_create(&threads[i], NULL, fibonacci, &args[i]);
        if (errs[i] != 0)
        {
            exit(1);
        }
    }

    // 等待线程结束
    for (int i = 0; i < cpp_debugs_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // 打印结果
    for (int i = 0; i < cpp_debugs_threads; i++)
    {
        std::cout << "线程 " << i << " " << "计算斐波那契数列的第 " << args[i].index << " 位的值 = " << args[i].result << std::endl;
    }
    return 0;
}