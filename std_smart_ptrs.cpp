#include <iostream>
#include <memory>

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

int main()
{
    cout<<"\n\nStarting Execution:"<<endl;
    cout<<"-----------------------"<<endl;
    unique_ptr<Logger> ptr1(new Logger(1001, "Log Start"));
    auto ptr2 = move(ptr1);
    cout<<ptr2->get_log_id()<<endl;
    cout<<ptr2->get_log_val()<<endl;

    cout<<"-----------------------"<<endl;
    shared_ptr<Logger> ptr3(new Logger(1002, "Log2 Start"));
    auto ptr4(ptr3);

    cout<<ptr3->get_log_id()<<endl;
    cout<<ptr3->get_log_val()<<endl;

    cout<<ptr4->get_log_id()<<endl;
    cout<<ptr4->get_log_val()<<endl;

    cout<<"-----------------------"<<endl;
    auto ptr5 = make_shared<Logger>(1003, "Log3 Start");
    auto ptr6 = ptr5;

    cout<<ptr5->get_log_id()<<endl;
    cout<<ptr5->get_log_val()<<endl;

    cout<<ptr6->get_log_id()<<endl;
    cout<<ptr6->get_log_val()<<endl;

    cout<<"-----------------------"<<endl;
    
    return 0;
}