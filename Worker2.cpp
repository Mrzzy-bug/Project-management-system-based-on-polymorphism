#include <fstream>
#include <iostream>
#include <string>
#define FILENAME "empFile.txt"
using namespace std;

class Worker //职工抽象类
{
public:
    virtual void showInfo() = 0;
    virtual string getDeptname() = 0;
    int m_id;//职工编号
    string m_name;//职工姓名
    int m_DeptId;//职工部门编号
};

class Employee : public Worker
{
public:
    Employee(int id, string name, int did);
    virtual void showInfo();
    virtual string getDeptname();
};
Employee::Employee(int id, string name, int did)
{
    this->m_id = id;
    this->m_name = name;
    this->m_DeptId = did;
}
void Employee::showInfo()
{
    cout << "职工编号:" << m_id
         << "\t职工姓名:" << this->m_name
         << "\t岗位:" << this->getDeptname()
         << "\t岗位职责:完成经理交给的任务" << endl;
}
string Employee::getDeptname()
{
    return string("员工");
}

class Manager : public Worker
{
public:
    Manager(int id, string name, int did);
    virtual void showInfo();
    virtual string getDeptname();
};
Manager::Manager(int id, string name, int did)
{
    this->m_id = id;
    this->m_name = name;
    this->m_DeptId = did;
}
void Manager::showInfo()
{
    cout << "职工编号:" << this->m_id
         << "\t职工姓名:" << this->m_name
         << "\t岗位:" << this->getDeptname()
         << "\t岗位职责:完成老板交给的任务和管理职工" << endl;
}
string Manager::getDeptname()
{
    return string("经理");
}

class Boss : public Worker
{
public:
    Boss(int id, string name, int did);
    virtual void showInfo();
    virtual string getDeptname();
};
Boss::Boss(int id, string name, int did)
{
    this->m_id = id;
    this->m_name = name;
    this->m_DeptId = did;
}
void Boss::showInfo()
{
    cout << "职工编号:" << this->m_id
         << "\t职工姓名:" << this->m_name
         << "\t岗位:" << this->getDeptname()
         << "\t岗位职责:管理职工和经理" << endl;
}
string Boss::getDeptname()
{
    return string("老板");
}

class WorkerManager //职工管理类
{
public:
    WorkerManager();
    void show_menu(); //显示函数
    void exit_menu(); //退出函数
    int m_EmpNum;     //记录职工人数
    Worker **m_EmpArray;//员工数组的指针 堆区
    void Add_Emp(); //添加职工的函数
    void save();    //保存文件函数
    bool m_FileIsEmpty;//判断文件是否为空
    int get_EmpNum();
    void init_Emp();
    void show_Emp();
    void Del_Emp();
    int IsExist(int id);
    void Mod_Emp();
    void Find_Emp();
    void Sort_Emp();
    void Clean_File();
    ~WorkerManager();
};

WorkerManager::WorkerManager() //构造函数
{
    //文件不存在
    ifstream ifs;
    ifs.open(FILENAME, ios::in);//读文件
    if (!ifs.is_open())
    {
       // cout << "文件不存在" << endl;
        //初始化
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    //文件存在数据为空
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        //文件为空
        //  cout << "文件为空!" << endl;
        this->m_EmpNum = 0;//初始化人数
        this->m_EmpArray = NULL;//初始化数组指针
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    //文件存在数据不为空
    int num = this->get_EmpNum();
    // cout << "职工人数为：" << num << endl;
    this->m_EmpNum = num;
    //开辟空间
    this->m_EmpArray = new Worker *[this->m_EmpNum];
    //将文件中的数据，存到数组中
    this->init_Emp();
}

//显示函数
void WorkerManager::show_menu()
{
    cout << "********************************************" << endl;
    cout << "********** 欢迎使用职工管理系统! ***********" << endl;
    cout << "************** 0.退出管理系统 **************" << endl;
    cout << "************** 1.增加职工信息 **************" << endl;
    cout << "************** 2.显示职工信息 **************" << endl;
    cout << "************** 3.删除职工信息 **************" << endl;
    cout << "************** 4.修改职工信息 **************" << endl;
    cout << "************** 5.查找职工信息 **************" << endl;
    cout << "************** 6.按照编号排序 **************" << endl;
    cout << "************** 7.清空所有文档 **************" << endl;
}

//退出函数
void WorkerManager ::exit_menu()
{
    cout << "欢迎下次使用谢谢" << endl;
    system("pause");
    exit(0);
}

//添加函数
void WorkerManager ::Add_Emp()
{
    cout << "请输入添加职工的数量" << endl;
    int addNum = 0;
    cin >> addNum;
    if (addNum > 0)
    {
        int newSize = this->m_EmpNum + addNum;     //计算新空间的人数=原来记录的人数+新增加的人数
        Worker **newSpace = new Worker *[newSize]; //开辟新空间
        if (this->m_EmpArray != NULL)//将原空间下的内容存放到新空间下
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }
        //输入新数据
        for (int i = 0; i < addNum; i++)

        {
            int id;      //职工编号
            string name; //职工姓名
            int dSelect; //部门选择
            cout << "请输入第" << i + 1 << "个新职工编号:" << endl;
            cin >> id;
            cout << "请输入第" << i + 1 << "个新职工姓名:" << endl;
            cin >> name;
            cout << "请选择该职工的岗位：" << endl;
            cout << "1，普通职工" << endl;
            cout << "2,经理" << endl;
            cout << "3,老板" << endl;
            cin >> dSelect;

            Worker *worker = NULL;//初始化，
            switch (dSelect)
            {
            case 1:
                worker = new Employee(id, name, 1);
                break;
            case 2:
                worker = new Manager(id, name, 2);
                break;
            case 3:
                worker = new Boss(id, name, 3);
                break;
            default:
                break;
            }
            //将创建职工职责，保存到数组中
            newSpace[this->m_EmpNum + i] = worker;
        }
        //释放原有空间
        delete[] this->m_EmpArray;
        //更改新空间的指向
        this->m_EmpArray = newSpace;
        //更新新的职工数
        this->m_EmpNum = newSize;
        this->m_FileIsEmpty = false;//更新职工不为空
        cout << "成功添加" << addNum << "名职工" << endl;
        this->save(); //保存数据到文件中
    }
    else
    {
        cout << "输入数据有误" << endl;
    }
    system("pause");
    system("cls");
}

//保存文件
void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out); //往文件中写入数据
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_id << " "
            << this->m_EmpArray[i]->m_name << " "
            << this->m_EmpArray[i]->m_DeptId << " " << endl;
    }
    //关闭文件11
    ofs.close();
}

int WorkerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in); //打开文件读数据
    int id;
    string name;
    int did;
    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> did)
    {
        num++;
    }
    return num;
}

//初始化员工 读文件里的数据
void WorkerManager::init_Emp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int id;
    string name;
    int did;
    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> did)
    {
        Worker *worker = NULL;
        if (did == 1)
        {
            worker = new Employee(id, name, did);
        }
        else if (did == 2)
        {
            worker = new Manager(id, name, did);
        }
        else
        {
            worker = new Boss(id, name, did);
        }
        this->m_EmpArray[index] = worker;
        index++;
    }
    ifs.close();
}

//展示职工
void WorkerManager::show_Emp()
{
    //判断文件是否为空
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空!" << endl;
    }
    else
    {
        for (int i = 0; i < m_EmpNum; i++)
        {
            //利用多态调用函数接口
            this->m_EmpArray[i]->showInfo();
        }
    }
    system("pause");
    system("cls");
}

//删除函数 数据前移
void WorkerManager::Del_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空！" << endl;
    }
    else
    {
        cout << "请输入想要删除职工编号：" << endl;
        int id = 0;
        cin >> id;
        int index = this->IsExist(id);
        if (index != -1)
        {
            for (int i = index; i < this->m_EmpNum - 1; i++)
            {
                this->m_EmpArray[i] = this->m_EmpArray[i + 1];
            }
            this->m_EmpNum--;
            this->save();
            cout << "删除成功" << endl;
        }
        else
        {
            cout << "删除失败，未找到该职工" << endl;
        }
    }
    system("pause");
    system("cls");
}

//判断是否存在函数
int WorkerManager::IsExist(int id)
{
    int index = -1;
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        if (this->m_EmpArray[i]->m_id == id)
        {
            index = i;
            break;
        }
    }
    return index;
}

//修改函数
void WorkerManager ::Mod_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空！" << endl;
    }
    else
    {
        cout << "请输入修改职工的编号：" << endl;
        int id;
        cin >> id;
        int ret = this->IsExist(id);
        if (ret != -1)
        {
            //查到此人
            delete this->m_EmpArray[ret];
            int newId = 0;
            string newName = "";
            int dSelect = 0;
            cout << "查到：" << id << "号职工，请输入新职工号：" << endl;
            cin >> newId;
            cout << "请输入新姓名：" << endl;
            cin >> newName;
            cout << "请输入新岗位：" << endl;
            cout << "1、普通职工" << endl;
            cout << "2、经理" << endl;
            cout << "3、老板" << endl;
            cin >> dSelect;
            Worker *worker = NULL;
            switch (dSelect)
            {
            case 1:
                worker = new Employee(newId, newName, dSelect);
                break;
            case 2:
                worker = new Manager(newId, newName, dSelect);
                break;
            case 3:
                worker = new Boss(newId, newName, dSelect);
                break;
            default:
                break;
            }
            //更新数据 到数组中
            this->m_EmpArray[ret] = worker;
            cout << "修改成功! " << endl;
            //保存到文件中
            this->save();
        }
        else
        {
            cout << "修改失败，查无此人！" << endl;
        }
    }
    system("pause");
    system("cls");
}

//查找函数
void WorkerManager::Find_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空！" << endl;
    }
    else
    {
        cout << "请输入查找的方式：" << endl;
        cout << "1、按职工编号查找：" << endl;
        cout << "2、按职工姓名查找：" << endl;
        int select = 0;
        cin >> select;
        if (select == 1)
        {
            int id;
            cout << "请输入查找的职工编号：" << endl;
            cin >> id;
            int ret = IsExist(id);
            if (ret != -1)
            {
                //查有此人
                cout << "查找成功！该职工信息如下：" << endl;
                this->m_EmpArray[ret]->showInfo();
            }
            else
            {
                cout << "查找失败，查无此人！" << endl;
            }
        }
        else if (select == 2)
        {
            string name;
            cout << "请输入查找的姓名：" << endl;
            cin >> name;
            //判断是否查到的 标志
            bool flag = true;
            for (int i = 0; i < m_EmpNum; i++)
            {
                if (this->m_EmpArray[i]->m_name == name)
                {
                    cout << "查找成功，职工编号为："
                         << this->m_EmpArray[i]->m_id
                         << "号职工信息如下：" << endl;
                    flag = true;
                    this->m_EmpArray[i]->showInfo();
                }
            }
            if (flag == false)
            {
                cout << "查找失败，查无此人！" << endl;
            }
        }
        else
        {
            cout << "输入选项有误！" << endl;
        }
    }
    system("pause");
    system("cls");
}

//排序函数
void WorkerManager::Sort_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空！" << endl;
        system("pause");
        system("cls");
    }
    else
    {
        cout << "请选择排序方式：" << endl;
        cout << "1、按职工号进行升序" << endl;
        cout << "2、按职工号进行降序" << endl;
        int select = 0;
        cin >> select;
        for (int i = 0; i < m_EmpNum; i++)
        {
            int minOrMax = i; //声明最小值或最大值下标 选择排序
            for (int j = i + 1; j < this->m_EmpNum; j++)
            {
                if (select == 1) //升序
                {
                    if (this->m_EmpArray[minOrMax]->m_id > this->m_EmpArray[j]->m_id)
                    {
                        minOrMax = j;
                    }
                }
                else //降序
                {
                    if (this->m_EmpArray[minOrMax]->m_id < this->m_EmpArray[j]->m_id)
                    {
                        minOrMax = j;
                    }
                }
            }
            //判断一开始认定 最小值或最大值 是不是 计算的最小值 最大值,不是就交换数据
            if (i != minOrMax)
            {
                Worker *temp = this->m_EmpArray[i];
                this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
                this->m_EmpArray[minOrMax] = temp;
            }
        }
        cout << "排序成功！排序后的结果为：" << endl;
        this->save();
        this->show_Emp();
    }
}

//清空函数
void WorkerManager::Clean_File()
{
    cout << "确定清空？" << endl;
    cout << "1、确定" << endl;
    cout << "2、返回" << endl;
    int select = 0;
    cin >> select;
    if (select == 1)
    {
        //清空文件
        ofstream ofs(FILENAME, ios::trunc); //如果存在删除文件后重建
        ofs.close();
        if (this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                //删除堆区的每个职工对象
                delete this->m_EmpArray[i];
                this->m_EmpArray[i] = NULL;
            }
            //删除堆区数组指针
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_EmpNum = 0;
            this->m_FileIsEmpty = true;
        }
        cout << "清空成功！" << endl;
    }
    system("pause");
    system("cls");
}

//析构函数
WorkerManager::~WorkerManager()
{
    if (this->m_EmpArray != NULL)//清空
    {
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}

//主函数
int main()
{
    int choice;
    WorkerManager sm;
    while (true)
    {
        sm.show_menu();
        cout << "请输入你的选择:" << endl;
        cin >> choice;
        switch (choice)
        {
        case 0: //退出系统
            sm.exit_menu();
            break;
        case 1:
            sm.Add_Emp(); //增加职工
            break;
        case 2:
            sm.show_Emp(); //显示
            break;
        case 3:
            sm.Del_Emp(); //删除
            break;
        case 4:
            sm.Mod_Emp(); //修改
            break;
        case 5:
            sm.Find_Emp(); //查找
            break;
        case 6:
            sm.Sort_Emp(); //排序
            break;
        case 7:
            sm.Clean_File(); //清空
            break;
        default:
            system("cls");
            break;
        }
    }
    system("pause");
    return 0;
}
