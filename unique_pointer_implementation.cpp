#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Logger
{
    string log_val;
    size_t log_id;

    public:
    Logger(){}
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
class UnqPtr
{
    T* m_ptr;
    public:
    UnqPtr()
    {
        m_ptr = nullptr;
    }

    UnqPtr(T* ptr)
    {
        m_ptr = ptr;
    }

    UnqPtr(const UnqPtr& u_ptr) = delete;
    UnqPtr& operator=(const UnqPtr& u_ptr) = delete;

    UnqPtr(UnqPtr&& u_ptr)
    {
        cout<<"Move Constructor Called"<<endl;
        this->m_ptr = u_ptr.m_ptr;
        u_ptr.m_ptr = nullptr;
    }

    UnqPtr& operator=(UnqPtr&& u_ptr)
    {
        cout<<"Move Assignment Called"<<endl;
        if(&u_ptr == this)
            return *this;

        if(this->m_ptr)
            delete this->m_ptr;
        
        this->m_ptr = u_ptr.m_ptr;
        u_ptr.m_ptr = nullptr;

        return *this;
    }

    T& operator*()
    {
        return *this;
    }

    T* operator->()
    {
        return this;
    }

    operator bool() const
    {
        return this->m_ptr != nullptr;
    }

    ~UnqPtr()
    {
        if(this->m_ptr)
        {
            delete this->m_ptr;
        }
            
    }
};

int main()
{
    UnqPtr<Logger> uptr1(new Logger(1001, "Log Start"));
    UnqPtr<Logger> uptr2;
    
    uptr2 = move(uptr1);
    if(uptr1)
        cout<<"Wrong"<<endl;

    auto uptr3(move(uptr2));

    if(uptr2)
        cout<<"Wrong"<<endl;

    return 0;
}
