#include <iostream>
#include <algorithm>
#include <queue>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

using namespace std;

typedef struct qube{
	int arr[4][5][5];
};

typedef struct pos{
	int layer, x, y, count;
};

qube filed[5];
int select_arr[5];
int nRet;

int nx[] = { 0, 1, 0, -1 };
int ny[] = { -1, 0, 1, 0 };
int nlayer[] = { -1, 1 };

int bfs()
{
	queue <pos> que;
	que.push({ 0, 0, 0, 0});

	int visit[5][5][5] = { 0, };

	visit[0][0][0] = 1;

	while (!que.empty())
	{
		pos temp = que.front();
		que.pop();

		if (temp.x == 4 && temp.y == 4 && temp.layer == 4)
		{
			return temp.count;
		}

		int tempx = 0;
		int tempy = 0;
		int templayer = 0;
		int tempcount = 0;

		for (int i = 0; i < 6; i++) // 위 오른쪽 아래 왼쪽 위 아래
		{
			if ((temp.layer == 0 && i == 4) || (temp.layer == 4 && i == 5))
				continue;

			if (i < 4)
			{
				tempx = temp.x + nx[i];
				tempy = temp.y + ny[i];

				if (tempx >= 0 && tempy >= 0 && tempx < 5 && tempy < 5)
				{
					if (!visit[templayer][tempy][tempx] && filed[templayer].arr[select_arr[templayer]][tempy][tempx])
					{
						tempcount = temp.count + 1;
						que.push({ templayer, tempx, tempy, tempcount });
						visit[templayer][tempy][tempx] = 1;
					}
				}

			}
			else
			{
				templayer = temp.layer + nlayer[i - 4];

				if (!visit[templayer][temp.y][temp.x] && filed[templayer].arr[select_arr[templayer]][temp.y][temp.x])
				{
					tempcount = temp.count + 1;
					que.push({ templayer, temp.x, temp.y, tempcount });
					visit[templayer][temp.y][temp.x] = 1;
				}
			}

		}
	}

	return 987654322;

}


void dfs(int cnt)
{
	if (cnt == 5)
	{
		nRet = min(nRet, bfs());
		return;
	}

	for (int k = 0; k < 5; k++)
	{
		select_arr[cnt] = k;
		dfs(cnt + 1);
	}
}


int main()
{
	int t;
	int test_case;

	freopen("input.txt", "r", stdin);

	cin >> t;

	for (test_case = 1; test_case <= t; ++test_case)
	{
		for (int k = 0; k < 5; k++){
			for (int i = 0; i < 5; i++){
				for (int j = 0; j < 5; j++){
					cin >> filed[k].arr[0][i][j];
				}
			}
		}

		///회전 후 결과 저장
		for (int k = 0; k < 5; k++){
			for (int i = 0; i < 5; i++){
				for (int j = 0; j < 5; j++)
				{
					filed[k].arr[1][i][j] = filed[k].arr[0][4 - j][i];
				}
			}

			for (int i = 0; i < 5; i++){
				for (int j = 0; j < 5; j++)
				{
					filed[k].arr[2][i][j] = filed[k].arr[0][4 - i][4 - j];
				}
			}

			for (int i = 0; i < 5; i++){
				for (int j = 0; j < 5; j++)
				{
					filed[k].arr[3][i][j] = filed[k].arr[0][j][4 - i];
				}
			}
		}


		nRet = 987654321;
		dfs(0);
	
		if (nRet == 987654321)
			cout << -1 << "\n";
		else
			cout << nRet << "\n";

	}

	return 0;
}