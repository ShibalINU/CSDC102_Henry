#include <iostream>
#include <string>

using namespace std;

class Rectangle{
    private:
        double width, height;
        
    public:
        Rectangle(double w, double h){
           width = w;
           height = h;
        } 
        double getArea(){
            return width * height;
        }
        double getPerimeter(){
            return 2 * (width + height);
        }
        bool isSquare(){
            return width == height;
        }
};
int main()
{
    double w, h;
    
    for(int i = 1; i <= 3; i++){
        cout << "rectangle " << i << ": " << endl;
        
        cout << "Enter width: " << endl;
        cin >> w; 
    
        cout << "Enter height: " << endl;
        cin >> h;
        
        Rectangle rectangle(w, h);
        
        cout << "Area: " << rectangle.getArea() << endl;
        cout << "Perimeter: " << rectangle.getPerimeter() << endl;
        if(rectangle.isSquare()){
            cout << "===it is square===" << endl;
        }else{
            cout << "===it ain't a square===" << endl;
        }
    }
    return 0;
}
