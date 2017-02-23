/* 
Date: 2017/02/23
Author: Max Huang 

Please Reference CodeFore 747D for more information
This is the solution 2 

Steps:
	if temperature<0  it will need to be winter wheel, define it as 1
	if temperature>=0 summer wheel is ok, difine it as 0
1. do check when every time read the temperature
2. just to fill all tire to winter wire first
3. if I still need winter tire when next input temperature, and all tire used, 
	decide a best choice(it is summer temperature but use winter tire first) to change it to summer tire, 
	and let this new temperater as winter tire

*/ 
#include <iostream>

using namespace std;

int main() {
	int n=0, k=0; 			// n is total days, k is the max winter wheel can use days
	int *temp = NULL;		// average temperature of each days
	int t = 0;				// input t
	int *weight = NULL;		// define the weight
	
	int preday = 0;			// previous day is winter or not, it is default not winter wheel
	int min=0;				// min changes
	int priority = 0;
	
    cout << " CodeForce Problem 747D \n Winder Is Coming\n Please input N and K\n";
    cin >> n >>k;
    cout << "N is " << n <<endl;
    cout << "K is " << k <<endl;
    if(n<k){
    	cout << "N<K, return -1";
    	return (-1);
	}    	
    cout << " Input the temperature of each day, totally "<<n<<" days: ";
    
    temp = new int[n];    
    weight = new int[n];
    
    for(int i=0; i<n; i++){		// start this loop, sequence handle every temperature input
    	cin >> t; 
    	// if summer temperature, and previous day is summer also
    	// this day should be summer also
    	if (t>=0 && preday==0){ 
    		*(temp+i) = 0;		// temp[i]=0, just pointer coding style
    		priority = 0;
    		*(weight+i) = 0;
    		preday = 0;
    	}
    	// if summer temperature, but previous day is winter
    	// this day should be consider int 2 part		
    	else if (t>=0 && preday==1){	
    		// 1. still have tires (k) still can be use
			if(k>0){			
				*(temp+i) = 1;		//temp[i]=1  set the day is changeable winter wheel
    			priority += 1;
    			*(weight+i) = priority;
    			preday = 1;
    			k -= 1;
			}
			// 2. no enough tires (k) can be use, need to decide to change to winter tire or not
			else{
				// checking if there is summer temperature, using winter tire, 
				// and that day follow with summer tire, so no need to add tire change
	    		int j = 0; 
	    		bool canChange = false;
				for (j=0; j<i-1; j++){
					if (*(weight+j+1)==0){
						canChange = true;
						break;
					}	
				}		
				// 2.1 no find any place to change
				if (!canChange){
		    		*(temp+i) = 0;		//temp[i]=0
		    		priority = 0;
		    		*(weight+i) = 0;				
		    		preday = 0;
				}
				// 2.2 can change and the target index is j
				else{
		    		*(temp+i) = 1;		//temp[i]=1
		    		*(temp+j) = 0;
					priority = 0;
		    		preday = 1;
		    		*(weight+i) = -1;
		    		*(weight+j) = 0;					
				}
			}
		}
		// t<0, winter temperature, preday=winter or summer, need winter wheel, two case
    	else{					
    		// 1. still have winter tire, just use it
    		if(k>0){
				*(temp+i) = 1;		//temp[i]=1
	    		priority = 0;
	    		preday = 1;
	    		*(weight+i) = -1;
	    		k -= 1;
	    	}
	    	// 2. no more winter tire, need to change the previous winter tire in summer temperature
	    	else{  
				//find the candidate index j and set it to 0 first
	    		int j = 0; 
	    		bool needNewZeroWeight = true;
				// 2.1 if a summer temperature use winter tire, and it follows with summer tire
				// it will be the best choice since it do not incease tire change
				for (j=0; j<i-1; j++){
					if (*(weight+j+1)==0){
						needNewZeroWeight = false;
						break;
					}
				}
				// 2.2 if need to incease tire change, choose the max weighting index, it will be the best choice
				if (needNewZeroWeight == true){
					int maxIndex = 0;
					for (j=0; j<i; j++){
						if(*(weight+j) > *(weight+maxIndex))
							maxIndex = j;
					}
					j = maxIndex;
	    		}
	    		// this means no enough tire can be use, escape
				if(needNewZeroWeight == true && *(weight+j)<=0){
	    			cout << "-1\n";
	    			break;
	    		}
	    		// change the tire, the selected index is j
	    		*(temp+i) = 1;		//temp[i]=1
	    		*(temp+j) = 0;
				priority = 0;
	    		preday = 1;
	    		*(weight+i) = -1;
	    		*(weight+j) = 0;
			}
    	}	
	}
    
    // print the input result, this can be delate, just for checking
    for(int i=0; i<n; i++){
    	cout << *(temp+i)<<" ";
	}
	cout << endl;
    
    // calculate the min, using flag to record previous temperature
    int flag=0;
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
