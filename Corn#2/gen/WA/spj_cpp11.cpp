#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

int main() {
	ifstream fout("user_out");
	ifstream fans("answer");

	double ans,out;

	bool ok = true;

	fans>>ans;

	if(!(fout>>out)) {
		ok=false;
		cerr << "User_Output Not Found!" << endl;
	} else if(fabs(ans-out)>1e-9) {
		ok=false;
		cerr << "Find Diffrence: Expected " << ans << "; got " << out << "." << endl;
	}

	if (ok) {
		cerr << "OK!" << endl;
	}
	cout << (ok ? 100 : 0) << endl;
}
