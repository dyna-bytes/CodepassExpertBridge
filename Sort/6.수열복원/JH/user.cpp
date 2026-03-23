// user.cpp
#define MAXN 100000

extern int orderCheck(int left, int right);
/**
 * 실제 값을 몰라도 대소관계만 비교할 수 있다면 정렬할 수 있다.
 * 학생 번호의 대소관계(=카드 번호) 를 모르더라도 학생 번호를 정렬할 수 있다.
 */

void mergeSort(int s, int e, int arr[]) {
	if (s + 1 >= e) return;

	int m = (s + e)/2;
	mergeSort(s, m, arr);
	mergeSort(m, e, arr);

	int l = s, r = m, k = 0;
	int buf[MAXN] = { 0, };

	for (; l < m && r < e; ) {
		if (orderCheck(arr[l], arr[r])) buf[k++] = arr[l++];
		else buf[k++] = arr[r++];
	}

	while (l < m) buf[k++] = arr[l++];
	while (r < e) buf[k++] = arr[r++];

	for (int i = 0; i < k; i++)
		arr[s + i] = buf[i];
}
void array_restore(int N, int result[]) {
	// implement here
	int students[MAXN] = { 0, };
	for (int i = 0; i < N; i++)
		students[i + 1] = i;

	mergeSort(1, N + 1, students);
	for (int card = 1; card <= N; card++)
		result[students[card]] = card;
}