#include <bits/stdc++.h>
using namespace std;

long long merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left;
    int j = mid + 1;
    int k = 0;
    long long inv = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv += (mid - i + 1);
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }
    for (int p = 0; p < k; p++) {
        arr[left + p] = temp[p];
    }

    return inv;
}
long long _mergeSort(vector<int>& arr, int left, int right) {
    long long inv = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        inv += _mergeSort(arr, left, mid);
        inv += _mergeSort(arr, mid + 1, right);
        inv += merge(arr, left, mid, right);
    }
    return inv;
}
long long countInversions(vector<int>& arr) {
    if (arr.empty()) return 0;
    return _mergeSort(arr, 0, arr.size() - 1);
}

void testCase() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<int>> blocks;
    int i = 0;
    while (i < n) {
        if (a[i] % 2 == 0) {
            vector<int> block;
            while (i < n && a[i] % 2 == 0) {
                block.push_back(a[i]);
                i++;
            }
            blocks.push_back(block);
        } else {
            i++;
        }
    }
    long long same_block_inv = 0;
    for (auto& block : blocks) {
        same_block_inv += countInversions(block);
    }
    vector<int> E;
    for (auto& block : blocks) {
        E.insert(E.end(), block.begin(), block.end());
    }
    long long total_inv = countInversions(E);
    long long result = total_inv - same_block_inv;
    cout << result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    testCase();
    cout << "\n";
    return 0;
}
