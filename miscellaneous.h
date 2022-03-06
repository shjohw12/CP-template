/* ordered_set */
using namespace __gnu_pbds;
template<typename T, typename U = less<T>>
using ordered_set = tree<T, null_type, U, rb_tree_tag, tree_order_statistics_node_update>;
// order_of_key(k) = The number of items in a set that are strictly smaller than k
// find_by_order(k) = It returns an iterator to the k-th(0-based) element

/* gp_hash_table */
using namespace __gnu_pbds;
using myset = gp_hash_table<int, null_type>;
using mymap = gp_hash_table<int, int>;

/* rope */
using namespace __gnu_cxx;
// push_back(x);

// pop_back();

// insert(x, rope r1)
// x번째 원소 앞에 r1 삽입

// erase(x, l)
// x번째 원소부터 l개 삭제

// substr(x, l)
// x번째 원소부터 l개 substr

// replace(x, l, rope r1)
// x번째 원소부터 l개 r1로 replace

// rope r1 + rope r2
// concatenate

/* random */
// random_device rdd;
// mt19937 rng(rdd());
mt19937 rng(0x971111);
inline int randint(int mn, int mx) {
    return uniform_int_distribution<int>(mn, mx)(rng);
}

/* time */
auto START = chrono::system_clock::now();
while (1) {
    auto NOW = chrono::system_clock::now();
    int elapsed = chrono::duration_cast<chrono::milliseconds>(NOW - START).count();
}

/* string에 한 줄 입력받기 */
getline(cin, string)

/* char[]에 한 줄 입력받기 */
cin.getline(char *, sizeof(char *))

/* 공백 버퍼 지우기 */
cin >> ws

/* string으로부터 입력받기 */
string s; cin >> s;
stringstream ss(s);
while (ss >> s) {

}

/* char[]로부터 입력받기 */
scanf("%s", buf); // buf = "12 + 34 = 46"
sscanf(buf, "%s = %s + %s", str1, str2, str3); // str1 = "12", str2 = "34", str3 = "46"

/* std::rotate */
rotate(begin, middle, end)
// middle이 맨 앞에 오도록 왼쪽 회전
// [begin, middle)을 맨 뒤에 붙임

rotate(rbegin, middle, rend)
// middle이 맨 뒤에 가도록 오른쪽 회전
// (middle, rbegin]을 맨 앞에 붙임

/* 원점에서 (x, y)까지의 거리 */
hypot(x, y)

/* 원점과 (x, y)를 잇는 선분과 +x축이 이루는 각 [-PI ~ PI] */
atan2(x, y)

/* list1의 p가 가리키는 위치에 list2의 [s, e)를 잘라 붙임 */
list1.splice(p, list2, s, e)