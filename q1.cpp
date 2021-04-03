#include<bits/stdc++.h>

using namespace std;
#define pi pair<int,int>
#define ll long long
#define piii pair<long long,pair<int,int> >
const ll INF=1e18;
vector<vector<pi > > adj;
vector<vector<ll> > dist;

void dijkstra(int s,int total_coupons)
{
	priority_queue<piii,vector<piii>,greater<piii>> pq;
	dist[s][0] = 0;
	pq.push({0,{s,0}});
	while(!pq.empty())
	{
		int cost = pq.top().first;
		int source = pq.top().second.first;
		int coupon= pq.top().second.second;
		pq.pop();
		if(dist[source][coupon] < cost)
		   continue;
		for(auto child : adj[source])
		{
			int v = child.first;
			int w = child.second;
			if(coupon == total_coupons)
			{
				if(dist[v][coupon] > dist[source][coupon]+w)
				{
					dist[v][coupon] = dist[source][coupon] + w;
					pq.push({dist[v][coupon],{v,coupon}});
				}
			}
			else
			{
				//either we don't take coupon
				if(dist[v][coupon] > dist[source][coupon]+w)
				{
					dist[v][coupon] = dist[source][coupon] + w;
					pq.push({dist[v][coupon],{v,coupon}});
				}
				//or take it
				if(dist[v][coupon+1] > dist[source][coupon])
				{
					dist[v][coupon+1] = dist[source][coupon];
					pq.push({dist[v][coupon+1],{v,coupon+1}});
				}
			}
		}
	}
}

int main()
{
	int n,m,k;
	cin >> n >> m >> k;
	adj.resize(n+1);
	dist.resize(n+1,vector<ll>(k+1,INF));
	for(int i = 0;i<m;i++)
	{
		int u,v,w;
		cin >> u >> v >> w;
		adj[u].push_back({v,w});
		adj[v].push_back({u,w});
	}
	dijkstra(1,k);
	for(int i = 1;i<=n;i++)
	   cout << *min_element(dist[i].begin(),dist[i].end()) << " ";
	return 0;
}