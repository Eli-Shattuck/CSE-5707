#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>

typedef struct Data {
    int w;
    int v;
    float r;

    Data(int _w, int _v, float _r) { w=_w; v=_v; r=_r; };
} Data;

typedef struct Node {
    int w; // weight
    int v; // value
    int c; // index in data
    int ub; // upper bound

    Node(int _w, int _v, int _c, int _ub) { w = _w; v = _v; c = _c; ub = _ub; };
} Node;

int lb = 0;
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

    float ub = greedy(data, n, cap, 0);
    queue.push(
        new Node(0, 0, 0, ub)
    );

    while(!queue.empty()) {
        Node* curr = queue.top();
        queue.pop();

        //if(curr->w > cap) continue;
        if(curr->v > lb) lb = curr->v;
        if(curr->c >= n) continue;

        float ub_leave = curr->v + greedy(data, n, cap - curr->w, curr->c+1);
        float ub_take  = curr->v + data[curr->c].v + greedy(data, n, cap - curr->w - data[curr->c].w, curr->c+1);
        
        //if(ub_leave == lb || ub_take == lb) return lb;

        if(ub_leave > lb && curr->w < cap) {
            queue.push(
                new Node(curr->w, curr->v, curr->c+1, ub_leave)
            );
        } else if(curr->w == cap && curr->v > lb) lb = curr->v;

        int tmpW = curr->w + data[curr->c].w;
        int tmpV = curr->v + data[curr->c].v;
        if(ub_take > lb && tmpW < cap) {
            queue.push(
                new Node(tmpW, tmpV, curr->c+1, ub_take)
            );
        }  else if(tmpW == cap && tmpV > lb) lb = tmpV;
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
    printf("Here\n");
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

    int w,v;
    for (int i = 0; i < n; i++) {
        fscanf(fp, "%*d %d %d \n", &v, &w);
        data[i] = Data(w, v, v / (float)w );
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
    printf("[%d]\n", best);

    return 0;
}