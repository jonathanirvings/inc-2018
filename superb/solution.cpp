#include<stdio.h>
#include<string.h>
#include<algorithm>

using namespace std;

int data[100010];
const int MAX_INT = 0x7ffffff;

int getSuperb(int data[], int n){
	int cntData[20];
	memset(cntData, 0, sizeof(cntData));

	for(int i=0; i<n; i++){
		int num = data[i];
		cntData[num]++;
	}

	int calcMax = 0;
	for(int i=0; i<=9; i++){
		if(calcMax < cntData[i]){
			calcMax = cntData[i];
		}
	}

	return n - calcMax;
}

int dpGreat[100010][10];
int getGreat(int data[], int n){
	memset(dpGreat, 0, sizeof(dpGreat));
	
	for(int i=0; i<n; i++){
		for(int j=0; j<10; j++){
			if(i == 0){
				if(data[i] != j){
					dpGreat[i][j] = 1;
				}
			}
			else{
				int mn1 = j-1 >= 0 ? dpGreat[i-1][j-1] : MAX_INT;
				int mn2 = dpGreat[i-1][j];
				int mn3 = j+1 <= 9 ? dpGreat[i-1][j+1] : MAX_INT;
				int mn = min( min(mn1, mn2), mn3 );
				if(data[i] != j){
					mn += 1;
				}

				dpGreat[i][j] = mn;
			}
		}
	}

	// for(int i=0; i<n; i++){
	// 	for(int j=0; j<10; j++){
	// 		printf("%d ", dpGreat[i][j]);
	// 	}
	// 	printf("\n");
	// }

	int res = MAX_INT;
	for(int i=0; i<10; i++){
		res = min(res, dpGreat[n-1][i]);
	}

	return res;
}

const int MAX_SEQ = 3;
int dpGood[100010][MAX_SEQ + 2][10];
int getGood(int data[], int n){
	// memset(dpGood, -1, sizeof(dpGood));

	for(int i=0; i<n; i++){
		for(int j=0; j<MAX_SEQ; j++){
			for(int k=0; k<10; k++){
				dpGood[i][j][k] = MAX_INT;
			}
		}
	}

	for(int i=0; i<n; i++){
		for(int j=0; j<MAX_SEQ; j++){
			for(int k=0; k<10; k++){
				if(i==0){
					if(j==0){
						if(data[i] == k){
							dpGood[i][j][k] = 0;
						}
						else{
							dpGood[i][j][k] = 1;
						}
					}
				}
				else{
					if(j == 0){
						int mn = MAX_INT;
						for(int prev=0; prev<10; prev++){
							if(abs(k-prev) > 1){
								mn = min(mn, dpGood[i-1][MAX_SEQ-1][prev]);
							}							
						}

						if(data[i] != k){
							mn += 1;
						}

						dpGood[i][j][k] = mn;
					}
					else{
						int prev = j-1;

						int mn1 = k-1 >= 0 ? dpGood[i-1][prev][k-1] : MAX_INT;
						int mn2 = dpGood[i-1][prev][k];
						int mn3 = k+1 <= 9 ? dpGood[i-1][prev][k+1] : MAX_INT;
						int mn = min( min(mn1, mn2), mn3 );

						if(j == MAX_SEQ - 1){
							int mn4 = k-1 >= 0 ? dpGood[i-1][j][k-1] : MAX_INT;
							int mn5 = dpGood[i-1][j][k];
							int mn6 = k+1 <= 9 ? dpGood[i-1][j][k+1] : MAX_INT;

							mn = min( mn, min( min(mn4, mn5), mn6) );
						}

						if(data[i] != k){
							mn += 1;
						}

						dpGood[i][j][k] = mn;

					}
				}
			}
		}
	}

	// for(int k=0; k<MAX_SEQ; k++){
	// 	printf("SEQ: %d\n", k);
	// 	for(int i=0; i<n; i++){
	// 		for(int j=0; j<10; j++){
	// 			if(dpGood[i][k][j] >= MAX_INT){
	// 				printf("- ");
	// 			}
	// 			else{
	// 				printf("%d ", dpGood[i][k][j]);
	// 			}
	// 		}
	// 		printf("\n");
	// 	}
	// }

	int res = MAX_INT;
	for(int i=0; i<10; i++){
		res = min(res, dpGood[n-1][MAX_SEQ-1][i]);
	}

	return res;
}

int main(){
	int nt, n;

	//scanf("%d", &nt);

	//for(int t=0; t<nt; t++){
		scanf("%d", &n);
		
		for(int i=0; i<n; i++){
			scanf("%d", &data[i]);
		}

		int superb = getSuperb(data, n);
		int great = getGreat(data, n);
		int good = getGood(data, n);

		//printf("Case %d: %d %d %d\n", t+1, good, great, superb);
		printf( "%d %d %d\n", good, great, superb );

	//}

	return 0;
}