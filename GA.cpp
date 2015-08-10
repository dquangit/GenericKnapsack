#include <iostream>
#include <cstdio>
#include <fstream>
#include <stack>
#include <algorithm>
#include <ctime>
#define maximum 100001
#define num_of_individual 40
using namespace std;
fstream file;

struct datatype
{
    char* filename;
};
datatype data[100];

struct __item
{
    int w;
    int v;
};

__item item[10000];

struct __individual
{
    bool selection[maximum];
    int value;
    int weight;
};

__individual individual[50];

bool myfunction(__individual a,__individual b)
{
    if (a.value>b.value) return true;
    return false;
}

int n,max_value,min_value;
float capacity;

void get_data()
{
data[0].filename="data/s10.txt";
data[1].filename="data/s10-1.txt";
data[2].filename="data/s50.txt";
data[3].filename="data/s50-1.txt";
data[4].filename="data/s100.txt";
data[5].filename="data/s100-1.txt";
data[6].filename="data/s500.txt";
data[7].filename="data/s500-1.txt";
data[8].filename="data/s1000.txt";
data[9].filename="data/s1000-1.txt";
data[10].filename="data/s5000.txt";
data[11].filename="data/s5000-1.txt";
data[12].filename="data/s10000.txt";
data[13].filename="data/s10000-1.txt";
data[14].filename="data/s100000.txt";
data[15].filename="data/u10.txt";
data[16].filename="data/u50.txt";
data[17].filename="data/u100.txt";
data[18].filename="data/u500.txt";
data[19].filename="data/u1000.txt";
data[20].filename="data/wc10.txt";
data[21].filename="data/wc50.txt";
data[22].filename="data/wc1000.txt";
data[23].filename="data/wc5000.txt";
data[24].filename="data/wc10000.txt";
}

int f_size(char* filename)
{
    float capicity;
    file.open(filename,ios::in);
    file>>capicity;
    int t;
    int d=0;
    while(file)
    {
        file>>t;
        d++;
    }
    file.close();
    return d/2;
}

void input(char* filename)
{
    n=f_size(filename);
    file.open(filename,ios::in);
    file>>capacity;
    cout<<"input: "<<endl;
    cout<<"number of items: "<<n<<endl;
    cout<<"capacity:\t "<<capacity<<endl;
    for (int i=1;i<=n;i++)
    {
        file>>item[i].v;

    }
    for (int i=1;i<=n;i++)
    {
        file>>item[i].w;
    }
    file.close();
}

void create_individual(__individual &a)
{
    int tmp;
    a.value=0;
    a.weight=0;
    for (int j=1;j<=n;j++)
        {
            tmp=rand()%2;
            a.selection[j]=tmp;
            if (tmp==1)
            {
                a.weight+=item[j].w;
                a.value+=item[j].v;
            }
        }

}

void create_individual_population()
{
    srand(time(NULL));

    max_value=min_value=0;
    for (int i=0;i<=num_of_individual;i++)
    {
        do
        {
            create_individual(individual[i]);
        }
        while (individual[i].weight>capacity);
        if (individual[max_value].value<individual[i].value) max_value=i;
        if (individual[min_value].value>individual[i].value) min_value=i;
    }
}

__individual crossover(__individual a,__individual b)
{
    __individual tmp;
    do
    {
    tmp.value=tmp.weight=0;
    for (int i=1;i<=n;i++)
    {
        if (rand()%2==0) tmp.selection[i]=a.selection[i];
        else tmp.selection[i]=b.selection[i];
        if (tmp.selection[i]==1)
        {
            tmp.value+=item[i].v;
            tmp.weight+=item[i].w;
        }
    }
    }
    while (tmp.weight>capacity);
    return tmp;
}

__individual mutation(__individual a)
{
    do
    {
    int tmp=rand()%n+1;
    if (a.selection[tmp]==1)
    {
        a.selection[tmp]=0;
        a.value-=item[tmp].v;
        a.weight-=item[tmp].w;
    }
    else
    {
        a.selection[tmp]=1;
        a.value+=item[tmp].v;
        a.weight+=item[tmp].w;

    }
    }
    while (a.weight>capacity);
    return a;
}

void output()
{
    for (int i=1;i<=n;i++)
    {
        cout<<item[i].v<<"\t"<<item[i].w<<"\t"<<endl;
    }
    cout<<endl;
    for (int i=0;i<=num_of_individual;i++)
    {
        for (int j=1;j<=n;j++)
        cout<<individual[i].selection[j];
        cout<<"\t"<<individual[i].value<<"\t"<<individual[i].weight;
        cout<<endl;

    }
    cout<<max_value<<" "<<min_value<<endl;
}


int main()
{
    get_data();
    input(data[3].filename);
    create_individual_population();

    output();
}
