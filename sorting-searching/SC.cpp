#include <iostream>
#include <vector>
#include <set>
using namespace std;

typedef long long ll;

int N, K;
vector<int> x;
multiset<int> s1, s2;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;

    x.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> x[i];
        if (i < K) s1.insert(x[i]);
    }

    long long cst1 = 0, cst2 = 0;
    while (s1.size() > (K + 1) / 2)
        s2.insert(*s1.rbegin()), s1.erase(prev(s1.end()));

    int at = K, median = *s1.rbegin();

    // calculate first cost
    for (const auto& a : s1)
        cst1 += (ll) a;
    for (const auto& a : s2)
        cst2 += (ll) a;
    cout << cst2 - cst1 + (s1.size() == s2.size() ? 0 : median); // do some math figuring

    while (at < N)
    {
        if (x[at] <= median) s1.insert(x[at]), cst1 += x[at];
        else s2.insert(x[at]), cst2 += x[at];

        if (x[at - K] <= median) s1.erase(s1.find(x[at - K])), cst1 -= x[at - K];
        else s2.erase(s2.find(x[at - K])), cst2 -= x[at - K];

        while (s1.size() > (K + 1) / 2)
            s2.insert(*s1.rbegin()), cst2 += *s1.rbegin(), cst1 -= *s1.rbegin(), s1.erase(prev(s1.end()));
        while (s2.size() > K / 2)
            s1.insert(*s2.begin()), cst1 += *s2.begin(), cst2 -= *s2.begin(), s2.erase(s2.begin());

        median = *s1.rbegin();
        cout << " " << cst2 - cst1 + (s1.size() == s2.size() ? 0 : median);

        at++;
    }

    cout << "\n";

    return 0;
}
