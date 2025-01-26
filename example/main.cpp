#include <iostream>
#include <random>

#include "../include/ThreadPool.h"

/*
C++11 生成随机数

定义random_device对象
选择随机引擎（默认、线性、梅森、斐波那契）的实现类，将random_device的随机结果传入作为种子
选择要的分布，创建分布对象，将引擎传入作为种子，让分布对象输出随机数。
*/
std::random_device rd;
/*
std::mt19937是C++标准库中的一个伪随机数生成器类，它实现了梅森旋转算法（Mersenne Twister）。
mt19937类是一个随机数引擎，可以生成高质量的伪随机数序列。
*/
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist(-1000, 1000);
auto rnd = std::bind(dist, mt);


void simulate_hard_computation() {
  std::this_thread::sleep_for(std::chrono::milliseconds(2000 + rnd()));
}

// Simple function that adds multiplies two numbers and prints the result
void multiply(const int a, const int b) {
  simulate_hard_computation();
  const int res = a * b;
  std::cout << a << " * " << b << " = " << res << std::endl;
}

// Same as before but now we have an output parameter
void multiply_output(int & out, const int a, const int b) {
  simulate_hard_computation();
  out = a * b;
  std::cout << a << " * " << b << " = " << out << std::endl;
}

// Same as before but now we have an output parameter
int multiply_return(const int a, const int b) {
  simulate_hard_computation();
  const int res = a * b;
  std::cout << a << " * " << b << " = " << res << std::endl;
  return res;
}


int main(int argc, char *argv[])
{
  // Create pool with 3 threads
  ThreadPool pool(3);

  // Initialize pool
  pool.init();

  // Submit (partial) multiplication table
  for (int i = 1; i < 3; ++i) {
    for (int j = 1; j < 10; ++j) {
      pool.submit(multiply, i, j);
    }
  }

  // Submit function with output parameter passed by ref
  int output_ref;
  auto future1 = pool.submit(multiply_output, std::ref(output_ref), 5, 6);

  // Wait for multiplication output to finish
  future1.get();
  std::cout << "Last operation result is equals to " << output_ref << std::endl;

  // Submit function with return parameter
  auto future2 = pool.submit(multiply_return, 5, 3);

  // Wait for multiplication output to finish
  int res = future2.get();
  std::cout << "Last operation result is equals to " << res << std::endl;

  pool.shutdown();

  return 0;
}
