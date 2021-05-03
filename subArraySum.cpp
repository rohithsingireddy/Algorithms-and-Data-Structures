#include<bits/stdc++.h>
using namespace std;
const int MAX{100000};

struct subArray{
	int low;
	int high;
	int sum;
	void set(int l, int h, int s)
	{
		low=l;
		high=h;
		sum=s;
	}
	const bool operator>=(const subArray&b) const
	{
		return sum>=b.sum;
	}
};

subArray max_crossingSum(vector<int> a, int low, int mid, int high)
{
	int left_sum=-MAX, right_sum = -MAX;
	int max_left,max_right;
	int i=mid, j=mid+1;
	int sum =0;
	//subArray left_array, right_array;
	for(i;i>=0;i--)
	{
		sum += a[i];
		if(sum>left_sum)
		{
			left_sum = sum;
			max_left = i;
		}
		//i--;
	}
	sum = 0;
	for(j;j<=high;j++)
	{
		sum += a[j];
		if(sum>right_sum)
		{
			right_sum = sum;
			max_right = j;
		}
	}
	subArray res;
	res.set(max_left,max_right,left_sum+right_sum);
	return res;
}

subArray maxSubarray(vector<int> a, int low, int high)
{
	subArray res;
	if(low==high)
		res.set(low,high,a[low]);
	else
	{
		int mid = (low+high)/2;
		subArray temp_left, temp_right, temp_cross;
		temp_left  = maxSubarray(a,low,mid);
		temp_right = maxSubarray(a,mid+1,high);
		temp_cross = max_crossingSum(a, low, mid, high);
		if(temp_left>=temp_right && temp_left>= temp_cross)
			res = temp_left;
		else if (temp_right>=temp_left && temp_right>=temp_cross)
			res = temp_right;
		else
			res = temp_cross;

	}
	return res;
}
//Kadane's Algorithm
subArray linear_maxSubarray(vector<int> a)
{
	subArray res;
	int sum=-MAX,max_sum=-MAX;
	int n = a.size();
	int curLow, curHigh;
	for(int i=0;i<n;i++)
	{
		curHigh = i;
		if(sum>0)
			sum += a[i];
		else{
			sum = a[i];
			curLow = i;
		}
		if(sum>max_sum){
			max_sum = sum;
			res.set(curLow,curHigh,sum);
		}
	}

	return res;
}	

subArray brute_maxSubarray(vector<int> a)
{
	int n = a.size();
	subArray res;
	int max_sum = -MAX;
	for(int i=0;i<n;i++){
		int sum = 0;
		for(int j=i;j<n;j++)
		{
			sum += a[j];
			if(sum>max_sum)
			{
				max_sum = sum;
				res.set(i,j,max_sum);
			}
		}
	}
	return res;

}

int main()
{
	vector<int> a{-6,-1,-4,-3,-4};
	auto temp = linear_maxSubarray(a);
	cout<<temp.low<<' '<<temp.high<<' '<<temp.sum;
}

