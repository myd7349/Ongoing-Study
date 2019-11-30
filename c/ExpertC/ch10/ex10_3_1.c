void myfunction1(int fruit[2][3][5])
{
}

void myfunction2(int fruit[][3][5])
{
}

void myfunction3(int (*fruit)[3][5])
{
}


int main(void)
{
    int apricout[2][3][5] = {};

    myfunction1(apricout);
    myfunction1(apricout);
    myfunction1(apricout);

    int (*p)[3][5] = apricout;

    myfunction1(p);
    myfunction1(p);
    myfunction1(p);

    int (*q)[2][3][5] = &apricout;

    myfunction1(*q);
    myfunction1(*q);
    myfunction1(*q);

    return 0;   
}
