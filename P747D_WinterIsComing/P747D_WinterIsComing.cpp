/* 
Date: 2017/02/23
Author: Max Huang 

Please Reference CodeFore 747D for more information
This is the solution 1

Steps:
1. read all temperature into an array
2. transfer the array to: 
	if temperature<0  it will need to be winter wheel, define it as 1
	if temperature>=0 summer wheel is ok, difine it as 0
3. define rest = k - total 1  , define it is the rest winter wheel that I can use
4. if the rest whell is not 0, I still can use it
	the best chose will be something like: 1 0 1, 
	0 between two 1, since I change it to 1 can save two times tire change.
5. fulfill all 1 0 1 in the temperaure, and then I can try 1 0 0 1 if I still have winter tire
6. so it will like: 
	fill all 1 0 1
	fill all 1 0 0 1
	fill all 1 0 0 0 1
	...
	until I use up the all winter tire
*/ 
#include <iostream>

using namespace std;

int main() {
	int n=0, k=0; 
	int *temp = NULL;
	int t=0;
	int min=0;
	int rest=0;
	int emptyNum=1;
	int flag=0;
	
    cout << " CodeForce Problem 747D \n Winder Is Coming\n Please input N and K\n";
    cin >> n >>k;
    cout << "N is " << n <<endl;
    cout << "K is " << k <<endl;
    if(n<k){
    	cout << "N<K, return -1";
    	return (-1);
	}    	
    cout << " Input the temperature of each day, totally "<<n<<" days: ";
    
    // read all temperature into array, and formalize it to 1 0 1 0 0 0 1 1 ...
    temp = new int[n];    
    for(int i=0; i<n; i++){
    	cin >> t; 
    	if (t>=0)
    		*(temp+i) = 0;	// temp[i]=0
    	else{
    		*(temp+i) = 1; 
    		rest+=1;		// now rest means the sum of the temp array 
    	}    		
	}
    rest = k-rest;			// calculate the rest tires that I can use
    
    // just print the temperature to avoid error, can delate this part
    for(int i=0; i<n; i++){
    	cout << *(temp+i)<<" ";
	}
	cout << endl;
    
    while(rest!=0){
    	for(int i=0; i<n; i++){
    		if(temp[i]==1)		// means encounter 1 rise the flag to contine the try
    			flag=1;			// or just do nothing if not encoutner 1
    		else{
    			if(flag==1){
    				// fill all 0 to 1 since found
    				if((i+emptyNum)<n && temp[i+emptyNum]==1){
    					for(int j=0; j<emptyNum;j++){
    						temp[i+j]=1;
    						rest-=1;
    						if(rest==0)
    							break;
						}						
					}
					//reach the last of the temperature array
					else if((i+emptyNum)==n){         
    					for(int j=0; j<emptyNum;j++){
    						temp[i+j]=1;
    						rest-=1;
    						if(rest==0)
    							break;
						}						
					}
				}				
				flag=0;	
			}
			// if rest is 0, means all tires use up, break for loop, and while loop will end
			if(rest==0)		
				break;
		}
		emptyNum+=1;  // emptyNum record this time want to fill how much 0, start from 1
		flag=0;		  // clear flag since another round
	}
	
	// just print the temperature to avoid error, can delate this part
    for(int i=0; i<n; i++){
    	cout << *(temp+i)<<" ";
	}
	cout << endl;
	
	// calculate the min tire change times
    flag=0;		// this flag record previous result
    for(int i=0; i<n; i++){
    	if(temp[i]==1&&flag==0){
    		min+=1;
    		flag=1;
		}
		else if(temp[i]==0&&flag==1){
			min+=1;
			flag=0;
		}
	}
    cout<<"min: "<<min;
    
    system("pause");
}
