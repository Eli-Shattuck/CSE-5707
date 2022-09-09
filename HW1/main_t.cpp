#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <cmath>
#include <thread>
#include <set>

typedef struct Data {
    int w;
    int v;
    float r;
    int index;
    Data(int _w, int _v, float _r, int _index) { w=_w; v=_v; r=_r; index=_index;};
} Data;

typedef struct Node {
    int w; // weight
    int v; // value
    int c; // index in data
    int ub; // upper bound
    unsigned long int* taken; // uses the bits stored to keep track of the taken items
    Node(int _w, int _v, int _c, int _ub, int sz) { w = _w; v = _v; c = _c; ub = _ub; taken = new unsigned long int[sz]; for (int i = 0; i < sz; i++) {taken[i] = 0;}};
    ~Node() {
        delete [] taken;
    }
    void copyTaken(Node* n, int sz) {
        for (int i = 0; i < sz; i++) {
            taken[i] = n->taken[i];
        }
    }
} Node;

typedef struct ThreadData {
    Node* take;
    Node* leave;
    int lb;
    unsigned long int* taken;
    ThreadData(Node* _t, Node* _l, int _lb) { take=_t; leave=_l; lb=_lb; taken=nullptr;};
} ThreadData;

int lb = 0;
unsigned long int * takenItems;

float greedy(Data* data, int n, int cap, int c) {
    float sum = 0;
    for (int i = c; (i < n) && cap > 0; i++) {
        int w = data[i].w;
        if (w > cap) {
            sum += (float)cap/w * data[i].v;
            break;
        }
        else {
            sum += (float)data[i].v;
            cap -= w;
        }
    }

    return sum;
}

int sz;

void help(int cap, int n, Data* data, Node* curr, ThreadData** ret) {
    ThreadData* td = new ThreadData(nullptr, nullptr, lb);
    td->taken = curr->taken;

    //if(curr->w > cap) continue;
        if(curr->v > td->lb) {
            td->lb = curr->v;
            // for (int i = 0; i < sz; i++) {
            //     takenItems[i] = curr->taken[i];
            // }
            //td->taken = curr->taken;
        }
        if(curr->c >= n) {
            *ret = td;
            return;
        }

        float ub_leave = curr->v + greedy(data, n, cap - curr->w, curr->c+1);
        float ub_take  = curr->v + data[curr->c].v + greedy(data, n, cap - curr->w - data[curr->c].w, curr->c+1);
        
        //if(ub_leave == lb || ub_take == lb) return lb;
        // copies the taken items
        Node* leftNode = new Node(curr->w, curr->v, curr->c+1, ub_leave, sz);
        leftNode->copyTaken(curr, sz);

        if(ub_leave > td->lb && curr->w < cap) {
            td->leave = leftNode;
        } else if(curr->w == cap && curr->v > td->lb) {
            td->lb = curr->v;
            // for (int i = 0; i < sz; i++) {
            //     takenItems[i] = leftNode->taken[i];
            // }
            td->taken = leftNode->taken;
        }

        int tmpW = curr->w + data[curr->c].w;
        int tmpV = curr->v + data[curr->c].v;

        // copies the taken items and sets the most recent item to taken
        Node* takeNode = new Node(tmpW, tmpV, curr->c+1, ub_take, sz);
        takeNode->copyTaken(curr, sz);
        int index = curr->c % 64;
        int tIndex = curr->c / 64;
        takeNode->taken[tIndex] = takeNode->taken[tIndex] | (unsigned long int)1 << index;

        if(ub_take > td->lb && tmpW < cap) {
            td->take = takeNode;
        }  else if(tmpW == cap && tmpV > td->lb) {
            td->lb = tmpV;
            // for (int i = 0; i < sz; i++) {
            //     takenItems[i] = takeNode->taken[i];
            // }
            td->taken = takeNode->taken;
        }

        *ret = td;
        //printf("%p -> %d\n", (*ret)->take, (*ret)->take->c);
}

const int THREAD_COUNT = 8;

int solve(int cap, int n, Data* data) {
    auto cmp = [](Node* a, Node* b) { return a->ub > b->ub; };
    std::set<Node*, decltype(cmp)> queue(cmp);

    float ub = greedy(data, n, cap, 0);
    queue.insert(
        new Node(0, 0, 0, ub, sz)
    );

    std::thread workers[THREAD_COUNT];
    ThreadData* tds[THREAD_COUNT];

    while(!queue.empty()) {
        int activeWorkers = 0;
        for(int i = 0; i < THREAD_COUNT && !queue.empty(); i++) {
            activeWorkers++;
            auto ch = queue.extract(queue.begin());
            Node* curr = ch.value();
            //printf("%d\n", curr->ub);
            workers[i] = std::thread(help, cap, n, data, curr, &tds[i]);
        }
        //printf("\n");
        //tds[0] = new ThreadData(nullptr, nullptr, 0);
        //printf("%d\n", activeWorkers);
        for (int i = 0; i < activeWorkers; i++) {
            workers[i].join();
            //printf("%p\n", tds[i]->leave);
            if(tds[i]->leave) queue.insert(tds[i]->leave);
            //printf("%p\n", tds[i]->take);
            if(tds[i]->take ) queue.insert(tds[i]->take );

            //printf("here\n");
            if(tds[i]->lb > lb) {
                lb = tds[i]->lb;
                for (int j = 0; j < sz; j++) {
                    takenItems[j] = tds[i]->taken[j];
                }
            }
        }
        //printf("=====\nrestart queue\n=====\n");
    }

    return lb;

}

int cmp(const void* a, const void* b) { 
    float r1 = ((Data*)b)->r;
    float r2 = ((Data*)a)->r;

    if(r1 > r2) return  1;
    if(r2 > r1) return -1;
    return 0;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("Usage: knap [fileName]\n");
        return 0;
    }

    FILE* fp;
    char ch;
    fp = fopen(argv[1], "r");
 
    int n;
    fscanf(fp, "%d\n", &n);

    sz = ceil((double)n / 64);
    takenItems = new unsigned long int[sz];
    
    Data* data = (Data*)malloc(sizeof(Data) * n); 

    int w,v, index;
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%d %d %d \n", &index, &v, &w);
        data[i] = Data(w, v, v / (float)w, index);
        //printf("%d %d\n", v, w);
    }

    int cap;
    fscanf(fp, "%d", &cap);     
 
    // Closing the file
    fclose(fp);

    //for (int i = 0; i < n; i++) printf("(%d, %d, %.2f)\n", data[i].v, data[i].w, data[i].r);
    qsort(data, n, sizeof(Data), cmp);
    //printf("\n");
    //for (int i = 0; i < n; i++) printf("(%d, %d, %.2f)\n", data[i].v, data[i].w, data[i].r);


    //int best = solve_r(cap, n, data, 0, 0, 0);
    int best = solve(cap, n, data);

    for (int i = 0; i < n; i++) {
        int mod = i % 64;
        int div = i / 64;
        unsigned long int val = (takenItems[div] >> mod) & 1;
        if (val) {
            printf("Took item [%d %d %d]\n", data[i].index, data[i].v, data[i].w);
        }
    }

    printf("[%d]\n", best);

    delete [] takenItems;
    return 0;
}