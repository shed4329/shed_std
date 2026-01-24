#include "../Qqueue.h"
#include "../iostream.h"

int main(){
    shed_std::Qqueue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.pop();
    int* ptr = queue.data();

    shed_std::Cconsole_output << *ptr << shed_std::end_line;
    return 0;
}