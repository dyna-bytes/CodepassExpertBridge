#include <iostream>
using namespace std;
#define FASTIO ios::sync_with_stdio(false), cin.tie(0);
#define endl '\n'

const int MAXN = 5e5 + 1;
struct priority_queue { // max heap
    int sz = 0;
    int arr[MAXN];

    void heapify_down() {
        int curr = 1;

        while (curr * 2 <= sz) {
            int left = curr * 2;
            int right = curr * 2 + 1;

            int larger_child = left;
            if (right <= sz && arr[right] > arr[left])
                larger_child = right;

            if (arr[curr] < arr[larger_child]) {
                swap(arr[curr], arr[larger_child]);
                curr = larger_child;
            } else {
                break;
            }
        }
    }

    void heapify_up() {
        int curr = sz;

        while (curr > 1) {
            int parent = curr / 2;
            // 부모 노드보다 현재 노드가 크면 스왑 (최대 힙)
            if (arr[parent] < arr[curr]) {
                swap(arr[parent], arr[curr]);
                curr = parent;
            } else {
                break;
            }
        }
    }

    int pop_heap() {
        int ret = arr[1];

        // 1. 마지막 노드의 값을 루트로 옮기고 사이즈 감소
        arr[1] = arr[sz--];

        // 2. 힙에 요소가 남아있다면 다운 힙프트 진행
        if (sz > 0)
            heapify_down();

        return ret;
    }

    void push_heap(int val) {
        // 1. 마지막 위치에 값을 삽입하고 사이즈 증가
        arr[++sz] = val;

        // 2. 방금 넣은 값을 위로 올리며 힙 속성 복구
        heapify_up();
    }
};

int main() {
    int N; scanf("%d", &N);
    priority_queue pq;
    for (int i = 0; i < N; i++) {
        int val; scanf("%d", &val);
        pq.push_heap(val);
    }

    for (int i = 1; i <= pq.sz; i++)
        printf("%d ", pq.arr[i]);
    printf("\n");

    int ans[MAXN];
    int k = 0;
    while (pq.sz > 0) {
        int val = pq.pop_heap();
        ans[k++] = val;
    }

    for (int i = k - 1; i >= 0; i--)
        printf("%d ", ans[i]);
    printf("\n");

    return 0;
}