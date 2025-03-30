#include <bits/stdc++.h>

using namespace std;
int main(){
    unique_ptr<int> p1(new int(20));
    unique_ptr<int> p2 = make_unique<int>(10);

    cout<<*p1<<endl;
    cout<<*p2<<endl;

    unique_ptr<int> p3 = move(p2);
    cout<<*p3<<endl;

    shared_ptr<int> sp1(new int(20));
    shared_ptr<int> sp2 = make_shared<int>(10);
    shared_ptr<int> sp3 = sp2;
    cout<<*sp1<<" "<<sp1.use_count()<<endl;
    sp3.reset();
    cout<<*sp2<<" "<<sp2.use_count()<<endl;

}