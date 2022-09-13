int main() {
    int a = 0;
    {
        a = 3;
        int a = 1;
        a = 9;
    }
    return a;
}