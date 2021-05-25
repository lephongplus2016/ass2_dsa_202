/**
 * Name: Le Hong Phong
 * id: 1813518
*/
#include "main.h"

// read thong qua put co lam thay doi gia tri
Data* Cache::read(int addr) { //ok
	for (int i = 0; i < p; i++)
        if (arr[i]->addr == addr)
            return arr[i]->data;
    return NULL;
}
//put ko the goi truc tiep, ma thong qua read
Elem* Cache::put(int addr, Data* cont) {

    if(p<15)
    {
	    arr[p++] = new Elem(addr,cont,true);
        this->avlRoot = insert(avlRoot,arr[p-1] );
        return NULL;
    }
    else {
        Elem *temp = arr[0];// xoa phan tu dau queue
        this->avlRoot = deleteNode(avlRoot,temp->addr );

        int last = p -1;
        for(int i=0;i< last;i++)
        {
            arr[i] = arr[i+1];
        }
        p--;
        arr[p++] = new Elem(addr,cont,true); // them phan tu moi vao cache
        this->avlRoot = insert(avlRoot,arr[p-1] );
        return temp;
    }
    
}

//cu chay write thi sync dat thanh false
//chi co write moi thay doi duoc gia tri cua addr da co trong caches
Elem* Cache::write(int addr, Data* cont) {
    bool found = false;
	for (int i = 0; i < p; i++)
        if (arr[i]->addr == addr) {
            //delete arr[i]->data;
            arr[i]->data = cont;
            arr[i]->sync = false;
            found = true;
            break;
        }
    if (!found) {      //neu chua co trong caches
        if(p<15)         // them ko xoa
        {
            arr[p++] = new Elem(addr,cont,false);
            this->avlRoot = insert(avlRoot,arr[p-1] );
            return NULL;
        }
        else {                 //them co xoa
            Elem *temp = arr[0];// xoa phan tu dau queue
            this->avlRoot = deleteNode(avlRoot,temp->addr );//delete theo key

            int last = p -1;
            for(int i=0;i< last;i++)
            {
                arr[i] = arr[i+1];
            }
            p--;
            arr[p++] = new Elem(addr,cont,false);
            this->avlRoot = insert(avlRoot,arr[p-1] );
            return temp;
        }
    }
    return NULL;
}
void Cache::print() {  //ok
	for (int i =0; i < p; i++)
       arr[i]->print();   
}
void Cache::preOrder() {

    preOrderAVL(avlRoot);
}
void Cache::inOrder() {

    inOrderAVL(avlRoot);
}
