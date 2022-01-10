#include <iostream>
#include <Networking/Base.h>

using namespace std;

int main()
{
	cout << "Hello Client! " << static_cast<int>(MyEnum::Two) << endl;
	return 0;
}
