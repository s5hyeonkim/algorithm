#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct coord
{
    int y, x;
};

struct info
{
    int y, x, m;
};
queue <info> q;
vector <coord> mac_pos;
queue <int> dirnum;

int r, c, t;
int map[51][51] = { 0, };

int map_rest[51][51] = { 0, };
int map_move[51][51] = { 0, };
int macbyflow[51][51] = { 0, };
int dc[] = { 0,1,0,-1,0,1,0,-1 };
int dr[] = { -1 ,0,1,0,1,0,-1,0 };


void dust_move(int my, int mx)
{
    // 이동할 수 있는 방향 선별
    for (int i = 0; i < 4; i++)
    {
        int ny = my + dr[i];
        int nx = mx + dc[i];
        //이동 못하는 경우, 칸넘어감/ 공청기 있음
        if (ny <= 0 || nx <= 0 || ny > r || nx > c) continue;
        if (map[ny][nx] == -1) continue;
        dirnum.push(i);
    }
    int movenum = dirnum.size();
    int rest = map[my][mx] / 5;
    map_rest[my][mx] = map[my][mx] - rest * movenum;
    while (!dirnum.empty())
    {
        int move_dir = dirnum.front();
        int ny = my + dr[move_dir];
        int nx = mx + dc[move_dir];
        dirnum.pop();
        //이동한 좌표에 대하여 분배
        map_move[ny][nx] += map[my][mx] / 5;
    }

}

int dyBym = 0;
int dxBym = 0;


void dustBymac(int my, int mx, int num)
{
    int ny = my + dr[num];
    int nx = mx + dc[num];
    if (ny <= 0 || nx <= 0 || nx > c) return;
    //아래쪽일떄는 행이 4보다 작거나 6보다 크면 종료
    // 위쪽일때는 
    if ((num > 3 && ny < mac_pos[1].y) || (num > 3 && ny >r) || (num <= 3 && ny > mac_pos[0].y)) return;
    if (map[ny][nx] == -1)
    {
        map[my][mx] = 0;
        return;
    }
    if (map[my][mx] != -1)
    {
        map[my][mx] = map[ny][nx];
    }
 
    dyBym = ny;
    dxBym = nx;
    dustBymac(ny, nx, num);
}

void machine_on()
{
    for (int i = 0; i < mac_pos.size(); i++)
    {
        dyBym = mac_pos[i].y;
        dxBym = mac_pos[i].x;
        for (int j = 0; j < 4; j++)
        {
            int dirnum = j;
            if (i % 2 == 1) dirnum += 4;
            dustBymac(dyBym, dxBym, dirnum);
            
        }
    }
}

int main()
{
    cin >> r >> c >> t;
    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == -1)
            {
                //짝수벡터는 반시계 / 홀수벡터는 시계
                mac_pos.push_back({ i,j });
            }
        }
    }

    int timeflow = 0;
    int dustsum = 0;

    while (timeflow < t)
    {
        for (int i = 1; i <= r; i++)
        {
            for (int j = 1; j <= c; j++)
            {
                if (map[i][j] > 0) dust_move(i, j);
            }
        }


        for (int i = 1; i <= r; i++)
        {
            for (int j = 1; j <= c; j++)
            {
                if (map[i][j] < 0) continue;
                map[i][j] = map_rest[i][j] + map_move[i][j];
                map_rest[i][j] = 0;
                map_move[i][j] = 0;
            }
        }
        int de = 1;
        machine_on();
        
        timeflow++;
    }
    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            if (map[i][j] > 0) dustsum += map[i][j];
        }
    }
    cout << dustsum << endl;
}