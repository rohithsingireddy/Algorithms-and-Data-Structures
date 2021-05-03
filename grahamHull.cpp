#include<bits/stdc++.h>
const int MAX {10000000};
const long som = std::pow(10,9);

struct point{
	int x=0,y=0;
	point(int a=0, int b=0){x=a;y=b;}
	void operator=(point b){
		x = b.x;
		y = b.y;
	}
	bool operator<(point &b) const{
		if(x!=b.x)
			return x< b.x;
		else
			return y<b.y;
	}
};

inline int polar_angle(point &a, point &b){
	return -(a.x-b.x)/(a.y-b.y);
}

inline int direction(point i, point j, point k)
{
	return (k.x-i.x)*(j.y-i.y) - (k.y-i.y)*(j.x-i.x);
}

point op(MAX,MAX); //origin point
struct comparator{
	bool operator()(point &a, point &b){
		return polar_angle(op, a) < polar_angle(op, b);
	}
};

std::vector<point> graham_scan(std::vector<point> p){
	
	/*point temp(MAX,MAX);
	int index;

	for(int i=0;i<p.size();i++)
	{
		if(temp.y > p[i].y){
			temp = p[i];
			index = i;
		}
		else if(temp.y == p[i].y)
		{
			if(temp.x > p[i].x){
				temp = p[i];
				index = i;
			}
		}
	}
	op = temp;
	p.erase(p.begin()+index);
	std::sort(p.begin(), p.end(), comparator());
	std::vector<int> t;
	for(int i=p.size()-1;i>=1;i--)
		if(polar_angle(op,p[i])==polar_angle(op,p[i-1]))
			t.push_back(i-1);
	for(auto i:t)
		p.erase(p.begin()+i);
	std::vector<point> result;
	result.push_back(op);
	result.push_back(p[0]);
	result.push_back(p[1]);
	int k = 1;
	for(int i=2;i<p.size();i++)
	{
		while(direction(result[k-1], result[k], p[i]) <= 0){
			result.pop_back();
			k--;
		}
		result.push_back(p[i]);
	}
	//std::cout<<temp.x<<temp.y;
	return result;
	*/
	if(p.size()<=3) return p;
	int n = p.size(),k=0;
	std::sort(p.begin(), p.end());
	std::vector<point> h(2*n);
	for(int i=0;i<n;i++)
	{
		while(k>=2  && direction(h[k-2],h[k-1],p[i])<=0)
			k--;
		h[k++] = p[i];
	}
	for(int i = n-1,t=k+1;i>0;i--)
	{
		while(k>=t && direction(h[k-2],h[k-1],p[i-1])<=0)
			k--;
		h[k++] = p[i-1];
	}
	h.resize(k-1);
	return h;

}


int main(){
	int n;
	std::cin>>n;
	std::vector<point> p(n);
	for(int i=0;i<n;i++)
	{
		int a, b;
		std::cin>>a>>b;
		p[i].x = a;
		p[i].y = b;
	}
	std::cout<<'\n';
	for(auto i:graham_scan(p))
		std::cout<<i.x<<' '<<i.y<<'\n';
}