#include <iostream>

/*
主要用于二阶构造，防止半成品对象
*/

template <typename T>
class SecondOrder
{
public:
    ~SecondOrder()
    {
        delete m_pChar;
        m_pChar = NULL;

    }

    static SecondOrder<T>* instance()
    {
        SecondOrder<T>* ret = new SecondOrder<T>;

        if(!(ret && (ret->construct())))
        {
            delete ret;
            ret = NULL;
        }

        return ret;

    }

    void setValue(T fd, int val)
    {
        *m_pChar = fd;
        m_val = val;
        
    }

    void printValue()
    {
        std::cout << "m_pChar: " << *m_pChar << std::endl;
        std::cout << "m_val: " << m_val << std::endl;
    }


private:
    bool construct()    //二阶构造
    {
        m_pChar = new T;

        return (m_pChar != NULL);

    }

    SecondOrder()   //一阶构造
    {
        m_val = 0;

    }


private:
    int m_val;
    T* m_pChar;

};



int main()
{
    SecondOrder<char>* ps = SecondOrder<char>::instance();
    if(ps != NULL)
    {
        ps->setValue('6', 9);
        ps->printValue();

    }


    return 0;
}