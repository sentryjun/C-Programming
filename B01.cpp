#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class Student {
    private:
        char name[21];
        int age;
        int id;
        int scores[4];
        double average;
    public:
        void setName(const char * stName)
        {
            strcpy(name,stName);
        }
        
        void setAge(const char* Age)
        {
            age = (int)atoi(Age);
        }

        void setId(const char* Id)
        {
            id = (int)atoi(Id);
        }

        void setScores()
        {
            for (int i = 0; i < 4; i++)
            {
                //scores[i] = atoi(Scores[i]);
                scanf(",%d", &scores[i]);
            }
        } 

        void input() {
            char tempstr[21];
            std::cin.getline(tempstr, 21, ',');
            this->setName(tempstr);
            std::cin.getline(tempstr, 21, ',');
            this->setAge(tempstr);
            std::cin.getline(tempstr, 21, ',');
            this->setId(tempstr);
            //getchar();
            scanf("%d,%d,%d,%d", &scores[0],&scores[1],&scores[2],&scores[3]);
            
        }
        int calculate() {
            average = (double)(scores[1]+scores[2]+scores[3]+scores[0])/4;
            return average;
        }
        int output() {
            std::cout << name <<',' << age << ',' << id << ',' << average <<  std::endl;
            return 0;
        }
};

int main() {
	Student student;        // 定义类的对象
	student.input();        // 输入数据
	student.calculate();    // 计算平均成绩
	student.output();       // 输出数据
}