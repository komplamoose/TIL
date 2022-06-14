#include <iostream>

using namespace std;


int main()
{
    int n;
    cin >> n;
    int cnt=0;

    for (int i=1; i<=n; i++) {
        int num=i;
        while (num!=1) { // 1이면 종료
            if (num==5 || num== 17){ // 5, 혹은 17인 경우 무한루프 생김
                cnt++;
                break;
            }
            if (num%2==0) {
                num=num/2;
            }else {
                num=num*3;
                num=num-1;
            }
        }
    }

    cout << cnt << endl;
}
