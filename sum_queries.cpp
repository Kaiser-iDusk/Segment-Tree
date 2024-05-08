#include <bits/stdc++.h>
using namespace std;

class Node{
    public:
    int l, r, sum;
    
    Node(int l, int r, int sum){
        this->l = l;
        this->r = r;
        this->sum = sum;
    }
};
class SegmentTree{
private:
    int N, TOTAL, SIZE;
    vector<Node*> TREE;

    void build(vector<int>& nums, int s, int e, int idx){
        if(s == e){
            SIZE = max(SIZE, idx)+1;
            TREE[idx] = new Node(s, e, nums[s]);
            return;
        }
        int left_idx = 2*idx + 1;
        int right_idx = 2*idx + 2;

        int mid = s + (e-s)/2;

        build(nums, s, mid, left_idx);
        build(nums, mid+1, e, right_idx);

        int l_sum = TREE[left_idx]->sum, r_sum = TREE[right_idx]->sum;

        TREE[idx] = new Node(s, e, (l_sum + r_sum));
        return;
    }
    void DFS(int i){
        if(i >= SIZE || !TREE[i]) return;
        
        cout << "L: " << TREE[i]->l << "  R:" << TREE[i]->r << " || " << TREE[i]->sum << "\n";
        DFS(2*i+1);
        DFS(2*i+2);
        return;
    }
    void UPDATE(int idx, int i, int val){
        int l = TREE[idx]->l, r = TREE[idx]->r;
        if(l > i || r < i || i >= SIZE || !TREE[idx]) return;
        if(l == r && r == i){
            TREE[idx]->sum = val;
            return;
        }
        int l_idx = 2*idx+1, r_idx = 2*idx+2;
        int mid = l + (r-l)/2;
        if(i <= mid){
            UPDATE(l_idx, i, val);

            TREE[idx]->sum = TREE[l_idx]->sum + TREE[r_idx]->sum;
        }
        else{
            UPDATE(r_idx, i, val);

            TREE[idx]->sum = TREE[l_idx]->sum + TREE[r_idx]->sum;
        }
    }
    int QUERY(int l, int r, int idx){
        if(idx >= SIZE) return 0;
        int start = TREE[idx]->l, end = TREE[idx]->r;
        if(l>end || r<start) return 0;
        if(l<=start && end<=r) return TREE[idx]->sum;
        // int mid = start + (end-start)/2;
        int left = QUERY(l, r, 2*idx+1);
        int right = QUERY(l, r, 2*idx+2);
        return (left + right);
    }
public:
    SegmentTree(int n){
        N = n;
        TOTAL = SIZE = 0;
        vector<Node*> temp(4*n + 1, NULL);
        TREE = temp;
    }
    void buildTree(vector<int>& nums, int s, int e){
        build(nums, s, e, 0);
        TOTAL = TREE[0]->sum;
        return;
    }
    void printTree(){
        if(SIZE == 0) return;
        DFS(0);
    }
    void update(int i, int val){
        if(i >= N) {cout << "Error: Array Index out of Bounds.\n"; return;}

        UPDATE(0, i, val);
    }
    int query(int l, int r){
        if(l < 0 || r >= N) {cout << "Error: Array Index Out of Bounds.\n"; return -1;}
        int ans = QUERY(l, r, 0);
        return ans;
    }
};

int main(){
    vector<int> nums = {1, 4, 2, 6, 0, 3};
    SegmentTree TreeObj = SegmentTree(nums.size());
    TreeObj.buildTree(nums, 0, nums.size()-1);
    TreeObj.printTree();
    cout << "__________________UPDATE__________________\n";
    TreeObj.update(4, 4);
    TreeObj.printTree();
    cout << "__________________TEST__________________\n";
    cout << "Range Query in range: (0, 1) = " << TreeObj.query(0, 1) << "\n";
    return 0;
}