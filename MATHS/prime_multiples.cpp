#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, k;
    cin >> n >> k;

    vector<ll> primes(k);
    for (ll i = 0; i < k; i++) cin >> primes[i];

    ll ans = 0;

    for (ll mask = 1; mask < (1LL << k); mask++) {
        ll mylcm = 1;
        ll cnt = 0;
        ll i = 0; 
        bool possible = true;

        ll temp_mask = mask;
        while (temp_mask > 0) {
            if (temp_mask & 1) {
                cnt++;
                if (mylcm > n / primes[i]) {
                    possible = false;
                    break;
                }
                mylcm *= primes[i];
            }
            temp_mask >>= 1; 
            i++;             
        }

        if (!possible) continue;

        if (cnt % 2 == 1) ans += (n / mylcm);
        else ans -= (n / mylcm);
    }

    cout << ans << endl;
    return 0;
}