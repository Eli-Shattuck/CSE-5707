package main

import (
	"bufio"
	"container/heap"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type Data struct {
	w int
	v int
	r float64
}

type Node struct {
	w     int     // weight
	v     int     // value
	c     int     // index in data
	ub    float64 // upper bound
	index int
}

type PriorityQueue []*Node

func (pq PriorityQueue) Len() int { return len(pq) }

func (pq PriorityQueue) Less(i, j int) bool {
	// We want Pop to give us the highest, not lowest, priority so we use greater than here.
	return pq[i].ub < pq[j].ub
}

func (pq PriorityQueue) Swap(i, j int) {
	pq[i], pq[j] = pq[j], pq[i]
	pq[i].index = i
	pq[j].index = j
}

func (pq *PriorityQueue) Push(x interface{}) {
	n := len(*pq)
	node := x.(*Node)
	node.index = n
	*pq = append(*pq, node)
}

func (pq *PriorityQueue) Pop() interface{} {
	old := *pq
	n := len(old)
	item := old[n-1]
	old[n-1] = nil  // avoid memory leak
	item.index = -1 // for safety
	*pq = old[0 : n-1]
	return item
}

var lb int = 0

func solve_r(cap int, n int, data []Data, currW int, currV int, currC int) int {
	if currW > cap {
		return 0
	}
	if currC == n {
		return currV
	}

	leave := solve_r(cap, n, data, currW, currV, currC+1)
	take := solve_r(cap, n, data, currW+data[currC].w, currV+data[currC].v, currC+1)

	if take > leave {
		return take
	}
	return leave
}

func greedy(data []Data, n int, cap int, c int) float64 {
	var sum float64 = 0
	for i := c; (i < n) && cap > 0; i++ {
		w := data[i].w
		if w > cap {
			sum += float64(cap) / float64(w) * float64(data[i].v)
			break
		} else {
			sum += float64(data[i].v)
			cap -= w
		}
	}

	return sum
}

func solve(cap int, n int, data []Data) int {
	queue := make(PriorityQueue, 0)

	heap.Init(&queue)

	ub := greedy(data, n, cap, 0)
	queue.Push(&Node{0, 0, 0, ub, -1})

	for len(queue) > 0 {
		curr := (queue.Pop()).(*Node)

		//if(curr.w > cap) continue;
		if curr.v > lb {
			lb = curr.v
		}
		if curr.c >= n {
			continue
		}

		ub_leave := float64(curr.v) + greedy(data, n, cap-curr.w, curr.c+1)
		ub_take := float64(curr.v) + float64(data[curr.c].v) + greedy(data, n, cap-curr.w-data[curr.c].w, curr.c+1)

		//if(ub_leave == lb || ub_take == lb) return lb;

		if ub_leave > float64(lb) && curr.w < cap {
			queue.Push(&Node{curr.w, curr.v, curr.c + 1, ub_leave, -1})
		} else if curr.w == cap && curr.v > lb {
			lb = curr.v
		}

		tmpW := curr.w + data[curr.c].w
		tmpV := curr.v + data[curr.c].v
		if ub_take > float64(lb) && tmpW < cap {
			queue.Push(&Node{tmpW, tmpV, curr.c + 1, ub_take, -1})
		} else if tmpW == cap && tmpV > lb {
			lb = tmpV
		}
	}

	return lb

}

func main() {
	if len(os.Args) != 2 {
		fmt.Println("Usage: knap [fileName]")
		return
	}

	f, err := os.Open(os.Args[1])

	if err != nil {
		fmt.Println(err.Error())
	}

	defer f.Close()

	scanner := bufio.NewScanner(f)

	scanner.Scan()
	n, _ := strconv.Atoi(scanner.Text())
	//fmt.Printf("n: %d\n", n)

	data := make([]Data, n)

	var w, v, d int

	for i := 0; i < n; i++ {
		scanner.Scan()
		fmt.Fscanf(strings.NewReader(scanner.Text()), "%d %d %d\n", &d, &v, &w)
		data[i] = Data{w, v, float64(v) / float64(w)}
		//fmt.Printf("(v: %d, w: %d, r: %f)\n", data[i].v, data[i].w, data[i].r)
	}

	scanner.Scan()
	cap, _ := strconv.Atoi(scanner.Text())
	//fmt.Printf("cap: %d\n", cap)

	if err := scanner.Err(); err != nil {
		fmt.Println(err.Error())
	}

	//best := solve_r(cap, n, data, 0, 0, 0)
	best := solve(cap, n, data)
	fmt.Printf("[%d]\n", best)
}
