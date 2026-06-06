#include <stdio.h>
#include <memory.h>
#define debug(x) printf("%s is %d\n", #x, x);

typedef long long ll;
const ll MAXN = 1e5 + 5;
const ll MOD = 1e9;

struct disjoint_set {
    ll parent[MAXN];

    void init() {
        memset(parent, -1, sizeof(parent));
    }
    ll find(ll x) {
        if (parent[x] < 0) return x;
        return parent[x] = find(parent[x]);
    }
    ll merge(ll u, ll v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        parent[v] += parent[u];
        parent[u] = v;
        return true;
    }
    ll size(ll u) {
        return -parent[find(u)];
    }
};

struct edge_t {
    ll u, v, w;
    bool operator<(const edge_t& other) {
        return w < other.w;
    }
};

ll N;
ll M;
edge_t edges[MAXN];
ll edges_sz;

edge_t buf[MAXN];
void sort(edge_t arr[], ll s, ll e) {
    if (s + 1 >= e) return;
    ll m = (s + e)/2;
    sort(arr, s, m);
    sort(arr, m, e);

    ll l = s, r = m, k = 0;
    while (l < m && r < e) {
        if (arr[l] < arr[r]) buf[k++] = arr[l++];
        else buf[k++] = arr[r++];
    }

    while (l < m) buf[k++] = arr[l++];
    while (r < e) buf[k++] = arr[r++];

    for (ll i = 0; i < k; i++)
        arr[i + s] = buf[i];
}

int upper_bound(edge_t arr[], ll s, ll e, ll target) {
    ll l = s, r = e;
    while (l + 1 < r) {
        ll m = (l + r)/2;
        if (arr[m].w < target) r = m;
        else l = m;
    }
    return r;
}

ll pref[MAXN];
ll solve() {
    sort(edges, 0, edges_sz);
    for (int i = 0; i < edges_sz; i++)
        pref[i + 1] = pref[i] + edges[i].w;

    disjoint_set uf;
    uf.init();

    ll cost = 0;
    for (int i = edges_sz - 1; i >= 0; i--) {
        ll u = edges[i].u;
        ll v = edges[i].v;
        ll w = edges[i].w;
        if (uf.find(u) == uf.find(v)) continue;

        cost += (uf.size(u) * uf.size(v) * pref[i + 1]) % MOD;
        cost %= MOD;
        uf.merge(u, v);
    }
    return cost;
}

int main() {
    scanf("%lld %lld", &N, &M);
    for (ll i = 0; i < M; i++) {
        ll u, v, w;
        scanf("%lld %lld %lld", &u, &v, &w);
        if (u > v) {
            ll tmp = u;
            u = v;
            v = tmp;
        }

        edges[edges_sz++] = {u, v, w};
    }

    ll ret = solve();
    printf("%lld\n", ret);
    return 0;
}