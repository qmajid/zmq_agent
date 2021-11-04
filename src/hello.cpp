#include "hello.h" 
#include <random>

Test::Test() 
{
	
}

Test::~Test() 
{
	
}

void Test::hello_google_benchmark(int value) 
{
    int r = random() / value;
}

