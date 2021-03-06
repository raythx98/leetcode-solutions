# leetcode-solutions

### Custom Comparators
#### • Useful Custom Comparators
sort in descending order:
```
greater<int> // opposite for priority queue
```
sort in ascending order:
```
less<int> // opposite for priority queue
```

#### • Defining Custom Comparators
for priority queue
```
class Compare {
public:
    bool operator() (pair<int, string> &pair1, pair<int, string> &pair2){
        if (pair1.first == pair2.first) return pair1.second > pair2.second; // smallest first
        return pair1.first < pair2.first; // largest first
    }
};
```
for sorting
```
struct Compare
{
    inline bool operator() (const pi& pair1, const pi& pair2)
    {
        if (pair1.first == pair2.first) return pair1.second < pair2.second; // smallest first
        return pair1.first < pair2.first; // largest first
    }
};
```
### Common Data Structures
- ###### Node definition
```
struct Node {
    int val;
    Node* next;

    Node(int val, Node* next){
        this->val = val;
        this->next = next;
    }
    
    bool operator <(const Node& node){
        return val < node.val;
    }
};
```
- ###### find_if
```
find_if(v.rbegin(), v.rend(),
    [](int i) { return i == 42; }
);
```
- ###### erase-remove idiom
```
v.erase(remove_if(v.begin(), v.end(),
    [&del_val](int& val)->bool{
        return del_val == val
    }
), v.end())
```
#### • Vector
- ###### initialize vector
```
vector<int> v(size, element);
vector<int, vector<int>> v(size_r, vector<int>(size_c, element));
```
- ###### access vector elements
```
v[idx]
v.front()
v.back()
```
- ###### insert val
```
v.push_back(val)
v.insert(v.begin(), offset)
```
- ###### whether val exists
```
// unsorted vector
find(v.begin(), v.end(), val) != v.end()
// sorted vector
binary_search(v.begin(), v.end(), val)
```
- ###### find with val
```
// iterator
vector<type>::iterator it = v.find(val);
// index
distance(v.begin(), v.find(v.begin(), v.end(), val));
```
- ###### get nth element
```
v.begin() + n
```
- ###### erasing
```
v.pop_back();
// val
v.erase(val)
// index
v.erase(it)
v.erase(it1, it2)
// clear
v.clear()
```

#### • Set
- ###### insert val
```
s.insert(val)
```
- ###### whether val exists
```
s.find(val) != s.end()
s.count(val)
```
- ###### find with val
```
// iterator
set<type>::iterator it = s.find(val);
// index
distance(s.begin(), s.find(val));
```
- ###### get nth element
```
advance(s.begin(), n)
```
- ###### erasing
```
// val
s.erase(val)
// index
s.erase(it)
s.erase(it1, it2)
// clear
s.clear()
```

#### • Map
- ###### set val from key
```
m[key] = val
```
- ###### get val from key
```
// creates new 
m[key]
// only finds
m.at(key)
```
- ###### whether val exists
```
m.find(val) != m.end()
m.count(val)
```
- ###### find with val
```
// iterator
map<type, type>::iterator it = m.find(val);
// index
distance(m.begin(), m.find(val));
```
- ###### get nth element
```
advance(m.begin(), n)
```
- ###### erasing
```
// key
m.erase(key)
// index
m.erase(it)
m.erase(it1, it2)
// clear
m.clear()
```

#### • Stack

```
stack<int> s;
s.push(10);
s.top();
s.pop();
s.empty();
```

#### • Queue

```
queue<int> q;
q.push(10);
q.front();
q.pop();
q.empty();

q.back(); //last element in queue
```

#### • Priority Queue

```
using pi = pair<int, int>;

priority_queue<int, vector<int>> pq; // largest elements first
priority_queue<int, vector<int>, greater<int>> pq; // smallest elements first
priority_queue<pi, vector<pi>, Compare> pq;

pq.push({cost, i});
auto &[cost, i] = pq.top();
pq.pop();
```

### Binary Search
Thought Process:
1. Index is found once low = high
`while (low < high)`
2. Right bias or left bias?
left: `int mid = low + ((high - low) >> 1);`
right: `int mid = low + ((high - low + 1) >> 1);`
3. Equalities are flexible, but always include/exclude mid correctly
`if (target > nums[mid])` 
then    `low = mid + 1; // mid is not target, so exclude`
else `high = mid; // mid might be target, so include`
4. If unsure, use 2 elements and observe behaviour

#### • Left bias
```
// Loop invariant: if found, index is between [low, high]
while (low < high) {
    int mid = low + ((high - low) >> 1);
    if (target > nums[mid]) {
        low = mid + 1;
    } else {
        high = mid;
    }
}
return nums[low] == target ? low : -1;
```

#### • Right bias 
```
// Loop invariant: if found, index is between [low, high]
int low = 0, high = nums.size() - 1;
while (low < high) {
    int mid = low + ((high - low + 1) >> 1);
    if (target < nums[mid]) {
        high = mid - 1;
    } else {
        low = mid;
    }
}
return nums[low] == target ? low : -1;
```

### Sort

#### • Quick Sort (in-place, NOT stable)
```
int partition(vector<int> &values, int left, int right) {
    int mid = left + (right - left) / 2;
    int val = values[mid];
    while(left <= right) {
        while(values[left] < val) {
            left++;
        }
        while(values[right] > val) {
            right--;
        }
        if(left <= right) {
            int temp = values[left];
            values[left] = values[right];
            values[right] = temp;
            left++;
            right--;
        }
    }
    return left;
}

void quicksort(vector<int> &values, int left, int right) {
    if(left < right) {
        int pivotIndex = partition(values, left, right);
        quicksort(values, left, pivotIndex - 1);
        quicksort(values, pivotIndex, right);
    }
}
```
#### • Merge Sort - Linked List (stable, NOT in-place)
```
```
#### • Merge Sort - Arrays (stable, NOT in-place)
```
void TopDownMerge(vector<int> &nums, int low, int mid, int high) {
    if (low >= high) return;
    int l = low;
    int r = mid + 1;
    int k = 0;
    int size = high - low + 1;
    vector<int> sorted(size, 0);
    while (l <= mid and r <= high)
        sorted[k++] = nums[l] < nums[r] ? nums[l++] : nums[r++];
    while (l <= mid) 
        sorted[k++] = nums[l++];
    while (r <= high) 
        sorted[k++] = nums[r++];
    for (k = 0; k < size; k++)
        nums[k + low] = sorted[k];
}

void mergeSort(vector<int> &nums, int low, int high) {
    if (low >= high) return;
    int mid = (high - low) / 2 + low;
    mergeSort(nums, low, mid);
    mergeSort(nums, mid + 1, high);
    TopDownMerge(nums, low, mid, high);
}
```
#### • Radix Sort (stable, in-place, _O(d(n+k))_)
```
    int getNthDigit(int num, int n) {
        return num/pow(10, n)%10;
    }
    
    void countSort(vector<int>& nums, int digit) {
        int count[10] = {0};
        for (auto &i : nums) {
            count[getNthDigit(i, digit)]++;
        }
        for (int i = 1; i < 10; i++) {
            count[i] += count[i-1];
        }
        for (int i = 9; i > 0; i--) {
            count[i] = count[i-1];
        }
        count[0] = 0;
        vector<int> new_nums(nums.size(), 0);
        for (auto &i : nums) {
            new_nums[count[getNthDigit(i, digit)]++] = i;
        }
        nums = new_nums;
    }
    
    vector<int> sortArray(vector<int>& nums) {
        vector<int> positives;
        vector<int> negatives;
        for (auto &num : nums) {
            if (num >= 0) {
                positives.push_back(num);
            } else {
                negatives.push_back(-num);
            }
        }
        for (int i = 0; i < 6; i++) {
            countSort(positives, i);
            countSort(negatives, i);
        }
        for (auto &num : negatives) {
            num = -num;
        }
        reverse(negatives.begin(), negatives.end());
        negatives.insert(negatives.end(), positives.begin(), positives.end());
        return negatives;
    }
```
### Graph Traversal

#### • Inorder (Left, Root, Right) Stack
```
void addLeft(stack<TreeNode*> *node_stack, TreeNode* node) {
    while(node) {
        node_stack->push(node);
        node = node->left;
    }
}

vector<int> inorderTraversal(TreeNode* root) {
    if (!root) return {};
    stack<TreeNode*> node_stack;
    addLeft(&node_stack, root);
    vector<int> ans;
    while(!node_stack.empty()) {
        TreeNode* curr = node_stack.top();
        node_stack.pop();
        ans.push_back(curr->val);
        if (curr->right) addLeft(&node_stack, curr->right);
    }
    return ans;
}
```
#### • Preorder (Root, Left, Right) Stack
```
vector<int> preorderTraversal(TreeNode* root) {
    if (!root) return {};
    stack<TreeNode*> node_stack;
    vector<int> ans;
    node_stack.push(root);
    while (!node_stack.empty()) {
        TreeNode* curr = node_stack.top();
        node_stack.pop();
        ans.push_back(curr->val);
        if (curr->right) node_stack.push(curr->right);
        if (curr->left) node_stack.push(curr->left);
    }
    return ans;
}
```
#### • Postorder (Left, Right, Root) Stack
```
if (!root) return {};
vector<TreeNode*> explored_rhs;
stack<TreeNode*> node_stack;
addLeft(&node_stack, root);
vector<int> ans;
while(!node_stack.empty()) {
    TreeNode* curr = node_stack.top();
    if (curr->right && find(explored_rhs.begin(), explored_rhs.end(), 
                            curr->right) == explored_rhs.end()) {
        explored_rhs.push_back(curr->right);
        addLeft(&node_stack, curr->right);
        continue;
    }
    node_stack.pop();
    ans.push_back(curr->val);
}
return ans;
}
```
#### • Levelorder (BFS) Queue
```
vector<int> levelOrder(TreeNode* root) {
    if (!root) return {};
    queue<TreeNode*> node_queue;
    vector<int> ans;
    node_queue.push(root);
    while (!node_queue.empty()) {
        TreeNode* curr = node_queue.front();
        node_queue.pop();
        if (curr->left) node_queue.push(curr->left);
        if (curr->right) node_queue.push(curr->right);
        ans.push_back(curr->val);
    }
    return ans;
}
```
#### • DFS (Recursion)
```
vector<int> ans;
if (!root) return;
ans.push_back(root->val);
if (root->left) recurse(root->left);
if (root->right) recurse(root->right);
return ans;
```
### Knapsack Problem
#### • Recursion (Memoization)
```
map<int, map<int, int>> dp;
    
int dp_contains(int target, int index) {
    if (dp.count(target)) {
        if (dp[target].count(index)) return true;
        return false;
    }
    return false;
}

int read(int target, int index) {
    return dp[target][index];
}

void write(int target, int index, int val) {
    dp[target][index] = val;
}
```
#### • DP Table (2D) - [LeetCode Coin Change 1 Problem](https://leetcode.com/problems/coin-change/)
```
int coinChange(vector<int>& coins, int amount) {
    if (amount == 0) return 0;
    int dp[coins.size()][amount+1];
    for (int row = 0; row < coins.size(); row++) {
        dp[row][0] = 0;
        for (int col = 1; col < amount + 1; col++) {
            dp[row][col] = INT_MAX;
            int test_col = col-coins[row];
            int row_min = test_col >= 0 && dp[row][test_col] != INT_MAX 
                    ? dp[row][test_col] + 1
                    : INT_MAX;
            int prev_min = row > 0 ? dp[row-1][col] : INT_MAX;
            dp[row][col] = min(prev_min, row_min);

        }
    }
    return dp[coins.size()-1][amount] > amount ? -1 : dp[coins.size()-1][amount];
}
```
#### • DP Table (Rolling 1D) [LeetCode Coin Change 2 Problem](https://leetcode.com/problems/coin-change-2/)
```
int change(int amount, vector<int>& coins) {
    if (amount == 0) return 1;
    if (coins.empty()) return 0;
    int dp[amount+1];
    dp[0] = 1;
    for (int i = 1; i < amount + 1; i++) {
        dp[i] = 0;
    }
    for (auto &c: coins) {
        for (int i = 1; i < amount + 1; i++) {
            dp[i] = i - c >= 0 ? dp[i - c] + dp[i] : dp[i];
        }
    }
    return dp[amount];
}
```
### Graph Theory
#### Topological Sort [LeetCode Course Schedule 2 Problem](https://leetcode.com/problems/course-schedule-ii/)
```
// build graph
vector<vector<int>> out_edges(graph.size(), vector<int>());
vector<int> in_degree(graph.size(), 0);
queue<int> frontier; // frontier always has in-degree == 0
vector<int> ans;

for (int i = 0; i < graph.size(); i++) {
    if (!in_degree[i]) {
        frontier.push(i);
    }
}

while (!frontier.empty()) {
    int pop_node = frontier.front();
    frontier.pop();
    ans.push_back(pop_node);
    for (auto &edge: out_edges[pop_node]) {
        if (!--in_degree[edge]) {
            frontier.push(edge);
        }
    }
}

return ans.size() == numCourses ? ans : vector<int>();
```
#### Dijkstra's Algorithm [LeetCode Minimum Cost Problem](https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/)
```
vector<vector<pi>> adj_list(graph.size(), vector<pi>());
priority_queue<pi, vector<pi>, Compare> pq;
vector<bool> explored = vector<graph.size(), 0);
// G is an adjacency-list, where they store the edges as grid numbers
// pq will store estimates of node in frontier

// first node
pq.push({0, 0});

while (!pq.empty()) {
    auto &[cost, i] = pq.top();
    pq.pop();
    if (i == graph.size()-1) return cost;
    if (explored[i]) continue;
    explored[i] = true;

    // relax
    for (auto &[nb_cost, nb_i]: adj_list[i]) {
        pq.push({nb_cost + cost, nb_i});
    }
}

return 0;
```
#### Minimum Spanning Tree [LeetCode MST Problem](https://leetcode.com/problems/min-cost-to-connect-all-points/)
```
// prim's algorithm
priority_queue<pi, vector<pi>, Compare> pq;
vector<vector<pi>> adj_list(graph.size(), vector<pi>());
vector<bool> explored(points.size());

// from starting point
pq.push({0, 0});
int total_cost = 0;

while (!pq.empty()) {
    auto [cost, i] = pq.top();
    pq.pop();
    if (explored[i]) continue;
    total_cost += cost; 
    explored[i] = true;

    // iterate through adjacent edges and push unexplored vertices
    for (auto &[nb_cost, nb_i]: adj_list[i]) {
        if (!explored[nb_i]) {
            pq.push({nb_cost, nb_i});
        }
    }
}

return total_cost;
```
