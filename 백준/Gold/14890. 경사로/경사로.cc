#include <iostream>

using namespace std;
int N, L;
int arr[101][101] = { 0, };

// -> 지나갈 수 있음: 모두 동일, 
// 지나가지 못하는 경우: 1층이 아닌 경우, 1층인데 두칸이 확보되지 않은 경우, 1층 변화 사이에 4칸이 확보되지않은 경우

int sum = 0;
void check(int n, int m)
{
	sum = 0;
	for (int i = 0; i < n; i++)
	{
		int upflag = 1;
		int downflag = 0;
		for (int j = 0; j < n-1; j++){
			//내려가는 경우
			if (arr[i][j + 1] + 1 == arr[i][j]) {
				if (downflag > 0) {
					downflag = -1;
					break;
				}
				downflag = 1;
				if (downflag == m)
				{
					downflag = 0;
					upflag = 0;
				}
			}
			//올라가는 경우
			else if (arr[i][j + 1] == arr[i][j]+1){
				if (downflag > 0){
					downflag = -1;
					break;
				}
				if (upflag >= m) upflag = 1;
				else{
					upflag = - 1;
					break;
				}
			}
			else if (arr[i][j+1]==arr[i][j]){
				// 내려가고 있었다.
				if (downflag >0) {
					downflag ++;
					upflag = 0;
					if (downflag == m) downflag = 0;
				}
				else {
					upflag++;
				}
			}
			else{
				upflag = -1;
				break;
			}
		}
		if (upflag == -1 || downflag >= 1 || downflag == -1) continue;
		sum++;
	}

	for (int j = 0; j < n; j++){
		int upflag = 1;
		int downflag = 0;
		for (int i = 0; i < n - 1; i++){
			//내려가는 경우
			if (arr[i+1][j] + 1 == arr[i][j]){
				if (downflag > 0) {
					downflag = -1;
					break;
				}
				downflag = 1;
				if (downflag == m)
				{
					downflag = 0;
					upflag = 0;
				}
			}
			//올라가는 경우
			else if (arr[i+1][j] == arr[i][j] + 1) {
				if (downflag > 0) {
					downflag = -1;
					break;
				}
				if (upflag >= m) upflag = 1;
				else {
					upflag = -1;
					break;
				}
			}
			else if (arr[i+1][j] == arr[i][j]) {
				// 내려가고 있었다.
				if (downflag > 0) {
					downflag++;
					upflag = 0;
					if (downflag == m) downflag = 0;
				}
				else {
					upflag++;
				}
			}
			// 2층 이상 차이나는 경우
			else{
				upflag = -1;
				break;
			}
		}
		if ( upflag == -1 || downflag >= 1 || downflag == -1) continue;
		sum++;
	}
}
int main(){
	cin >> N >> L;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			cin >> arr[i][j];
		}
	}
	
	check(N, L);
	cout << sum << endl;
	return 0;
}