#include <iostream>

using namespace std;

class memInit {
private:
	int num1;
	int num2;
public:
	memInit(int _num1, int _num2) : num1(_num1), num2(_num2) { }
	void ShowInfo()
	{
		cout << "num1: " << num1 << ", num2: " << num2 << endl;
	}
};

int main()
{
	memInit mi(50, 70);

	mi.ShowInfo();
	return 0;
}