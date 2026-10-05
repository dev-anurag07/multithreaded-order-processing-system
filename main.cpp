#include<iostream>
#include<mutex>
#include<queue>
#include<thread>
#include<condition_variable>

using namespace std;

struct Order{
    int orderid;
    string customername;
    float amount;
};

class TaskQueue{
    
  private:
  
  queue<Order>orders;
  mutex m;
  condition_variable cv;
  bool stopped = false;


public:

void push(Order order){
    {
    lock_guard<mutex>lock(m);
    
    orders.push(order);
    }
    
    cv.notify_one();
}

bool pop(Order &order){
    
    
        unique_lock<mutex>lock(m);
        
        
        cv.wait(lock, [this] {
            return stopped || !orders.empty();
        });

        if (stopped && orders.empty()) {
            return false;
        }
        
        order=orders.front();
        orders.pop();
    
    return true;
}

void stop(){
    {
    lock_guard<mutex>lock(m);
    
    stopped = true;
    }
    
    cv.notify_all();
}


};

void worker(TaskQueue &q){
    while(true){
        
        Order order;
        
        bool success = q.pop(order);
        
        if(!success){
            break;
        }
        
        else{
            cout << "Processing Order: "
             << order.orderid
             << " | Customer: "
             << order.customername
             << " | Amount: "
             << order.amount
             << endl;
        }
    }
}
    
 void producer(TaskQueue &q){
        
    q.push({101, "Anurag", 499.50});
    q.push({102, "Rahul", 799.00});
    q.push({103, "Aman", 299.00});
    q.push({104, "Ravi", 999.00});

    q.stop();
    
    }

int main(){
    
    TaskQueue q;
    
    thread w1(worker,ref(q));
    thread w2(worker,ref(q));
    thread p(producer, ref(q));
    
    w1.join();
    w2.join();
    p.join();
    
    return 0;
}
