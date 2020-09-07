#include <iostream>
#include <map>
#include <memory>

using namespace std;

/*
工厂模式（单列模式），解决过多的if else
*/

//基类
class RoleOperation
{

public:
    virtual string op() = 0;   //纯虚函数,核心进行多态的应用
    virtual ~RoleOperation(){}
};

//接下来针对不同的角色类，继承基类，并实现 Op 函数：

//管理者
class RootAdminRole : public RoleOperation
{
public:
    RootAdminRole(const string& RoleName): m_RoleName(RoleName){}

    string op()
    {
        return m_RoleName + " has A permission";
    }

private:
    string m_RoleName;

};

//订单管理者
class OrderAdminRole : public RoleOperation
{
public:
    OrderAdminRole(const string& RoleName) : m_RoleName(RoleName){}

    string op()
    {
        return m_RoleName + " has B permission";
    }

private:
    string m_RoleName;

};

//普通用户
class NormalRole : public RoleOperation
{
public:
    NormalRole(const string& RoleName) : m_RoleName(RoleName){}

    string op()
    {
        return m_RoleName + " has C permission";
    }

private:
    string m_RoleName;
};

//工厂接口
class RoleFactory
{
public:
    static RoleFactory& Instance()  //创建工厂模式，唯一单列
    {
        static RoleFactory instance;
        return instance;
    }

    //把指针对象注册到工厂
    void RegisterRole(const string& name, RoleOperation* registry)
    {
        m_RoleRegistry[name] = registry;
    }

    //根据名字找到对应的角色指针对象的
    RoleOperation* GetRole(const string& name)
    {
        map<string, RoleOperation*>::iterator it;

        it = m_RoleRegistry.find(name);

        if(it != m_RoleRegistry.end())
        {
            return it->second;
        }

        return NULL;
    }


private:
    //禁用拷贝和复制操作
    RoleFactory(const RoleFactory&);
    const RoleFactory& operator=(const RoleFactory&);

    RoleFactory(){};  //禁止外部创建对象
    ~RoleFactory(){};

//创建 map 容器用于存储数据;保存注册过的角色，key:角色名称 , value:角色指针对象
    map<string, RoleOperation*> m_RoleRegistry;
};


//初始化函数(初始角色到工厂)
void InitializeRole()
{
    static bool bInitialize = false;

    if(!bInitialize)
    {
        //注册管理者到工厂
        RoleFactory::Instance().RegisterRole("ROLE_ROOT_ADMIN", new RootAdminRole("ROLE_ROOT_ADMIN"));

        //注册订单管理者到工厂
        RoleFactory::Instance().RegisterRole("ROLE_ORDER_ADMIN", new OrderAdminRole("ROLE_ORDER_ADMIN"));

        //注册普通用户到工厂
        RoleFactory::Instance().RegisterRole("ROLE_NORMAL", new NormalRole("ROLE_NORMAL"));

        bInitialize = true;
    }

}

class JudgeRole
{
public:
    JudgeRole()
    {
        InitializeRole();

    }

    string Judge(const string& RoleName)
    {
        RoleOperation* factory = RoleFactory::Instance().GetRole(RoleName);
        if(factory)
        {
            RoleOperation* pRoleOperation = factory;
            //shared_ptr<RoleOperation> pRoleOperation(factory);  //C++ 11 智能指针用户释放内存

            delete pRoleOperation;

            return pRoleOperation->op();
        }

        string strErrorInfo = "NO product found for " + RoleName;

        return strErrorInfo;
    }
};



int main()
{

    JudgeRole judgeRole;

    cout << judgeRole.Judge("ROLE_ROOT_ADMIN") << endl;
    cout << judgeRole.Judge("ROLE_ORDER_ADMIN") << endl;
    cout << judgeRole.Judge("ROLE_NORMAL") << endl;
    cout << judgeRole.Judge("yudong") << endl;

    return 0;
}