#include <iostream>  
#include <fstream>  
#include <vector>  
#include <string>  
#include <cstdlib> // 用于rand()和srand()  
#include <ctime>   // 用于time() 
#include <random>  
#include <chrono> 

using namespace std;    
 

// 消息类  
class ObstacleMessage {  
public:  
    string obstacle_direction;  
  
    ObstacleMessage(string direction) : obstacle_direction(direction) {}  
};  
  
// 订阅者接口  
class Subscriber {  
public:  
    virtual void notify(const ObstacleMessage& msg) = 0;  
    virtual ~Subscriber() {}  
};  

class Tire {  
private:  
    string geshu;       //个数
    string model_wheel; //型号 
    string size;        //尺寸
public:  
    Tire(string g = "4个", string m = "公路轮、麦克纳姆轮",string s = "175mm") : geshu(g), model_wheel(m),size(s) {}  
  
    void setGeshu(string g) { geshu = g; }
    void setModel_wheel(string m) { model_wheel = m; }  
    void setSize(string s) { size = s; }  
  
    void print() const {  
        cout << "轮胎（ " << geshu << ") 型号:" << model_wheel << " 尺寸:" << size <<endl;  
    }  
  
    void save(const string& filename) const {  
        ofstream file(filename, ios::app); // 注意这里使用了 std::ios::app  
        if (file.is_open()) {  
            file << "轮胎（ " << geshu << "） 型号:" << model_wheel << " 尺寸:" << size << endl;  
            // 文件自动在析构时关闭，但显式关闭也是一个好习惯（尽管在这个例子中不是必需的）  
            // file.close();  
        } else {  
            // 处理文件打开失败的情况  
            // 可以通过抛出异常、记录日志或设置错误码等方式进行  
            throw runtime_error("无法打开文件以追加数据。");  
        }  
    }  
};  
  
class Chassis:public Tire,public Subscriber {  
    // 类似地定义底盘的属性和方法
private:
    string id;              //编号
    string model;           //型号
    string wheelbase;       //轴距
    string track_width;     //轮距
    string ground_clearance;//最小离地间隙
    string turning_radius;  //最小转弯半径
    string drive_mode;      //驱动形式
    string maximum_range;   //最大行程
public:  
    Chassis(string id = "Unknown", string model = "SCOUT MINI",string wheelbase = "451mm",
    string track_width ="490mm",string ground_clearance = "115mm",string turning_radius = "0m",
    string drive_mode = "四轮四驱",string maximum_range = "10KM") : 
    Tire(),id(id), model(model), wheelbase(wheelbase), track_width(track_width),  
    ground_clearance(ground_clearance), turning_radius(turning_radius),  
    drive_mode(drive_mode), maximum_range(maximum_range) {}  
  
    void setId(string i) { id = i; }
    void setModel(string i) { model = i; }
    void setWheelbase(string i) { wheelbase = i; }
    void setTrack_width(string i) { track_width = i; }
    void setGround_clearance(string i) { ground_clearance = i; }
    void setTurning_radius(string i) { turning_radius = i; }
    void setDrive_mode(string i) { drive_mode = i; }
    void setMaximum_range(string i) { maximum_range = i; }  
  
    void print() const {  
        cout << "底盘编号:"<< id <<" 型号:" << model << " 轴距:" << wheelbase 
        << " 轮距:" << track_width << " 最小离地间隙:" << ground_clearance 
        << " 最小转弯半径:" << turning_radius << " 驱动形式:" << drive_mode 
        << " 最大行程:" << maximum_range <<endl;
        Tire::print();  
    }  

    void save(const string& filename) const {  
        ofstream file(filename, ios::app); // 注意这里使用了 std::ios::app  
        if (file.is_open()) {  
            file << "底盘编号:"<< id <<" 型号:" << model << " 轴距:" << wheelbase 
            << " 轮距:" << track_width << " 最小离地间隙:" << ground_clearance 
            << " 最小转弯半径:" << turning_radius << " 驱动形式:" << drive_mode 
            << " 最大行程:" << maximum_range <<endl;  
            // 文件自动在析构时关闭，但显式关闭也是一个好习惯（尽管在这个例子中不是必需的）  
            // file.close();  
        } else {  
            // 处理文件打开失败的情况  
            // 可以通过抛出异常、记录日志或设置错误码等方式进行  
            throw runtime_error("无法打开文件以追加数据。");  
        }  
    }

    void notify(const ObstacleMessage& msg) override {  // 底盘模块类，实现订阅者接口
        if (msg.obstacle_direction == "1") {  
            cout << "后退..." << endl;  
        } else if (msg.obstacle_direction == "2") {  
            cout << "左转..." << endl;  
        } else if (msg.obstacle_direction == "3") {  
            cout << "右转..." << endl;  
        } else {  
            cout << "无障碍物或未知方向..." << endl;  
        }  
    }  
      
};

class AGX{                  //AGX套件参数
private:
    string geshu;           //个数
    string AGX_model;       //型号
    string AI_Capability;   //AI
    string CUDA_Cores;      //CUDA核心
    string Tensor_Cores;    //Tensor CORE
    string VRAM;            //显存
    string Storage;         //储存
public:
    AGX(string geshu = "1个",string AGX_model= "AGX Xavier",string AI_Capability = "32 TOPS",
    string CUDA_Cores = "512",string Tensor_Cores = "64",string VRAM = "32G",string Storage = "32G"):
    geshu(geshu), AGX_model(AGX_model), AI_Capability(AI_Capability), CUDA_Cores(CUDA_Cores), 
    Tensor_Cores(Tensor_Cores), VRAM(VRAM), Storage(Storage) {}
    
    void setGeshu(string i) { geshu = i; }
    void setAGX_model(string i) { AGX_model = i; }
    void setAI_Capability(string i) { AI_Capability = i; }
    void setCUDA_Cores(string i) { CUDA_Cores = i; }
    void setTensor_Cores(string i) { Tensor_Cores = i; }
    void setVRAM(string i) { VRAM = i; }
    void setStorage(string i) { Storage = i; }

    void print() const {  
        cout << "AGX套件（"<< geshu <<"） 型号:" << AGX_model << " AI:" << AI_Capability 
             << " CUDA核心:" << CUDA_Cores << " Tensor CORE:" << Tensor_Cores << " 显存:" 
             << VRAM << " 存储:" << Storage <<endl;
    } 

    void save(const string& filename) const {  
        ofstream file(filename, ios::app); // 注意这里使用了 std::ios::app  
        if (file.is_open()) {  
            file << "AGX套件（"<< geshu <<"） 型号:" << AGX_model << " AI:" << AI_Capability 
                 << " CUDA核心:" << CUDA_Cores << " Tensor CORE:" << Tensor_Cores << " 显存:" 
                 << VRAM << " 存储:" << Storage <<endl;  
            // 文件自动在析构时关闭，但显式关闭也是一个好习惯（尽管在这个例子中不是必需的）  
            // file.close();  
        } else {  
            // 处理文件打开失败的情况  
            // 可以通过抛出异常、记录日志或设置错误码等方式进行  
            throw runtime_error("无法打开文件以追加数据。");  
        }  
    }

    
};

class Stereo_Camera{//双目摄像头参数
private:
    string geshu;   //个数
    string Model;   //型号
    string Camera;  //摄像头
    string RGB_Frame_Resolution;//分辨率
    string RGB_Frame_Rate;      //帧率
    string FOV;                 //fov
    string Depth_Frame_Rate;    //深度帧率
public:
    Stereo_Camera(string geshu = "1个",string Model = "RealSense D435i",string Camera = "D430",
    string RGB_Frame_Resolution = "19201080",string RGB_Frame_Rate = "30",string FOV = "8758",
    string Depth_Frame_Rate = "90"):
    geshu(geshu), Model(Model), Camera(Camera), RGB_Frame_Resolution(RGB_Frame_Resolution),  
    RGB_Frame_Rate(RGB_Frame_Rate), FOV(FOV), Depth_Frame_Rate(Depth_Frame_Rate) {}

    void setGeshu(string i) { geshu = i; }
    void setModel(string i) { Model = i; }
    void setCamera(string i) { Camera = i; }
    void setRGB_Frame_Resolution(string i) { RGB_Frame_Resolution = i; }
    void setRGB_Frame_Rate(string i) { RGB_Frame_Rate = i; }
    void setFOV(string i) { FOV = i; }
    void setDepth_Frame_Rate(string i) { Depth_Frame_Rate = i; }

    void print() const {  
        cout << "双目摄像头（"<< geshu <<"） 型号:" << Model << " 摄像头:" << Camera 
             << " RGB帧分辨率:" << RGB_Frame_Resolution << " RGB帧率:" << RGB_Frame_Rate << " FOV:" 
             << FOV << " 深度帧率:" << Depth_Frame_Rate <<endl;
    } 

    void save(const string& filename) const {  
        ofstream file(filename, ios::app); // 注意这里使用了 std::ios::app  
        if (file.is_open()) {  
            file << "双目摄像头（"<< geshu <<"） 型号:" << Model << " 摄像头:" << Camera 
                 << " RGB帧分辨率:" << RGB_Frame_Resolution << " RGB帧率:" << RGB_Frame_Rate << " FOV:" 
                 << FOV << " 深度帧率:" << Depth_Frame_Rate <<endl;  
            // 文件自动在析构时关闭，但显式关闭也是一个好习惯（尽管在这个例子中不是必需的）  
            // file.close();  
        } else {  
            // 处理文件打开失败的情况  
            // 可以通过抛出异常、记录日志或设置错误码等方式进行  
            throw runtime_error("无法打开文件以追加数据。");  
        }  
    }   
};

class LiDAR{//多线激光雷达
private:
    string geshu;
    string Model;  
    string Channels;
    string Range;
    string Consumption;
    vector<Subscriber*> subscribers;
public:
    LiDAR(string geshu = "1个",string Model = "RS-Helios-16p",string Channels = "16",
    string Range = "100m",string Consumption = "8W"):
    geshu(geshu), Model(Model), Channels(Channels), Range(Range), Consumption(Consumption) {}

    void setGeshu(string i) { geshu = i; }
    void setModel(string i) { Model = i; }
    void setChannels(string i) { Channels = i; }
    void setRange(string i) { Range = i; }
    void setConsumption(string i) { Consumption = i; }

    void print() const {  
        cout << "多线激光雷达（"<< geshu <<"） 型号:" << Model << " 通道数:" << Channels 
             << " 测试范围:" << Range << " 功耗:" << Consumption <<endl;
    } 

    void save(const string& filename) const {  
        ofstream file(filename, ios::app); // 注意这里使用了 std::ios::app  
        if (file.is_open()) {  
            file << "多线激光雷达（"<< geshu <<"） 型号:" << Model << " 通道数:" << Channels 
             << " 测试范围:" << Range << " 功耗:" << Consumption <<endl;  
            // 文件自动在析构时关闭，但显式关闭也是一个好习惯（尽管在这个例子中不是必需的）  
            // file.close();  
        } else {  
            // 处理文件打开失败的情况  
            // 可以通过抛出异常、记录日志或设置错误码等方式进行  
            throw runtime_error("无法打开文件以追加数据。");  
        }  
    }

    void addSubscriber(Subscriber* subscriber) {  
        subscribers.push_back(subscriber);  
    }  
  
    void publishObstacle(const string& obstacle_direction) {  
        ObstacleMessage msg(obstacle_direction);  
        for (auto subscriber : subscribers) {  
            subscriber->notify(msg);  
        }  
    }     
};

class Gyroscope{
private:
    string geshu;
    string Model;  
    string Manufacturer;
public:
    Gyroscope(string geshu = "1个",string Model = "CH110",string Manufacturer = "NXP"):
    geshu(geshu),Model(Model),Manufacturer(Manufacturer){}
    
    void setGeshu(string i) { geshu = i; }
    void setModel(string i) { Model = i; }
    void setManufacturer(string i) { Manufacturer = i; }

    void print() const {  
        cout << "9轴陀螺仪（"<< geshu <<"） 型号:" << Model << " 厂家:" << Manufacturer << endl;
    } 

    void save(const string& filename) const {  
        ofstream file(filename, ios::app); // 注意这里使用了 std::ios::app  
        if (file.is_open()) {  
            file << "9轴陀螺仪（"<< geshu <<"） 型号:" << Model << " 厂家:" << Manufacturer <<endl; 
            // 文件自动在析构时关闭，但显式关闭也是一个好习惯（尽管在这个例子中不是必需的）  
            // file.close();  
        } else {  
            // 处理文件打开失败的情况  
            // 可以通过抛出异常、记录日志或设置错误码等方式进行  
            throw runtime_error("无法打开文件以追加数据。");  
        }  
    }
};
class LCD{
private:
    string geshu;
    string Size;  
    string Model; 
public:
    LCD(string geshu = "1个",string Size = "11.6",string Model = "super"):
    geshu(geshu),Size(Size),Model(Model){}

    void setGeshu(string i) { geshu = i; }
    void setSize(string i) { Size = i; }
    void setModel(string i) { Model = i; }

    void print() const {  
        cout << "液晶显示屏（"<< geshu <<"） 尺寸:" << Size << " 型号:" << Model << endl;
    } 

    void save(const string& filename) const {  
        ofstream file(filename, ios::app); // 注意这里使用了 std::ios::app  
        if (file.is_open()) {  
            file << "液晶显示屏（"<< geshu <<"） 尺寸:" << Size << " 型号:" << Model << endl; 
            // 文件自动在析构时关闭，但显式关闭也是一个好习惯（尽管在这个例子中不是必需的）  
            // file.close();  
        } else {  
            // 处理文件打开失败的情况  
            // 可以通过抛出异常、记录日志或设置错误码等方式进行  
            throw runtime_error("无法打开文件以追加数据。");  
        }  
    }

};

class Battery{
private:
    string geshu;
    string Parameters;  
    string Supply;
    string Time; 
public:
    Battery(string geshu = "1个",string Parameters = "24V/15Ah",string Supply = "24V",string Time = "2H"):
    geshu(geshu),Parameters(Parameters),Supply(Supply),Time(Time){}

    void setGeshu(string i) { geshu = i; }
    void setParameters(string i) { Parameters = i; }
    void setSupply(string i) { Supply = i; }
    void setTime(string i) { Time = i; }

    void print() const {  
        cout << "电池模块（"<< geshu <<"） 参数:" << Parameters << " 对外供电:" << Supply << " 充电时长:" << Time << endl;
    } 

    void save(const string& filename) const {  
        ofstream file(filename, ios::app); // 注意这里使用了 std::ios::app  
        if (file.is_open()) {  
            file << "电池模块（"<< geshu <<"） 参数:" << Parameters << " 对外供电:" << Supply << " 充电时长:" << Time << endl; 
            // 文件自动在析构时关闭，但显式关闭也是一个好习惯（尽管在这个例子中不是必需的）  
            // file.close();  
        } else {  
            // 处理文件打开失败的情况  
            // 可以通过抛出异常、记录日志或设置错误码等方式进行  
            throw runtime_error("无法打开文件以追加数据。");  
        }  
    }
};

// 学生信息类  
class Student {  
private:
    string id;  
    string name;   
public:  
    Student(string i = "Unknown",string n = "Unknown") : name(n), id(i) {}  
  
    void setName(string n) { name = n; }  
    void setId(string i) { id = i; }  
  
    void print() const {  
        cout << "学号:" << id << " 姓名:" << name << endl;  
    }  
  
    void save(const string& filename) const {  
        ofstream file(filename, ios::app); // 注意这里使用了 std::ios::app  
        if (file.is_open()) {  
            file << "学号:" << id << endl;
            file << "姓名:" << name << endl;
            // 文件自动在析构时关闭，但显式关闭也是一个好习惯（尽管在这个例子中不是必需的）  
            // file.close();  
        } else {  
            // 处理文件打开失败的情况  
            // 可以通过抛出异常、记录日志或设置错误码等方式进行  
            throw runtime_error("无法打开文件以追加数据。");  
        }  
    }

}; 

class SmartCar:public AGX,public Stereo_Camera,public Gyroscope,public LCD,public Battery,public Student{  
private:  
    string id;
    Chassis* chassis;  
    LiDAR* lidar;        
public:
    SmartCar(string i = "Unknown") : id(i),chassis(new Chassis),AGX(),Stereo_Camera(),lidar(new LiDAR()),Gyroscope(),LCD(),Battery(),Student() {}  

    void setID(string i) { id = i; }  
    Chassis* getChassis() const {return chassis;}
    LiDAR* getLiDAR() const {return lidar;}

    void print() const {  
        cout << "智能车编号:" << id << endl;  
        chassis->print();   //chassis改成了指针
        AGX::print();
        Stereo_Camera::print();
        lidar->print();     //lidar改成了指针
        Gyroscope::print();
        LCD::print();
        Battery::print();
        Student::print();
        // ...  
    }  
  
    void save(const string& filename) const {  
        ofstream file(filename, ios::app); // 注意这里使用了 std::ios::app  
        if (file.is_open()) {  
            file << "智能车编号:" << id << endl;
            chassis->save(filename);    //chassis改成了指针
            AGX::save(filename);
            Stereo_Camera::save(filename);
            lidar->save(filename);      //lidar改成了指针
            Gyroscope::save(filename);
            LCD::save(filename);
            Battery::save(filename);
            Student::save(filename);
            file << "---" << endl;  
            // 文件自动在析构时关闭，但显式关闭也是一个好习惯（尽管在这个例子中不是必需的）  
            // file.close();  
        } else {  
            // 处理文件打开失败的情况  
            // 可以通过抛出异常、记录日志或设置错误码等方式进行  
            throw runtime_error("无法打开文件以追加数据。");  
        }  
    }
     
};  
  
char getRandomChar1() {    
    const std::string charset = "0123456789";    
    std::random_device rd;    
    std::mt19937 gen(rd());    
    std::uniform_int_distribution<> dis(0, charset.size() - 1);    
    return charset[dis(gen)];    
} 

char getRandomChar2() {    
    const std::string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";    
    std::random_device rd;    
    std::mt19937 gen(rd());    
    std::uniform_int_distribution<> dis(0, charset.size() - 1);    
    return charset[dis(gen)];    
}  
  
std::string generateCQUSN16() {    
    std::string cqusn = "cqusn"; // 初始前缀    
    for (int i = 0; i < 16; ++i) {    
        cqusn += getRandomChar1(); // 添加16个随机数字字符    
    }  
    cqusn += getRandomChar2();  // 添加1个随机大写英文字符  
    return cqusn; // cqusn  
} 

std::string generateCQUSN8() {  
    std::string dp = "dp"; // 初始前缀  
    for (int i = 0; i < 8; ++i) {  
        dp += getRandomChar1(); // 添加8个随机字符  
    }
    dp += getRandomChar2();  
    return dp; // dp 
}

void loadCarsFromFile(vector<SmartCar>& cars, const string& filename) {  
    ifstream file(filename);  
    if (!file.is_open()) {  
        cerr << "Failed to open file for reading." << endl;  
        return;  
    }  
    string line;  
    SmartCar currentCar;  
    while (getline(file, line)) {  
         if (line.substr(0, 16) == "智能车编号:") {             
            currentCar.setID(line.substr(16));          
        } else if (line.substr(0, 13) == "底盘编号:") {  
            size_t colon = line.find(':');
            Chassis* chassis = currentCar.getChassis(); 
            chassis->setId(line.substr(colon + 2,11));
        } else if (line.substr(0, 7) == "学号:") {  
            size_t colon = line.find(':');             
            currentCar.Student::setId(line.substr(colon + 2));
        }else if (line.substr(0, 7) == "姓名:") {  
            size_t colon = line.find(':');             
            currentCar.Student::setName(line.substr(colon + 2));
            cars.push_back(currentCar);
            currentCar = SmartCar();
        } 
    }  
    file.close();  
}

void displayCars(const vector<SmartCar>& cars, int currentIndex) {  //作业二的显示代码
    if (currentIndex < 0 || currentIndex >= cars.size()) return;  
    const SmartCar& car = cars[currentIndex];  
    car.print();  
}

void displayCars1(const vector<SmartCar>& cars, int currentIndex) {  
    if (currentIndex < 0 || currentIndex >= cars.size()) return;  
    const SmartCar& car = cars[currentIndex];
    LiDAR* lidar = cars[currentIndex].getLiDAR();
    Chassis* chassis = cars[currentIndex].getChassis();
    // 注册订阅者
    lidar->addSubscriber(chassis);

    // 模拟发布障碍物信息  
    lidar->publishObstacle("1"); // 前方障碍物  
    lidar->publishObstacle("2"); // 左前方障碍物  
    lidar->publishObstacle("3"); // 右前方障碍物  

    car.print();  
}

int main() {  
    
    srand(time(0));
    // 创建智能小车
    SmartCar* p[10];

    for (int i = 0; i < 10; ++i) {  
        p[i]=new SmartCar;  
        p[i]->setID(generateCQUSN16());

        Chassis* chassis = p[i]->getChassis();
        chassis->setId(generateCQUSN8());   

        // 分配学生（随机分配示例）  
        p[i]->Student::setId("stu" + to_string(rand() % 1000));  
        p[i]->Student::setName("Student_" + to_string(rand() % 1000));  
    }

    for (int i = 0; i < 10; ++i) {    
        p[i]->save("car1_info.txt");
        //p[i]->print();   
        // 保存和打印信息
    }
    ofstream file("car1_info.txt", ios::app);
    file.close();

    vector<SmartCar> loadedCars;  
    loadCarsFromFile(loadedCars, "car1_info.txt");

    int currentIndex = 0;  
    char key;  
    do {  
        displayCars1(loadedCars, currentIndex);  
        cout << "Press 'n' for next or 'p' for previous (current: " << currentIndex + 1 << "): ";  
        cin >> key;  
        if (key == 'n' && currentIndex < loadedCars.size() - 1) currentIndex++;  
        else if (key == 'p' && currentIndex > 0) currentIndex--;  
    } while (key == 'n' || key == 'p');

    return 0;  
}