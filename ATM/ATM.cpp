#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <windows.h>
using namespace std;
class ATM
{
private:
        string name;
        string password;
        string id;
        int money;
        int users;
public:
    bool isrepeat(string fp, string type, string contain);
    int getstrline(string fp, string type, string contain);
    string getstr(string fp, int i);
    int getmoney(string fp);
    int gettransmoney(string fp,int x);
    void login(string fp);
    void regist(string fp);
    void changepassword(string fp, int targetline, string newpassword);
    void changemoney(string fp, int targetline, int money);
    void save(string fp);
    void gain(string fp);
    void trans(string fp);
    void surface();
    void inquiry();
    void welcome();
    void goodbye();
    void reset(string fp);
};

//修改密码
void ATM::changepassword(string fp, int targetline, string newpassword)
{
    fstream read(fp);
    fstream write("temp.txt", ios::out | ios::trunc);
    string origin;
    for (int i = 1; !read.eof(); i++)
    {
        if (i == targetline)
        {
            getline(read, origin);
            write << "password: " << newpassword << endl;
        }
        else
        {
            getline(read, origin);
            write << origin << endl;
        }
    }
    read.close();
    write.close();
    write.open(fp, ios::out | ios::trunc);
    read.open("temp.txt");
    while (!read.eof())
    {
        getline(read, origin);
        write << origin << endl;
    }
    write.close();
    read.close();
    system("del temp.txt");
}

//修改余额
void ATM::changemoney(string fp, int targetline, int money)
{
    fstream read(fp);
    fstream write("temp.txt", ios::out | ios::trunc);
    string origin;
    for (int i = 1; !read.eof(); i++)
    {
        if (i == targetline)
        {
            getline(read, origin);
            write << money << endl;
        }
        else
        {
            getline(read, origin);
            write << origin << endl;
        }
    }
    read.close();
    write.close();
    write.open(fp, ios::out | ios::trunc);
    read.open("temp.txt");
    while (!read.eof())
    {
        getline(read, origin);
        write << origin << endl;
    }
    write.close();
    read.close();
    system("del temp.txt");
}

//存款
void ATM::save(string fp)
{
    int tempmoney;
    string select;
        cout << "*************************************************" << endl << endl;
        cout << "                 本机仅能识别100元纸币" << endl;
        cout << "               本机单次存款限额为3000元" << endl;
        cout << "*************************************************" << endl << endl;
    while (true)
    {        cout << "              请输入存款金额：" << endl;
        cin >> tempmoney;
        if (tempmoney % 100 != 0)
        {
            cout << "       您输入的金额必须是100的整数倍！" << endl;
            cout << "                 请重新输入！" << endl;
            continue;
        }
        else if (tempmoney < 0)
        {
            cout << "            请您输入正确的金额！" << endl;
            cout << "                 请重新输入！" << endl;
            continue;
        }
        else if(tempmoney>3000)
        {
            cout << "       您输入的金额不能大于3000！" << endl;
            cout << "                 请重新输入！" << endl;
            continue;
        }
        else
        {
            money = money + tempmoney;
            cout << "                      存款成功！" << endl;
            cout << "                 当前余额： " << money << "元" << endl;
            cout << "                   是否继续存款？" << endl;
            cout << "                     1. 继续存款" << endl << endl;
            cout << "                   2. 返回主界面" << endl << endl;
            cout << "                输入对应数字选择功能" << endl;
            cin >> select;
            if (select == "1")
            {
                system("cls");
                continue;
            }
            else break;
        }
    }
    changemoney(fp, users + 3, money);
    system("cls");
    surface();
}

//取款
void ATM::gain(string fp)
{
    int tempmoney=0;
    string select;
    int tempsum = 0;
    while (true)
    {  
        cout << "*************************************************" << endl << endl;
        cout << "                 本机仅能取出100元纸币" << endl;
        cout << "                   单次最多取出5000元" << endl;
        cout << "                 当前余额： " << money << "元" << endl;
        cout << "             今日已取款数目： " <<tempsum<<"元"<< endl;
        cout << "               每日取款限额为20000元" << endl;
        cout << "*************************************************" << endl << endl;
      cout << "            请输入取款金额：" << endl;
        cin >> tempmoney;
        if (tempmoney % 100 != 0)
        {
            system("cls");
            cout << "       您输入的金额必须是100的整数倍！" << endl;
            cout << "                 请重新输入！" << endl;
            continue;
        }
        else if (tempmoney>money)
        {
            system("cls");
            cout << "             您的账户余额不足" << endl;
            cout << "                 请重新输入！" << endl;
            continue;
        }
        else if (tempmoney > 5000)
        {
            system("cls");
            cout << "       您输入的金额不能大于5000！" << endl;
            cout << "                 请重新输入！" << endl;
            continue;
        }
        else if (tempsum + tempmoney > 20000)
        {
            system("cls");
            cout << "       您今日取款金额达到上限！" << endl;
            cout << "                1. 输入其他金额" << endl << endl;
            cout << "                 2. 返回主界面" << endl << endl;
            cout << "          输入对应数字选择功能" << endl;
            cin >> select;
            if (select == "1")
            {
                system("cls");
                continue;
            }
            else
                break;
        }
        else
        {
            tempsum = tempsum + tempmoney;
            money = money - tempmoney;
            cout << "                      取款成功！" << endl;
            cout << "                   是否继续取款？" << endl;
            cout << "                     1. 继续取款" << endl << endl;
            cout << "                   2. 返回主界面" << endl << endl;
            cout << "                输入对应数字选择功能" << endl;
            cin >> select;
            if (select == "1")
            {
                system("cls");
                continue;
            }
            else break;
        }
    }
    changemoney(fp, users + 3, money);
    system("cls");
    surface();
}

//转账
void ATM::trans(string fp)
{
    int tempmoney = 0;
    int transmoney;
    string tran;
    int select;
    while (true)
    {
        cout << "*************************************************" << endl << endl;
        cout << "                 当前余额： " << money << "元" << endl;
        cout << "*************************************************" << endl << endl;
        while (true)
        {
            cout << "          请输入转账人的账号：";
            cin >> tran;
            if (tran == name)
            {
                cout << "               不能给自己转账！" << endl;
                continue;
            }
            if (isrepeat(fp, "name: ", tran) == false)
            {
                cout << "               该转账人不存在！" << endl << "请重新输入！" << endl;
            }
            else break;
        }
        cout << "          请输入转账金额：" ;
        cin >> tempmoney;
        if (money < tempmoney)
        {
            system("cls");
            cout << "              余额不足" << endl;
            cout << "             请重新输入！" << endl;
            continue;
        }
        else
        {
            cout << "              转账成功！" << endl;
            cout << "           5秒后将返回到主界面" << endl;
            Sleep(5000);
            system("cls");
            break;
        }
    }
    money = money - tempmoney;
    changemoney(fp, users + 3, money);
    changemoney(fp, getstrline(fp, "name: ", tran) + 3, gettransmoney(fp, getstrline(fp, "name: ", tran))+tempmoney);
    surface();
}

//获取指定字符串所在文本行数
int ATM::getstrline(string fp, string type, string contain)
{
    int i;
    fstream file;
    file.open(fp, ios::in);
    string temp;
    contain = type + contain;
    for (i = 1; !file.eof(); i++)
    {
        getline(file, temp);
        if (contain == temp)
        {
            file.close();
            return i;
        }
    }
    file.close();
        return 0;
}

//获取指定行数的字符串
string ATM::getstr(string fp,int i)
{
    fstream file;
    string temp;
    file.open(fp, ios::in);
    for (int j = 1; j <= i; j++)
    {
        getline(file, temp);
    }
    file.close();
    return temp;
}

//获取余额
int ATM::getmoney(string fp)
{
    fstream file;
    string temp;
    file.open(fp, ios::in);
    for (int j = 1; j <= users+2; j++)
    {
        getline(file, temp);
    }
    file >> money;
    file.close();
    return money;
}

//获取转账人余额
int ATM::gettransmoney(string fp,int x)
{
    int m;
    fstream file;
    string temp;
    file.open(fp, ios::in);
    for (int j = 1; j <= x + 2; j++)
    {
        getline(file, temp);
    }
    file >> m;
    file.close();
    return m;
}

//登录系统
void ATM::login(string fp)
{
    ofstream nofile;
    nofile.open("user.txt", ios::app);
    nofile.close();
    //防止空文件
    int zh;
    cout << "          请输入您的账号:" << endl;
    fstream file;
    file.open(fp, ios::in);
        string tempname;
        while (true)
        {
        cin >> tempname;
          if (isrepeat(fp, "name: ", tempname) == true)
          {
              zh = getstrline(fp, "name: ", tempname);
              users = zh;
              name = tempname;
            break;
          }
          else
          {
              cout << "           您输入的账号不存在！请重新输入"<<endl;
          }
        }
        cout << "          请输入您的密码："<<endl;
            string temppassword,temp;
            temp = getstr(fp, users + 1);
            while (true)
            {
                cin >> temppassword;
                password = temppassword;
                temppassword = "password: " + temppassword;
                if (temp == temppassword)
                    break;
                else cout << "            您的密码不正确，请重新输入！" << endl;
            }
            cout << "         登录成功！" << endl;
            id = getstr(fp, users + 2);
            money = getmoney(fp);
            cout << "           5秒后将转到主界面" << endl;
            Sleep(5000);
            system("cls");
            surface();
}

//判断用户名,转账人是否重复或存在
bool ATM::isrepeat(string fp, string type, string contain)
{
    int i;
    fstream file;
    file.open(fp, ios::in);
    string temp;
    contain = type + contain;
    while (!file.eof())
     {
        getline(file, temp);
        if (temp==contain)
            return true;
     }
    file.close();
    return false;
}

//注册系统
void ATM::regist(string fp)
{
    fstream file(fp, ios::app);
    bool repeat=0;
        cout << "      请输入您的账号：(不超过20位,仅支持数字和字母组合）" << endl;
        while (!repeat)
        {
            cin >> name;
            int flag = 0;
            for (int kk = 0; kk < name.size(); kk++)
            {
                if (name[kk] >= 48 && name[kk] <= 57 || name[kk] >= 65 && name[kk] <= 90 || name[kk] >= 97 && name[kk] <= 122)
                    continue;
                else
                {
                    flag = 1;
                    break;
                }
            }
            if (name.size() > 20)
            {
                cout << "       请输入小于20位的账号！" << endl;
                continue;
            }
            if (flag == 1)
            {
                cout << "         请不要输入除数字和字母之外的组合！" << endl;
                continue;
            }
            if (isrepeat(fp, "name: ", name) == false)
                repeat = 1;
            else cout << "        您输入的账号已被注册！请重新输入。" << endl;
        }
        repeat = 0;
         while (!repeat)
          {
                cout << "         请输入您的密码：（不超过20位，仅支持数字和字母组合）" << endl;
                cin >> password;
                 int flag = 0;
                for (int kk = 0; kk < password.size(); kk++)
                {
                    if (password[kk] >= 48 && password[kk] <= 57 || password[kk] >= 65 && password[kk] <= 90 || password[kk] >= 97 && password[kk] <= 122)
                        continue;
                    else
                    {
                        flag = 1;
                        break;
                    }
                }
                if (password.size() > 20)
                {
                    cout << "       请输入小于20位的密码！" << endl;
                    continue;
                }
                if (flag == 1)
                {
                    cout << "         请不要输入除数字和字母之外的组合！" << endl;
                    continue;
                }
                string confirm;
                cout << "         请重新输入您设定的密码。" << endl;
                cin >> confirm;
                if (confirm == password)
                    repeat = 1;
                else cout << "您两次输入的密码不一致，请重新设定！" << endl;
          }
         repeat = 0;
         while (!repeat)
         {
             cout << "         请输入您的身份证号：" << endl;
             cin >> id;
             int flag = 0;
             if (id.size()!=18)
             {
                 cout << "       请输入正确的身份证号！" << endl;
                 continue;
             }
             string confirm;
             cout << "         请重新输入您设定身份证号。" << endl;
             cin >> confirm;
             if (confirm == id)
                 repeat = 1;
             else cout << "您两次输入的身份证号不一致，请重新设定！" << endl;
         }
         file << "name: " << name << endl;
         file << "password: " << password << endl;
         file << "id: " << id << endl;
         file <<  "0" << endl;
         file.close();
         cout << "        开卡成功！是否跳转至登录？(输入1跳转，其他字符回到主界面）" << endl;
         string k;
             cin >> k;
             system("cls");
             if (k == "1")
                 login(fp);
             else welcome();
}

//功能界面
void ATM::surface()
{
    cout << "*************************************************" << endl<<endl;
    cout << "                用户： " << name << "  " << endl << endl;
    cout << "                欢迎使用ATM机模拟系统                     " << endl << endl;
    cout << "                        1. 存款" << endl << endl;
    cout << "                        2. 取款" << endl << endl;
    cout << "                        3. 转账" << endl << endl;
    cout << "                      4. 查询当前余额" << endl << endl;
    cout << "                        5. 退卡" << endl << endl;
    cout << "                       6. 修改密码" << endl << endl;
    cout << "                输入对应数字选择功能" << endl;
    cout << "*****************************************************" << endl;
    string t1;
    while (true)
    {
        cin >> t1;
        if (t1 == "1")
        {
            system("cls");
            save("user.txt");
            break;
        }
        else if (t1 == "2")
        {
            system("cls");
            gain("user.txt");
            break;
        }
        else if (t1 == "3")
        {
            system("cls");
            trans("user.txt");
        }
        else if (t1 == "4")
        {
            system("cls");
            inquiry();
        }
        else if (t1 == "5")
        {
            system("cls");
            goodbye();
        }
        else if(t1=="6")
        {
            system("cls");
            reset("user.txt");
        }
        else cout << "                   请输入有效数字！" << endl;
    }
}

//查询余额系统
void ATM::inquiry()
{

    string select;
    cout << "*************************************************" << endl << endl;
    cout << "                用户： " << name << "  " << endl << endl;
    cout << "           当前余额为：" << money << endl << endl;
    cout << "                   1. 返回主界面" << endl << endl;
    cout << "                输入对应数字选择功能" << endl;
    cout << "*************************************************" << endl << endl;
    while (true)
    {
        cin >> select;
        if (select == "1")
        {
            system("cls");
            break;
        }
        else cout << "             请输入有效数字！" << endl;
    }
    surface();
}

//欢迎界面
void ATM::welcome()
{
    cout << "*****************************************************" << endl;
    cout << "                欢迎使用ATM机模拟系统                     " << endl << endl;
    cout << "                        1. 登录" << endl << endl;
    cout << "                        2. 开卡" << endl << endl;
    cout << "                输入对应数字选择功能" << endl;
    cout << "*****************************************************" << endl;
    string t1;
    while (true)
    {
        cin >> t1;
        if (t1 == "1")
        {
            system("cls");  
            login("user.txt");
            break;
        }
        else if (t1 == "2")
        {
             system("cls");
           regist("user.txt");
            break;
        }
        else cout << "                        请输入有效数字！" << endl;
    }
}

//结束界面
void ATM::goodbye()
{
    system("cls");
    cout << "*************************************************" << endl << endl;
    cout << "                   感谢您使用ATM模拟系统。"<< endl << endl;
    cout << "                            再见！" << endl << endl;
    cout << "*****************************************************" << endl;
    exit(0);
}

//重置密码
void ATM::reset(string fp)
{
    string temp,temp2;
    cout << "*************************************************"  << endl;
    while (true)
    {
        cout << "            请输入旧密码：";
        cin >> temp;
        if (password != temp)
        {
            cout << "        您输入的密码与原密码不一致"  << endl;
            cout << "                请重新输入！"  << endl;
        }
        else break;
    }
    cout << "            请输入新密码：";
    while (true)
    {
        cin >> temp;
        cout << "            请确认刚才输入密码：";
        cin >> temp2;
        if (temp2 != temp)
        {
            cout << "        您两次输入的密码不一致" << endl;
            cout << "                请重新输入！"  << endl;
        }
        else break;
    }
    changepassword(fp, users + 1, temp2);
    cout << "              密码修改成功！" << endl;
    cout << "           5秒后将返回到主界面" << endl;
    Sleep(5000);
    system("cls");
    surface();
}
int main()
{
    ATM A;
    A.welcome();
}