#include <iostream>
using namespace std;


int main() {
	//�˷��ھ���


	//��ӡ����
	for (int i = 1; i <= 9; i++) {
		//cout << i << endl;
		for (int j = 1; j <= i; j++) {
			cout << i << "*" << j << "=" << i*j << " ";
		}
		cout << endl;
	}
}
