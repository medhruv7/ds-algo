#include<bits/stdc++.h>
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
#define ll long long
using namespace std;
#define left(i) (2*i + 1)
#define right(i) (2*i + 2)
#define parent(i) ((i-1)/2)
#include <vector>

template<class T>
class SegmentTree
{
    public:
        SegmentTree(std::vector<T> data, T value, T (*combine)(T obj1, T obj2));
        SegmentTree(T ar[], int n, T value, T (*combine)(T obj1, T obj2));
        T query(int l, int r);
        void update(int idx, T val);
        //TODO lazy propagation
    private:
        T *tree;
        void buildTree(std::vector<T> data);
        int segTreeSize;
        T valueForExtraNodes;
        T (*combine)(T obj1, T obj2);
        int calculateSize(int n);
        T queryHelper(int l,int r, int st, int ed, int node);
};

template<class T> SegmentTree<T>::SegmentTree(std::vector<T> data,
                                                T value, T (*combine)(T obj1, T obj2))
{
   this->combine = combine;
   valueForExtraNodes = value;
   segTreeSize = calculateSize(data.size());
   buildTree(data);
}

template<class T> SegmentTree<T>::SegmentTree(T ar[], int n,
                                            T value, T (*combine)(T obj1, T obj2))
{
   this->combine = combine;
   valueForExtraNodes = value;
   segTreeSize = calculateSize(n);

   std::vector<T> data;
   for(int i = 0; i < n; i++)
         data.push_back(ar[i]);

   buildTree(data);
}


template<class T> int SegmentTree<T>::calculateSize(int n)
{
    int pow2 = 1;
    while( pow2 < n)
    {
        pow2 = pow2 << 1;
    }
    return 2*pow2 - 1;
}

template<class T> T SegmentTree<T>::query(int l, int r)
{
    int st = 0, ed = segTreeSize/2;
    return queryHelper(l, r, st, ed, 0);
}

template<class T> T SegmentTree<T>::queryHelper(int l,int r, int st, int ed, int node)
{
    if( (r < st) || (l > ed) || (l > r) )
        return valueForExtraNodes;
    if(st >= l && ed <= r)
        return tree[node];
    T leftVal = queryHelper(l, r, st, (st + ed)/2, left(node));
    T rightVal = queryHelper(l, r, (st+ed)/2 + 1, ed, right(node));
    return combine(leftVal, rightVal);
}

template<class T> void SegmentTree<T>::buildTree(std::vector<T> data)
{
   int n = data.size();
   tree = new T[segTreeSize];
   int extraNodes = (segTreeSize/2 + 1) - n;
   for(int i = segTreeSize - 1; i >= 0; i--)
   {
       if(extraNodes>0)
           {
               tree[i] = valueForExtraNodes;
               extraNodes--;
           }
       else if(n>0)
           {
               tree[i] = data[n-1];
               n--;
           }
       else
           tree[i] = combine(tree[left(i)], tree[right(i)]);
   }
}

template<class T> void SegmentTree<T>::update(int idx, T val)
{
    int segTreeIdx = (segTreeSize/2) + idx;
    tree[segTreeIdx] = val;
    while(parent(segTreeIdx) >= 0)
    {
        segTreeIdx = parent(segTreeIdx);
        if(right(segTreeIdx) < segTreeSize)
          tree[segTreeIdx] = combine(tree[left(segTreeIdx)], tree[right(segTreeIdx)]);
        if(segTreeIdx == 0)
            break;
    }
}

// returns number of employees with salaries between lo and hi
int calc(int lo, int hi, map<int,int>& sal2freq)
{
    int res = 0;
    auto it = sal2freq.lower_bound(lo);
    while(it != sal2freq.end() && it->first <= hi){
        res += it->second;
        it++;
    }
    return res;
}
//returns the bucket number to which x belongs
int bucket_no(int x)
{
    // 1-100 in block 0 but 100/100 = 1
    if(x % 100 == 0)
        x--;
    return (x / 100);
}

int sum(int x,int y) { return x+y; }
int main()
{
    fast_io;
    int n,q;
    cin >> n >> q;

    vector < int > employee(n);
    vector< int > buckets(10000000, 0);

    // salary = key, number of employees with this salary = value
    map < int, int> salary2freq;

    for(int  i = 0 ; i < n; i++)
    {
        int salary;
        cin >> salary;

        employee[i] = salary;
        salary2freq[salary]++;

        buckets[bucket_no(salary)]++;
    }
    SegmentTree < int > rangeSumQueries(buckets, 0, sum);

    while(q--)
    {
        char ch;
        cin >> ch;
        if(ch == '!')
        {
            int k,x;
            cin >> k >> x;
            int prev_salary = employee[k-1];
            employee[k-1] = x;

            int prev_bucket = bucket_no(prev_salary);
            int new_bucket = bucket_no(x);

            buckets[prev_bucket]--;
            buckets[new_bucket]++;
            salary2freq[prev_salary]--;
            salary2freq[x]++;

            rangeSumQueries.update(prev_bucket, buckets[prev_bucket]);
            rangeSumQueries.update(new_bucket, buckets[new_bucket]);
        }
        else
        {
            int a,b;
            cin >> a >> b;

            int lbucket = bucket_no(a);
            int rbucket = bucket_no(b);

            int ans = calc(a, min((lbucket+1)*100, b), salary2freq);
            ans  = ans + ((lbucket!=rbucket) ? calc(max(a, rbucket*100 + 1), b, salary2freq) : 0);
            ans  = ans + rangeSumQueries.query(lbucket+1, rbucket-1);

            cout << ans << '\n';
        }
    }

    return 0;
}
