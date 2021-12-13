#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define nn 42
#define kn 152
using namespace std;

struct axis{
	int x,y;
	int k,n; //kind & num id
	int e; //if exist
	axis() {x=y=k=n=0; e=1; }
	axis(int _x,int _y,int _k,int _n,int _e=1):x(_x),y(_y),k(_k),n(_n),e(_e) {}
};
bool operator !=(axis _, axis __) {return !(_.x == __.x && _.y == __.y && _.k == __.k && _.n == __.n && _.e == __.e); }

vector<axis> obj[10], sw[10], ow[10], is;
int st[10]; //state
char olist[kn];
int b[nn][nn], chg[12][12];
axis mvlist[nn*nn], nowlist[nn*nn], newlist[nn*nn];
int stoplist[nn];
bool babawin=0;
int n,m,k;
queue<axis> updQ;

void init()
{
	for(int i=0;i<10;++i)
		vector<axis>().swap(obj[i]),vector<axis>().swap(sw[i]),vector<axis>().swap(ow[i]);
	vector<axis>().swap(is);
}

void parse() //words wont overlap
{
	memset(b,-1,sizeof(b));
	memset(chg,0,sizeof(chg));
	for(int i=0;i<10;++i) st[i]=0;
	
	for(int i=0;i<10;++i)
	{
		for(auto w:sw[i]) b[w.x][w.y]=i;
		for(auto w:ow[i]) b[w.x][w.y]=i+10;
	}
	for(auto w:is) b[w.x][w.y]=20;	
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j)
		{
			//attribute parse
			if(j+2<=m && (b[i][j]>=0) && (b[i][j]<10) && (b[i][j+1]==20) && (b[i][j+2]>=10) && (b[i][j+2]<20))
			{
				st[b[i][j]]|=(1<<(b[i][j+2]-10));
			}
			if(i+2<=n && (b[i][j]>=0) && (b[i][j]<10) && (b[i+1][j]==20) && (b[i+2][j]>=10) && (b[i+2][j]<20))
			{
				st[b[i][j]]|=(1<<(b[i+2][j]-10));
			}
			//change parse
			if(j+2<=m && (b[i][j]>=0) && (b[i][j]<10) && (b[i][j+1]==20) && (b[i][j+2]>=0) && (b[i][j+2]<10))
			{
				chg[b[i][j]][b[i][j+2]]=1;
			}
			if(i+2<=n && (b[i][j]>=0) && (b[i][j]<10) && (b[i+1][j]==20) && (b[i+2][j]>=0) && (b[i+2][j]<10))
			{
				chg[b[i][j]][b[i+2][j]]=1;
			}
		}

	vector<axis> temp[10];
	int ifchg[10];
	axis w2;
	for(int i=0;i<10;++i)
	{
		ifchg[i] = 0;
		if(!chg[i][i])
		{
			for(int j=0;j<10;++j)
				if(chg[i][j])
				{
					ifchg[i] = 1;
					for(auto w: obj[i])
					{
						w2.x = w.x, w2.y = w.y, w2.k = j, w2.e = 1;
						temp[j].push_back(w2);
					}
				}
		}
	}
	for(int i=0;i<10;++i)
	{
		if(ifchg[i]) vector<axis>().swap(obj[i]);
		for(auto w: temp[i])
		{
			w2 = w; w2.n = obj[i].size();
			obj[i].push_back(w2);
		}
	}
}

bool cmp_u(axis _,axis __) {return _.x<__.x; }
bool cmp_d(axis _,axis __) {return _.x>__.x; }
bool cmp_l(axis _,axis __) {return _.y<__.y; }
bool cmp_r(axis _,axis __) {return _.y>__.y; }

void upd(axis t)
{
	if(t.k<10) obj[t.k][t.n]=t;
	else if(t.k<20) sw[t.k-10][t.n]=t;
	else if(t.k<30) ow[t.k-20][t.n]=t;
	else is[t.n]=t;
}

void mv(axis t, axis d)
{
	int nowl=0, newl=0, stopl=0;
	memset(stoplist,0,sizeof(stoplist));
	while(!updQ.empty()) updQ.pop();
		
	t.x+=d.x; t.y+=d.y;
	nowlist[nowl++]=t;
	while(nowl)
	{
		t=nowlist[0];
		if(!(t.x>=1&&t.x<=n&&t.y>=1&&t.y<=m)) return;
		
		stopl=0;
		//if stop && not push
		bool ifstop=0;
		int it;
		for(int i=0;i<10;++i)
		{
			if((st[i]&8)&&!(st[i]&4))
			{
				it=-1;
				for(auto w:obj[i]) if(w.e&&w.x==t.x&&w.y==t.y) {ifstop=1; it=i; }
				if(it>=0) stoplist[stopl++]=it;
			}
		}
		if(ifstop)
		{
			bool allopen=1, allshut=1;
			bool ifopen=1;
			axis temp;
			for(int i=0;i<nowl;++i)
			{
				temp=nowlist[i];
				if(temp.k<10 && !(st[temp.k]&256)) allopen=0;
				if(temp.k<10 && !(st[temp.k]&512)) allshut=0;
			}
			if(allopen || allshut)
			{
				for(int i=0;i<stopl;++i)
				{
					it=stoplist[i];
					if(allopen && !(st[it]&512)) {ifopen=0; break; }
					if(allshut && !(st[it]&256)) {ifopen=0; break; }
				}
			}
			else ifopen=0;
			
			if(ifopen)
			{
				for(int i=0;i<nowl;++i) updQ.push(nowlist[i]);
				break;
			}
			else return;
		}

		//if push
		newl=0;
		for(int i=0;i<10;++i)
		{
			if(st[i]&4)
			{
				for(auto w:obj[i])
				{
					if(w.e&&w.x==t.x&&w.y==t.y)
					{
						w.x+=d.x; w.y+=d.y;
						newlist[newl++]=w;
					}
				}
			}
			for(auto w:sw[i])
			{
				if(w.e&&w.x==t.x&&w.y==t.y)
				{
					w.x+=d.x; w.y+=d.y;
					newlist[newl++]=w;
				}				
			}
			for(auto w:ow[i])
			{
				if(w.e&&w.x==t.x&&w.y==t.y)
				{
					w.x+=d.x; w.y+=d.y;
					newlist[newl++]=w;
				}				
			}
		}
		for(auto w:is)
			if(w.e&&w.x==t.x&&w.y==t.y)
			{
				w.x+=d.x; w.y+=d.y;
				newlist[newl++]=w;
			}

		//store update
		for(int i=0;i<nowl;++i) updQ.push(nowlist[i]);
		nowl=newl;
		for(int i=0;i<nowl;++i) nowlist[i]=newlist[i];
	}

	//update
	axis temp;
	while(!updQ.empty())
	{
		temp=updQ.front(); updQ.pop();
		upd(temp);
	}
}

void work();
void move(axis d)
{
	//find you
	int mvl=0;
	for(int i=0;i<10;++i)
	{
		if(st[i]&1)
		{
			for(auto w:obj[i]) if(w.e) mvlist[mvl++]=w;
		}
	}
	if(mvl==0) return;
	if(d.x<0) sort(mvlist,mvlist+mvl,cmp_u);
	if(d.x>0) sort(mvlist,mvlist+mvl,cmp_d);
	if(d.y<0) sort(mvlist,mvlist+mvl,cmp_l);
	if(d.y>0) sort(mvlist,mvlist+mvl,cmp_r);
	
	axis t;
	for(int i=0;i<mvl;++i)
	{
		t=mvlist[i];
		mv(t, d);
	}
	parse();
	work();
}

void work()
{
	//hot & melt
	for(int i=0;i<10;++i)
	{
		if(st[i]&128)
		for(int j=0;j<10;++j)
			if(st[j]&64)
			{
				for(auto w1:obj[i])
					for(auto w2:obj[j])
						if(w1.e&&w2.e&&w1.x==w2.x&&w1.y==w2.y)
						{
							w1.e=0; upd(w1);
						}
			}
	}	
	//sink
	for(int i=0;i<10;++i)
	{
		if(st[i]&32)
		{
			for(auto w1:obj[i])
			{
				if(!w1.e) continue;
				bool ifsink = 0;
				for(int j=0;j<10;++j)
				{
					for(auto w2:obj[j])
						if(w2.e&&w1.x==w2.x&&w1.y==w2.y&&w1!=w2)
						{
							w2.e=0; upd(w2);
							ifsink=1;
						}
					for(auto w2:ow[j])
						if(w2.e&&w1.x==w2.x&&w1.y==w2.y&&w1!=w2)
						{
							w2.e=0; upd(w2);
							ifsink=1;
						}
					for(auto w2:sw[j])
						if(w2.e&&w1.x==w2.x&&w1.y==w2.y&&w1!=w2)
						{
							w2.e=0; upd(w2);
							ifsink=1;
						}
				}
				for(auto w2:is)
				    if(w2.e&&w1.x==w2.x&&w1.y==w2.y&&w1!=w2)
					{
						w2.e=0; upd(w2);
						ifsink=1;
					}
					
				if(ifsink)
				{
					w1.e=0; upd(w1);
				}
			}
		}
	}
	//open & shut
	for(int i=0;i<10;++i)
	{
		if(st[i]&256)
		for(int j=0;j<10;++j)
			if(st[j]&512)
			{
				for(auto w1:obj[i])
					for(auto w2:obj[j])
						if(w1.e&&w2.e&&w1.x==w2.x&&w1.y==w2.y)
						{
							w1.e=0; w2.e=0; upd(w1); upd(w2);
						}
			}
	}
	//defeat
	for(int i=0;i<10;++i)
	{
		if(st[i]&1)
		for(int j=0;j<10;++j)
			if(st[j]&16)
			{
				for(auto w1:obj[i])
					for(auto w2:obj[j])
						if(w1.e&&w2.e&&w1.x==w2.x&&w1.y==w2.y)
						{
							w1.e=0; upd(w1);
						}
			}
	}
	//win
	for(int i=0;i<10;++i)
	{
		if(st[i]&1)
		for(int j=0;j<10;++j)
			if(st[j]&2)
			{
				for(auto w1:obj[i])
					for(auto w2:obj[j])
						if(w1.e&&w2.e&&w1.x==w2.x&&w1.y==w2.y)
						{
							babawin=1;
							return;
						}
			}
	}
}

int main()
{
	freopen("baba.in","r",stdin);
	freopen("baba.out","w",stdout);

	int T;
	char ch;
	scanf("%d\n",&T);
	while(T--)
	{
		init();
		babawin=0;
		scanf("%d%d%d\n",&n,&m,&k);
		for(int i=1;i<=n;++i)
		{
			for(int j=1;j<=m;++j)
			{
				scanf("%c",&ch);
				if(ch>='0'&&ch<='9') obj[ch-'0'].push_back(axis(i,j,ch-'0',obj[ch-'0'].size()));
				if(ch>='a'&&ch<='j') sw[ch-'a'].push_back(axis(i,j,ch-'a'+10,sw[ch-'a'].size()));
				if(ch>='A'&&ch<='J') ow[ch-'A'].push_back(axis(i,j,ch-'A'+20,ow[ch-'A'].size()));
				if(ch=='*') is.push_back(axis(i,j,30,is.size()));
			}
			scanf("\n");
		}
		parse();
		work();

		int dx,dy;
		scanf("%s\n",olist);
		if(babawin)
		{
			printf("YES\n");
			continue;
		}
		
		for(int i=0;i<k;++i)
		{
			if(olist[i]=='L') dx=0,dy=-1;
			if(olist[i]=='R') dx=0,dy=1;
			if(olist[i]=='U') dx=-1,dy=0;
			if(olist[i]=='D') dx=1,dy=0;
			move(axis(dx,dy,-1,-1));
			if(babawin) break;
		}
		if(babawin) printf("YES\n");
		else printf("NO\n"); 
	}
	
	return 0;
}
