#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int global_size;
int num_pages=0;

class page
{
    public:
        page();
        int size;
        int r_capacity;
        vector <int> data;
        int count;
        int index;
        page* next;
        page* prev;
        virtual ~page();

};

page::page(){
    count = 0;
    next=nullptr;
    prev=nullptr;
    index = 0;
    size = global_size;
    r_capacity = global_size - 16;
}

page::~page(){

}

class heap_file{
    public:
        heap_file();
        page *head;
        void insert(int record_size,int record_data);
        void search(int search_data);
        void status();
        void init();
};

heap_file::heap_file(){
    head=new page;
}

void heap_file::insert(int record_size,int record_data){
    int actual_record_size = record_size + 4;
    page * pageptr = head;
    if(head->count==0){
        num_pages++;
        head->r_capacity = head->r_capacity - actual_record_size;
        head->index++;
        head->data.push_back(record_data);
        head->count++;
        head->prev=nullptr;
        head->next=nullptr;
    }
    else{
        while(pageptr->r_capacity < actual_record_size){
             if(pageptr!=nullptr){
                page* new_page = new page;
                new_page->count=0;
                new_page->size=head->size;
                new_page->r_capacity=new_page->size-16;
                new_page->index=0;
                num_pages++;
                pageptr->next=new_page;
                new_page->prev=pageptr;
             }
             pageptr=pageptr->next;
        }
        pageptr->r_capacity = pageptr->r_capacity - actual_record_size;
        pageptr->data.push_back(record_data);
        pageptr->count++;
        pageptr->index++;
    }
}

void heap_file::search(int search_data){
    page* pageptr = head;
    int h=-1;
    int dummy = -1;
    int success = 0;
    while(pageptr!=nullptr){
        h++;
        for(int i = 0;i<pageptr->data.size();i++){
           if(pageptr->data[i]==search_data){
                cout << h << " " << i << endl;
                success=1;
                break;
            }
        }
        if(success==1){
            break;
        }
        pageptr =  pageptr->next;
    }
    if(success!=1){
        cout <<dummy<<" "<<dummy<<endl;
    }
}

void heap_file::status(){
    cout<<num_pages<<" ";
    page* pageptr = head;
    if(num_pages!=0){
        while(pageptr!=nullptr){
            cout<<pageptr->count<<" ";
            pageptr = pageptr->next;
        }
    }
    cout << endl;
}



int main(){
    cin>>global_size;
    heap_file node;
    int temp;
    while(cin>>temp){
        if(temp==1){
            int r_size,r_data;
            cin>>r_size;
            cin>>r_data;
            node.insert(r_size,r_data);
        }
        else if(temp == 2){
            node.status();
        }
        else if(temp == 3){
            int s_data;
            cin>>s_data;
            node.search(s_data);
        }
        else if(temp == 4){
            break;
        }
    }
}
