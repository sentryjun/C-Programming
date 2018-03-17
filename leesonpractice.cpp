#include <cstdio>

class Circle
{
    private:
    double x;
    double y;
    double radius;
    public:
    Circle(double x= 0, double y = 0, double radius = 0)
    {
        this->setX(x,y);
        this->setRadius(radius);
    }
    void setX(double x, double y)
    {
        this->x =  x;
        this->y = y;
    }
    void setRadius(double radius)
    {
        this->radius = radius;
    }
    double area()
    {
        double Pi = 3.1415926;
        return Pi*radius*radius;
    }
    double lenth()
    {
        double Pi = 3.1415926;
        return Pi*radius*2;
    }
};

int main(int argc, char** argv)
{
    Circle myCircle(1.7, 3.2, 4.2);
    printf("%lf\n%lf", myCircle.area(), myCircle.lenth());
    myCircle.setRadius(8.2);
    printf("%lf\n%lf", myCircle.area(), myCircle.lenth());
    return 0;
    
}