#include <vector>
#include <iostream>

using namespace std;
int main()
{
	{
		std::vector<int> vec;
		for (int i = 0; i < 10; ++i)
			vec.push_back(i);
		// for (auto& itr : vec)
		// 	cout << itr << "  ";
        for (int i = 0; i < 10; ++i)
			cout << vec[i] << " ";
		cout << "\n";
	}
}