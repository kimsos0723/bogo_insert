#include <iostream>
#include <random>
#include <vector>
#include <stack>
#include <ctime>
#include <random>
#include <cmath>

using std::endl;
using std::rand;
using std::cout;
using std::random_device;
using std::mt19937_64;

typedef std::vector<int> data_t;
typedef std::stack<int> stack_t;
typedef std::uniform_int_distribution<int> distribution_t;

// data_t data{3, 4, 9, 0, 1, 7, 6, 8, 2, 5};
// data_t data{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
data_t data{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
// data_t data{31, 32, 8, 46, 19, 30, 42, 22, 43, 20, 13, 5, 6, 15, 39, 27, 48, 24, 37, 12, 40, 1, 4, 45, 35, 16, 10, 23, 41, 49, 44, 28, 38, 3, 47, 17, 14, 34, 0, 25, 21, 33, 36, 2, 9, 26, 11, 7, 29, 18};
// data_t data{26, 41, 94, 53, 15, 61, 9, 78, 46, 80, 21, 4, 38, 25, 85, 60, 45, 1, 88, 16, 54, 70, 81, 47, 20, 3, 79, 43, 83, 64, 34, 56, 6, 30, 11, 31, 87, 22, 42, 39, 27, 77, 8, 67, 28, 12, 75, 33, 66, 59, 63, 72, 24, 68, 13, 89, 96, 76, 51, 95, 69, 99, 93, 98, 14, 86, 23, 17, 82, 50, 73, 52, 36, 92, 2, 57, 29, 19, 35, 48, 91, 0, 84, 55, 65, 49, 37, 18, 32, 97, 7, 62, 10, 40, 71, 5, 58, 90, 44, 74};
// data_t data{99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
stack_t anomal_stack;

const size_t base_point = data.size();

size_t sorted_rating(const data_t d) {
    size_t p = base_point;
    for(int i=1; i<d.size();i++) {
        if(d[i-1] > d[i]) p-= 1;
    }    
    printf("%ld/%ld\n", p, base_point);
    return p;
}

void add_anomal_stack(data_t& d) {    
    for(int i=1;i<d.size();i++) {
        if(d[i-1] > d[i]) {                              
            anomal_stack.push(d[i-1]);
            d.erase(d.begin()+i-1);
            i=0;
        }
    }    
}

void insert_sort(data_t& d) {    
    for(int i=0;i<d.size();i++) {        
        if(anomal_stack.size() == 0) break;
        auto v=anomal_stack.top();                
        if(v < d[i]) {
            d.insert(d.begin()+i, v);
            anomal_stack.pop();
            i=0;
        } else if (i==d.size()-1) {
            d.insert(d.begin()+d.size(), v);
            anomal_stack.pop();
            i=0;
        }    
    }    
}

distribution_t get_random_number() {
    random_device rd;
    mt19937_64 rnd(rd());          
    return distribution_t(0, data.size());
}

void bogo_sort(data_t& d) {
    int t = 0;
    for(int i=0;i<(int)log10(static_cast<double>(d.size()));i++){
        int l = get_random_number().a();
        int r = get_random_number().a();

        if(d[l] > d[r]) {
            t = d[l];
            d[l] = d[r];
            d[r] = t;            
        }        
    }
}

int main(int argc, char const *argv[]) {
    clock_t begin, mid, end;     
    
    
    // if(5>sorted_rating(data)) bogo_sort(data);
    begin = clock();

    add_anomal_stack(data);
    mid = clock();

    insert_sort(data);
    end = clock();

    for(int i=0;i<data.size();i++) printf("%d ",data[i]);
    puts("");
    cout<<"all time: "<<end-begin<< " ms" << endl;
    cout<<"sorting time: "<<end-mid<< " ms" << endl;         
    
    return 0;
}
