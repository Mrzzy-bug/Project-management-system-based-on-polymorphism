#include <fstream>
#include <iostream>
#include <string>
#define FILENAME "empFile.txt"
using namespace std;

class Worker //ְ��������
{
public:
    virtual void showInfo() = 0;
    virtual string getDeptname() = 0;
    int m_id;//ְ�����
    string m_name;//ְ������
    int m_DeptId;//ְ�����ű��
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
    cout << "ְ�����:" << m_id
         << "\tְ������:" << this->m_name
         << "\t��λ:" << this->getDeptname()
         << "\t��λְ��:��ɾ�����������" << endl;
}
string Employee::getDeptname()
{
    return string("Ա��");
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
    cout << "ְ�����:" << this->m_id
         << "\tְ������:" << this->m_name
         << "\t��λ:" << this->getDeptname()
         << "\t��λְ��:����ϰ彻��������͹���ְ��" << endl;
}
string Manager::getDeptname()
{
    return string("����");
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
    cout << "ְ�����:" << this->m_id
         << "\tְ������:" << this->m_name
         << "\t��λ:" << this->getDeptname()
         << "\t��λְ��:����ְ���;���" << endl;
}
string Boss::getDeptname()
{
    return string("�ϰ�");
}

class WorkerManager //ְ��������
{
public:
    WorkerManager();
    void show_menu(); //��ʾ����
    void exit_menu(); //�˳�����
    int m_EmpNum;     //��¼ְ������
    Worker **m_EmpArray;//Ա�������ָ�� ����
    void Add_Emp(); //���ְ���ĺ���
    void save();    //�����ļ�����
    bool m_FileIsEmpty;//�ж��ļ��Ƿ�Ϊ��
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

WorkerManager::WorkerManager() //���캯��
{
    //�ļ�������
    ifstream ifs;
    ifs.open(FILENAME, ios::in);//���ļ�
    if (!ifs.is_open())
    {
       // cout << "�ļ�������" << endl;
        //��ʼ��
        this->m_EmpNum = 0;
        this->m_EmpArray = NULL;
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    //�ļ���������Ϊ��
    char ch;
    ifs >> ch;
    if (ifs.eof())
    {
        //�ļ�Ϊ��
        //  cout << "�ļ�Ϊ��!" << endl;
        this->m_EmpNum = 0;//��ʼ������
        this->m_EmpArray = NULL;//��ʼ������ָ��
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }

    //�ļ��������ݲ�Ϊ��
    int num = this->get_EmpNum();
    // cout << "ְ������Ϊ��" << num << endl;
    this->m_EmpNum = num;
    //���ٿռ�
    this->m_EmpArray = new Worker *[this->m_EmpNum];
    //���ļ��е����ݣ��浽������
    this->init_Emp();
}

//��ʾ����
void WorkerManager::show_menu()
{
    cout << "********************************************" << endl;
    cout << "********** ��ӭʹ��ְ������ϵͳ! ***********" << endl;
    cout << "************** 0.�˳�����ϵͳ **************" << endl;
    cout << "************** 1.����ְ����Ϣ **************" << endl;
    cout << "************** 2.��ʾְ����Ϣ **************" << endl;
    cout << "************** 3.ɾ��ְ����Ϣ **************" << endl;
    cout << "************** 4.�޸�ְ����Ϣ **************" << endl;
    cout << "************** 5.����ְ����Ϣ **************" << endl;
    cout << "************** 6.���ձ������ **************" << endl;
    cout << "************** 7.��������ĵ� **************" << endl;
}

//�˳�����
void WorkerManager ::exit_menu()
{
    cout << "��ӭ�´�ʹ��лл" << endl;
    system("pause");
    exit(0);
}

//��Ӻ���
void WorkerManager ::Add_Emp()
{
    cout << "���������ְ��������" << endl;
    int addNum = 0;
    cin >> addNum;
    if (addNum > 0)
    {
        int newSize = this->m_EmpNum + addNum;     //�����¿ռ������=ԭ����¼������+�����ӵ�����
        Worker **newSpace = new Worker *[newSize]; //�����¿ռ�
        if (this->m_EmpArray != NULL)//��ԭ�ռ��µ����ݴ�ŵ��¿ռ���
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }
        //����������
        for (int i = 0; i < addNum; i++)

        {
            int id;      //ְ�����
            string name; //ְ������
            int dSelect; //����ѡ��
            cout << "�������" << i + 1 << "����ְ�����:" << endl;
            cin >> id;
            cout << "�������" << i + 1 << "����ְ������:" << endl;
            cin >> name;
            cout << "��ѡ���ְ���ĸ�λ��" << endl;
            cout << "1����ְͨ��" << endl;
            cout << "2,����" << endl;
            cout << "3,�ϰ�" << endl;
            cin >> dSelect;

            Worker *worker = NULL;//��ʼ����
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
            //������ְ��ְ�𣬱��浽������
            newSpace[this->m_EmpNum + i] = worker;
        }
        //�ͷ�ԭ�пռ�
        delete[] this->m_EmpArray;
        //�����¿ռ��ָ��
        this->m_EmpArray = newSpace;
        //�����µ�ְ����
        this->m_EmpNum = newSize;
        this->m_FileIsEmpty = false;//����ְ����Ϊ��
        cout << "�ɹ����" << addNum << "��ְ��" << endl;
        this->save(); //�������ݵ��ļ���
    }
    else
    {
        cout << "������������" << endl;
    }
    system("pause");
    system("cls");
}

//�����ļ�
void WorkerManager::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out); //���ļ���д������
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_id << " "
            << this->m_EmpArray[i]->m_name << " "
            << this->m_EmpArray[i]->m_DeptId << " " << endl;
    }
    //�ر��ļ�11
    ofs.close();
}

int WorkerManager::get_EmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in); //���ļ�������
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

//��ʼ��Ա�� ���ļ��������
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

//չʾְ��
void WorkerManager::show_Emp()
{
    //�ж��ļ��Ƿ�Ϊ��
    if (this->m_FileIsEmpty)
    {
        cout << "�ļ������ڻ��¼Ϊ��!" << endl;
    }
    else
    {
        for (int i = 0; i < m_EmpNum; i++)
        {
            //���ö�̬���ú����ӿ�
            this->m_EmpArray[i]->showInfo();
        }
    }
    system("pause");
    system("cls");
}

//ɾ������ ����ǰ��
void WorkerManager::Del_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
    }
    else
    {
        cout << "��������Ҫɾ��ְ����ţ�" << endl;
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
            cout << "ɾ���ɹ�" << endl;
        }
        else
        {
            cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
        }
    }
    system("pause");
    system("cls");
}

//�ж��Ƿ���ں���
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

//�޸ĺ���
void WorkerManager ::Mod_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
    }
    else
    {
        cout << "�������޸�ְ���ı�ţ�" << endl;
        int id;
        cin >> id;
        int ret = this->IsExist(id);
        if (ret != -1)
        {
            //�鵽����
            delete this->m_EmpArray[ret];
            int newId = 0;
            string newName = "";
            int dSelect = 0;
            cout << "�鵽��" << id << "��ְ������������ְ���ţ�" << endl;
            cin >> newId;
            cout << "��������������" << endl;
            cin >> newName;
            cout << "�������¸�λ��" << endl;
            cout << "1����ְͨ��" << endl;
            cout << "2������" << endl;
            cout << "3���ϰ�" << endl;
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
            //�������� ��������
            this->m_EmpArray[ret] = worker;
            cout << "�޸ĳɹ�! " << endl;
            //���浽�ļ���
            this->save();
        }
        else
        {
            cout << "�޸�ʧ�ܣ����޴��ˣ�" << endl;
        }
    }
    system("pause");
    system("cls");
}

//���Һ���
void WorkerManager::Find_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
    }
    else
    {
        cout << "��������ҵķ�ʽ��" << endl;
        cout << "1����ְ����Ų��ң�" << endl;
        cout << "2����ְ���������ң�" << endl;
        int select = 0;
        cin >> select;
        if (select == 1)
        {
            int id;
            cout << "��������ҵ�ְ����ţ�" << endl;
            cin >> id;
            int ret = IsExist(id);
            if (ret != -1)
            {
                //���д���
                cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
                this->m_EmpArray[ret]->showInfo();
            }
            else
            {
                cout << "����ʧ�ܣ����޴��ˣ�" << endl;
            }
        }
        else if (select == 2)
        {
            string name;
            cout << "��������ҵ�������" << endl;
            cin >> name;
            //�ж��Ƿ�鵽�� ��־
            bool flag = true;
            for (int i = 0; i < m_EmpNum; i++)
            {
                if (this->m_EmpArray[i]->m_name == name)
                {
                    cout << "���ҳɹ���ְ�����Ϊ��"
                         << this->m_EmpArray[i]->m_id
                         << "��ְ����Ϣ���£�" << endl;
                    flag = true;
                    this->m_EmpArray[i]->showInfo();
                }
            }
            if (flag == false)
            {
                cout << "����ʧ�ܣ����޴��ˣ�" << endl;
            }
        }
        else
        {
            cout << "����ѡ������" << endl;
        }
    }
    system("pause");
    system("cls");
}

//������
void WorkerManager::Sort_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
        system("pause");
        system("cls");
    }
    else
    {
        cout << "��ѡ������ʽ��" << endl;
        cout << "1����ְ���Ž�������" << endl;
        cout << "2����ְ���Ž��н���" << endl;
        int select = 0;
        cin >> select;
        for (int i = 0; i < m_EmpNum; i++)
        {
            int minOrMax = i; //������Сֵ�����ֵ�±� ѡ������
            for (int j = i + 1; j < this->m_EmpNum; j++)
            {
                if (select == 1) //����
                {
                    if (this->m_EmpArray[minOrMax]->m_id > this->m_EmpArray[j]->m_id)
                    {
                        minOrMax = j;
                    }
                }
                else //����
                {
                    if (this->m_EmpArray[minOrMax]->m_id < this->m_EmpArray[j]->m_id)
                    {
                        minOrMax = j;
                    }
                }
            }
            //�ж�һ��ʼ�϶� ��Сֵ�����ֵ �ǲ��� �������Сֵ ���ֵ,���Ǿͽ�������
            if (i != minOrMax)
            {
                Worker *temp = this->m_EmpArray[i];
                this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
                this->m_EmpArray[minOrMax] = temp;
            }
        }
        cout << "����ɹ��������Ľ��Ϊ��" << endl;
        this->save();
        this->show_Emp();
    }
}

//��պ���
void WorkerManager::Clean_File()
{
    cout << "ȷ����գ�" << endl;
    cout << "1��ȷ��" << endl;
    cout << "2������" << endl;
    int select = 0;
    cin >> select;
    if (select == 1)
    {
        //����ļ�
        ofstream ofs(FILENAME, ios::trunc); //�������ɾ���ļ����ؽ�
        ofs.close();
        if (this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                //ɾ��������ÿ��ְ������
                delete this->m_EmpArray[i];
                this->m_EmpArray[i] = NULL;
            }
            //ɾ����������ָ��
            delete[] this->m_EmpArray;
            this->m_EmpArray = NULL;
            this->m_EmpNum = 0;
            this->m_FileIsEmpty = true;
        }
        cout << "��ճɹ���" << endl;
    }
    system("pause");
    system("cls");
}

//��������
WorkerManager::~WorkerManager()
{
    if (this->m_EmpArray != NULL)//���
    {
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}

//������
int main()
{
    int choice;
    WorkerManager sm;
    while (true)
    {
        sm.show_menu();
        cout << "���������ѡ��:" << endl;
        cin >> choice;
        switch (choice)
        {
        case 0: //�˳�ϵͳ
            sm.exit_menu();
            break;
        case 1:
            sm.Add_Emp(); //����ְ��
            break;
        case 2:
            sm.show_Emp(); //��ʾ
            break;
        case 3:
            sm.Del_Emp(); //ɾ��
            break;
        case 4:
            sm.Mod_Emp(); //�޸�
            break;
        case 5:
            sm.Find_Emp(); //����
            break;
        case 6:
            sm.Sort_Emp(); //����
            break;
        case 7:
            sm.Clean_File(); //���
            break;
        default:
            system("cls");
            break;
        }
    }
    system("pause");
    return 0;
}
