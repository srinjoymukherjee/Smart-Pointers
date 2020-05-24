#include <iostream>
#include <memory> //for smart pointers
#include <string>

using namespace std;

class Logger
{
    string log_val;
    size_t log_id;

    public:
    Logger() = delete;
    Logger(size_t id, string val)
        : log_id(id), log_val(val)
    {
        cout<<"Logger Allocated"<<endl;
    }

    string get_log_val()
    {
        return log_val;
    }

    size_t get_log_id()
    {
        return log_id;
    }

    ~Logger()
    {
        cout<<"Logger deallocated"<<endl;
    }
};

template <class T>
class SharedPtr
{
    T* m_ptr;
    size_t* obj_count;

    public:
    SharedPtr()
    {
        m_ptr = new T;
        obj_count = new size_t;
        *obj_count = 1;
    }

    SharedPtr(T* ptr)
    {
        m_ptr = ptr;
        obj_count = new size_t;
        *obj_count = 1;
    }

    SharedPtr(const SharedPtr& sptr)
    {
        this->m_ptr = sptr.m_ptr;
        this->obj_count = sptr.obj_count;
        *obj_count = *obj_count + 1;
    }

    SharedPtr& operator=(const SharedPtr& sptr)
    {
        this->m_ptr = sptr.m_ptr;
        this->obj_count = sptr.obj_count;        
        *obj_count += 1;
        return *this;
    }

    // SharedPtr(SharedPtr&& sptr)
    // {
    //     cout<<"Inside Move Constructor"<<endl;
    //     this->m_ptr = sptr.m_ptr;
    //     sptr.m_ptr = nullptr;
    //     this->obj_count = sptr.obj_count;
    //     sptr.obj_count = 0;
    // }

    // SharedPtr& operator=(SharedPtr&& sptr)
    // {
    //     cout<<"Inside Move Assignment"<<endl;
    //     if(this->m_ptr)
    //         delete this->m_ptr;
        
    //     this->m_ptr = sptr.m_ptr;
    //     sptr.m_ptr = nullptr;

    //     if(this->obj_count)
    //         delete this->obj_count;

    //     this->obj_count = sptr.obj_count;
    //     sptr.obj_count = 0;
    // }

    T& operator*() const
    {
        return *m_ptr;
    }

    T* operator->() const
    {
        return m_ptr;
    }

    operator bool() const
    {
        return m_ptr != nullptr;
    }

    ~SharedPtr()
    {
        if(*obj_count == 1)
        {
            delete m_ptr;
            delete obj_count;   
        }

        *obj_count -= 1;
    }
};

int main()
{
    SharedPtr<Logger> ptr1(new Logger(1001, "Log OK"));
    SharedPtr<Logger> ptr2(ptr1);
    auto ptr3 = ptr1;

    return 0;
}