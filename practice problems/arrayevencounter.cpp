#include <iostream>

int main()
{

    int count = 0;
    int arr[11] = {4, 7, 10, 3, 8, 4 , 19, 18 ,16 , 14, 12};
    
    for(int i = 0; i < 11; i++){
        if(arr[i] % 2 == 0){
            count++;
        }
         
    }
    
            std::cout << count;
   return 0;
}
