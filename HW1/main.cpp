#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <cmath>

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

int lb = 0;
unsigned long int * takenItems;
int solve_r(int cap, int n, Data* data, int currW, int currV, int currC) {
    if(currW > cap) return 0;
    if(currC == n) return currV;

    int leave = solve_r(cap, n, data, currW, currV, currC+1);
    int take = solve_r(cap, n, data, currW + data[currC].w, currV + data[currC].v, currC+1);

    return take > leave ? take : leave;
}

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

int solve(int cap, int n, Data* data) {
    auto cmp = [](Node* a, Node* b) { return a->ub < b->ub; };
    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> queue(cmp);

    const int sz = ceil((double)n / 64);

    float ub = greedy(data, n, cap, 0);
    queue.push(
        new Node(0, 0, 0, ub, sz)
    );

    while(!queue.empty()) {
        Node* curr = queue.top();
        queue.pop();

        //if(curr->w > cap) continue;
        if(curr->v > lb) {
            lb = curr->v;
            for (int i = 0; i < sz; i++) {
                takenItems[i] = curr->taken[i];
            }
        }
        if(curr->c >= n) continue;

        float ub_leave = curr->v + greedy(data, n, cap - curr->w, curr->c+1);
        float ub_take  = curr->v + data[curr->c].v + greedy(data, n, cap - curr->w - data[curr->c].w, curr->c+1);
        
        //if(ub_leave == lb || ub_take == lb) return lb;
        // copies the taken items
        Node* leftNode = new Node(curr->w, curr->v, curr->c+1, ub_leave, sz);
        leftNode->copyTaken(curr, sz);

        if(ub_leave > lb && curr->w < cap) {
            queue.push(
                leftNode
            );
        } else if(curr->w == cap && curr->v > lb) {
            lb = curr->v;
            for (int i = 0; i < sz; i++) {
                takenItems[i] = leftNode->taken[i];
            }
        }

        int tmpW = curr->w + data[curr->c].w;
        int tmpV = curr->v + data[curr->c].v;

        // copies the taken items and sets the most recent item to taken
        Node* takeNode = new Node(tmpW, tmpV, curr->c+1, ub_take, sz);
        takeNode->copyTaken(curr, sz);
        int index = curr->c % 64;
        int tIndex = curr->c / 64;
        takeNode->taken[tIndex] = takeNode->taken[tIndex] | (unsigned long int)1 << index;

        if(ub_take > lb && tmpW < cap) {
            queue.push(
                takeNode
            );
        }  else if(tmpW == cap && tmpV > lb) {
            lb = tmpV;
            for (int i = 0; i < sz; i++) {
                takenItems[i] = takeNode->taken[i];
            }
        }
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


    const int sz = ceil((double)n / 64);
    takenItems = new unsigned long int[sz];

    //int best = solve_r(cap, n, data, 0, 0, 0);
    int best = solve(cap, n, data);
    printf("[%d]\n", best);

    for (int i = 0; i < n; i++) {
        int mod = i % 64;
        int div = i / 64;
        unsigned long int val = (takenItems[div] >> mod) & 1;
        if (val) {
            printf("Took item [%d %d %d]\n", data[i].index, data[i].v, data[i].w);
        }
    }

    delete [] takenItems;
    return 0;
}