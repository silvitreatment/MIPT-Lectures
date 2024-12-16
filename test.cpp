#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<ll, ll> result(vector<ll> tracks, ll p, ll n) {
    ll cur_sum = 0;
    ll l = 0;
    ll circle = 1;
    ll stroke;
    pair<ll, ll> ans2;
    ll ans = LONG_LONG_MAX;
    for (ll r = 0; r < n * (circle  + 1); r++) {
        cur_sum += tracks[r % n];
        while (cur_sum - tracks[l % n] >= p) {
            cur_sum -= tracks[l% n];
            l++;
        } 
        if (cur_sum >= p) {
            if (ans > (r  - l + 1)) {
                ans = (r - l + 1); 
                stroke = l + 1;
            }  
        }
        if (r == (circle - 1) * n + n - 1 && cur_sum < p) {
            circle++;
            if (circle > 100000) {
                break;
            }
        }
    }
    ans2.first = ans;
    ans2.second = stroke;
    return ans2;
}
int main() {
    ll n, p;
    cin >> n >> p;
    vector<ll> tracks(n);
    for (int i = 0; i < n; i++) cin >> tracks[i];
    pair<ll, ll> ans = result(tracks, p, n);
    cout << ans.second << " " << ans.first << endl;
    return 0;
}