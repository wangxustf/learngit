#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <cstring>
using namespace std;

int data[100], sol[100];
int n, dest, cnt;
int ok;

int find(int curr, int curr_len, int start)
{
	int t, value, i, j;
	if (curr_len == dest)
	{
		//组装好cnt-1根,那么剩下的长度是dest,所以直接可以返回
		if (++curr == cnt-1) return ok = 1;
		
		//从第一个没有用过的棒开始
		//因为如果可行的话,下一组肯定是从第一个没有用过的开始
		//若下一组从第一个没有用过的棒开始的,那么可以断定,从第二个没有用过的开始将得不到最优解
		//因为始终会留着第一个没有用过的棒在那里呆着,而不可能完成任务
		//这一步枝剪比较重要
		for (j = 0; j < n; ++j) if(sol[j]==0)break;
		sol[j] = 1;
		if(find(curr, data[j], j+1)) return 1;
		return sol[j] = 0;
	}

   	for (i = start; i < n; ++i)
		if (sol[i] == 0)
		{
			if ((t = curr_len+data[i]) <= dest)
			{
				sol[i] = 1;
				if (find(curr, t, i+1)) return 1;
				sol[i] = 0;
			}
			if (ok) return 1;
			
			//若当前的棒组装完成,而组装下一个的时候失败
			//则当前的就已经失败
			//因为是从大到小排列的
			//第curr根用的是较大的组装成的
			//因此剩的是小的,小的灵活性强
			//用灵活性强的都不能完成任务
			//再把当前的组装用小的去完成
			//再次组装下一根,必然失败
			if (t == dest) return 0;
			
			//同一次搜索中,两个相同长度的只搜索一次
			value = data[i++];
			while (i < n && data[i] == value) ++i;
			--i;
		}
    return 0;
}


int solve(int* data, int n, int sum, int m)
{
    sort(data, data+n, greater<int>());

	//从小到大枚举所有可能的结果
	ok = 0;
    for (dest = m; dest < sum; ++dest)
    {
        if (sum%dest == 0)
        {
			memset(sol, 0, sizeof(sol));
			cnt = sum/dest;
			find(0, 0, 0);
			if (ok) return dest;
        }
    }
    return sum;
}

int main(void)
{
    int sum, max;
    while (scanf("%d", &n) == 1, n)
    {
		sum = max = 0;
        for (int i = 0 ; i < n; ++i) {scanf("%d", data+i), sum+=data[i]; if (data[i] > max) max = data[i];}
        printf("%d\n", solve(data, n, sum, max));
    }
    return 0;
}
