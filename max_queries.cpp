#include <bits/stdc++.h>
using namespace std;

class Node{
    public:
    int l, r, max;
    
    Node(int l, int r, int maxi){
        this->l = l;
        this->r = r;
        this->max = maxi;
    }
};
class SegmentTree{
private:
    int N, MAXIMUM, SIZE;
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

        int l_max = TREE[left_idx]->max, r_max = TREE[right_idx]->max;

        TREE[idx] = new Node(s, e, max(l_max, r_max));
        return;
    }
    void DFS(int i){
        if(i >= SIZE || !TREE[i]) return;
        
        cout << "L: " << TREE[i]->l << "  R:" << TREE[i]->r << " || " << TREE[i]->max << "\n";
        DFS(2*i+1);
        DFS(2*i+2);
        return;
    }
    void UPDATE(int idx, int i, int val){
        int l = TREE[idx]->l, r = TREE[idx]->r;
        if(l > i || r < i || i >= SIZE || !TREE[idx]) return;
        if(l == r && r == i){
            TREE[idx]->max = val;
            return;
        }
        int l_idx = 2*idx+1, r_idx = 2*idx+2;
        int mid = l + (r-l)/2;
        if(i <= mid){
            UPDATE(l_idx, i, val);

            TREE[idx]->max = max(TREE[l_idx]->max, TREE[r_idx]->max);
        }
        else{
            UPDATE(r_idx, i, val);

            TREE[idx]->max = max(TREE[l_idx]->max, TREE[r_idx]->max);
        }
    }
    int QUERY(int l, int r, int idx){
        if(idx >= SIZE) return 0;
        int start = TREE[idx]->l, end = TREE[idx]->r;
        if(l>end || r<start) return INT_MIN;
        if(l<=start && end<=r) return TREE[idx]->max;
        // int mid = start + (end-start)/2;
        int left = QUERY(l, r, 2*idx+1);
        int right = QUERY(l, r, 2*idx+2);
        return max(left, right);
    }
public:
    SegmentTree(int n){
        N = n;
        MAXIMUM = INT_MIN;
        SIZE = 0;
        vector<Node*> temp(4*n + 1, NULL);
        TREE = temp;
    }
    void buildTree(vector<int>& nums, int s, int e){
        build(nums, s, e, 0);
        MAXIMUM = TREE[0]->max;
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
    cout << "__________________UPDATE_________________\n";
    TreeObj.update(4, 10);
    TreeObj.printTree();
    cout << "__________________TEST__________________\n";
    cout << "Range Query in range: (1, 5) = " << TreeObj.query(1, 5) << "\n";
    return 0;
}