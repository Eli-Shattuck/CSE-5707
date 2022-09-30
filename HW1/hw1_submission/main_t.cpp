#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <cmath>
#include <thread>
#include <set>

typedef struct Data {
    uint64_t w;
    uint64_t v;
    float r;
    uint64_t index;
    Data(uint64_t _w, uint64_t _v, float _r, uint64_t _index) { w=_w; v=_v; r=_r; index=_index;};
} Data;

typedef struct Node {
    uint64_t w; // weight
    uint64_t v; // value
    uint64_t c; // index in data
    uint64_t ub; // upper bound
    uint64_t* taken; // uses the bits stored to keep track of the taken items
    Node(uint64_t _w, uint64_t _v, uint64_t _c, uint64_t _ub, uint64_t sz) { w = _w; v = _v; c = _c; ub = _ub; taken = new uint64_t[sz]; for (size_t i = 0; i < sz; i++) {taken[i] = 0;}};
    ~Node() {
        delete [] taken;
    }
    void copyTaken(Node* n, uint64_t sz) {
        for (size_t i = 0; i < sz; i++) {
            taken[i] = n->taken[i];
        }
    }
} Node;

typedef struct ThreadData {
    Node* take;
    Node* leave;
    uint64_t lb;
    uint64_t* taken;
    ThreadData(Node* _t, Node* _l, uint64_t _lb) { take=_t; leave=_l; lb=_lb; taken=nullptr;};
} ThreadData;

uint64_t lb = 0ull;
uint64_t* takenItems;

float greedy(Data* data, uint64_t n, uint64_t cap, uint64_t c) {
    float sum = 0;
    for (size_t i = c; (i < n) && cap > 0; i++) {
        uint64_t w = data[i].w;
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

uint64_t sz;

void help(uint64_t cap, uint64_t n, Data* data, Node* curr, ThreadData** ret) {
    ThreadData* td = new ThreadData(nullptr, nullptr, lb);
    td->taken = curr->taken;

    //if(curr->w > cap) continue;
        if(curr->v > lb) {
            td->lb = curr->v;
            // for (size_t i = 0; i < sz; i++) {
            //     takenItems[i] = curr->taken[i];
            // }
            //td->taken = curr->taken;
        }

        if(curr->c >= n) {
            *ret = td;
            return;
        }

        float ub_leave = curr->v + greedy(data, n, cap - curr->w, curr->c+1ull);
        float ub_take  = curr->v + data[curr->c].v + greedy(data, n, cap - curr->w - data[curr->c].w, curr->c+1ull);
        
        //if(ub_leave == lb || ub_take == lb) return lb;
        // copies the taken items
        Node* leftNode = new Node(curr->w, curr->v, curr->c+1ull, ub_leave, sz);
        leftNode->copyTaken(curr, sz);

        if(ub_leave > std::max(lb, td->lb) && curr->w < cap) {
            td->leave = leftNode;
        } else if(curr->w == cap && curr->v > std::max(lb, td->lb)) {
            td->lb = curr->v;
            // for (size_t i = 0; i < sz; i++) {
            //     takenItems[i] = leftNode->taken[i];
            // }
            td->taken = leftNode->taken;
        }

        uint64_t tmpW = curr->w + data[curr->c].w;
        uint64_t tmpV = curr->v + data[curr->c].v;

        // copies the taken items and sets the most recent item to taken
        Node* takeNode = new Node(tmpW, tmpV, curr->c+1ull, ub_take, sz);
        takeNode->copyTaken(curr, sz);
        uint64_t index = data[curr->c].index % 64ull;
        uint64_t tIndex = data[curr->c].index / 64ull;
        takeNode->taken[tIndex] = takeNode->taken[tIndex] | 1ull << index;

        if(ub_take > std::max(lb, td->lb) && tmpW < cap) {
            td->take = takeNode;
        }  else if(tmpW == cap && tmpV > std::max(lb, td->lb)) {
            td->lb = tmpV;
            // for (size_t i = 0; i < sz; i++) {
            //     takenItems[i] = takeNode->taken[i];
            // }
            td->taken = takeNode->taken;
        }

        *ret = td;
        //printf("%p -> %llu\n", (*ret)->take, (*ret)->take->c);
}

const uint64_t THREAD_COUNT = 1ull;
uint64_t insertCount = 1;

uint64_t solve(uint64_t cap, uint64_t n, Data* data) {
    auto cmp = [](Node* a, Node* b) { return a->ub > b->ub; };
    std::set<Node*, decltype(cmp)> queue(cmp);

    float ub = greedy(data, n, cap, 0ull);
    queue.insert(
        new Node(0ull, 0ull, 0ull, ub, sz)
    );

    std::thread workers[THREAD_COUNT];
    ThreadData* tds[THREAD_COUNT];

    while(!queue.empty()) {
        uint64_t activeWorkers = 0ull;
        for(size_t i = 0; i < THREAD_COUNT && !queue.empty(); i++) {
            activeWorkers++;
            auto ch = queue.extract(queue.begin());
            Node* curr = ch.value();
            //printf("%llu\n", curr->ub);
            workers[i] = std::thread(help, cap, n, data, curr, &tds[i]);
        }
        //printf("\n");
        //tds[0] = new ThreadData(nullptr, nullptr, 0);
        //printf("%llu\n", activeWorkers);
        for (size_t i = 0; i < activeWorkers; i++) {
            workers[i].join();
            //printf("%p\n", tds[i]->leave);
            if(tds[i]->leave) {
                queue.insert(tds[i]->leave);
                insertCount++;
            }
            //printf("%p\n", tds[i]->take);
            if(tds[i]->take ) {
                queue.insert(tds[i]->take );
                insertCount++;
            }

            //printf("here\n"
            if(tds[i]->lb > lb) {
                lb = tds[i]->lb;
                for (size_t j = 0; j < sz; j++) {
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

int cmp2(const void* a, const void* b) { 
    return ((Data*)a)->index - ((Data*)b)->index;
}

uint64_t numSlots(uint64_t n) {
    //printf("%u\n", n/64ull);
    if (n % 64ull == 0ull) {
        return n / 64ull;
    }
    else {
        return n/64ull + 1;
    }
}

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("Usage: knap [fileName]\n");
        return 0;
    }

    FILE* fp;
    char ch;
    fp = fopen(argv[1], "r");
 
    uint64_t n;
    fscanf(fp, "%llu\n", &n);

    sz = numSlots(n);
    //printf("n: %u, sz: %u\n", n, sz);
    takenItems = new uint64_t[sz];

    Data* data = (Data*)malloc(sizeof(Data) * n); 

    uint64_t w,v, index;
    int off = 0;
    for (size_t i = 0ull; i < n; i++) {
        fscanf(fp, "%llu %llu %llu \n", &index, &v, &w);
        if(i == 0) off = index;
        data[i] = Data(w, v, v / (float)w, index - off);
        //printf("%llu %llu\n", v, w);
    }

    uint64_t cap;
    fscanf(fp, "%llu", &cap);  

    //printf("cap: %llu\n", cap);   
 
    // Closing the file
    fclose(fp);

    //for (size_t i = 0; i < n; i++) printf("(%llu, %llu, %.2f)\n", data[i].v, data[i].w, data[i].r);
    qsort(data, n, sizeof(Data), cmp);
    //printf("\n");
    //for (size_t i = 0; i < n; i++) printf("(%llu, %llu, %.2f)\n", data[i].v, data[i].w, data[i].r);


    //uint64_t best = solve_r(cap, n, data, 0, 0, 0);
    uint64_t best = solve(cap, n, data);

    qsort(data, n, sizeof(Data), cmp2);

    for (size_t i = 0ull; i < n; i++) {
        uint64_t mod = i % 64ull;
        uint64_t div = i / 64ull;
        uint64_t val = (takenItems[div] >> mod) & 1;
        if (val) {
            printf("Took item [%llu %llu %llu]\n", data[i].index, data[i].v, data[i].w);
        }
    }

    printf("[%llu]\n", best);
    //printf("%llu inserts\n", insertCount);

    delete [] takenItems;
    return 0;
}