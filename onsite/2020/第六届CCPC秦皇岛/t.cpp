
#define dbg(x...) do { cout << #x << " -> "; err(x); } while (0)
void err() { cout << endl; }
template <class T, class... Ts> void err(const T& arg, const Ts&... args) {
	cout << arg << ' '; err(args...);
}



	int _T; scanf("%d", &_T);
	for (int CAS = 1; CAS <= _T; ++CAS) {
		printf("Case #%d: ", CAS);
		
	}
