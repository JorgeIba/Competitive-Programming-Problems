template<class T>
inline void read(T &x) {
    x = 0;
    char c = getchar();
    bool flag = 0;
    while (!isdigit(c)) {
        if (c == '-')
            flag = 1;
        c = getchar();
    }
    while (isdigit(c)) {
        x = (x << 3) + (x << 1) + c - '0';
        c = getchar();
    }
    x = flag ? -x : x;
}
 
template<class T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x >= 10)
        write(x / 10);
    putchar(x % 10 + '0');
}