#include<cstdio>
#include<cstring>
#define maxa 50010
#define maxn 50010
int r[maxn],w[maxa],sa2[maxn],r2[maxn],sa[maxn];
char s[maxn];
int n,k,n1,m;
void input()
{
	scanf("%s",s);
	n=strlen(s);
	
	for(int i=0;i<n;++i) r[i]=s[i];
	r[n]=-1;
	m=maxa;//由于r在计算的过程中可能会达到n的级别，但在小数ju的时候，状态的数量可能没有n，但是r[i]会超过n
	//的值所以最好就设最大。
}
void cal_sa()
{
	int i,j,p;
	memset(w,0,sizeof(w));
	for(i=0;i<n;++i) w[r[i]]++;
	for(i=1;i<m;++i) w[i]+=w[i-1];
	for(i=0;i<n;++i) sa[--w[r[i]]]=i;
	
	for(j=1;j<n;j*=2)
	{
		for(i=n-j,p=0;i<n;++i) sa2[p++]=i;//利用上一步求出的sa直接对第二关键字进行排序
		for(i=0;i<n;++i) if(sa[i]>=j) sa2[p++]=sa[i]-j;
		//
		memset(w,0,sizeof(w));
		for(i=0;i<n;++i) w[r[i]]++;
		for(i=1;i<m;++i) w[i]+=w[i-1];
		for(i=n-1;i>=0;--i) r2[sa2[i]]=--w[r[sa2[i]]]; //对第一关键字进行排序，注意要倒着算
		//
		for(i=0;i<n;++i) sa[r2[i]]=i;//计算当前的sa值
		for(i=0,p=0;i<n-1;++i)  //去除重复的r值，防止把本来相同的变为了不同，造成下一步计算的时候出错
			if(r[sa[i]]==r[sa[i+1]] && r[sa[i]+j]==r[sa[i+1]+j])  r2[sa[i]]=p;
			else r2[sa[i]]=p++;
		r2[sa[n-1]]=p;//对最后一个r 赋值
		memcpy(r,r2,sizeof(int)*n);
	}
}
int height[maxn];
void cal_height()
{
	int k,i,j;
	int rank[maxn];	
	for(i=0;i<n;++i) rank[sa[i]]=i;//由于此时的r会有相同的，这样会影响height的计算
	for(k=0,i=0;i<n;i++)  
	if(rank[i]>0){
		if(k>0) k--;
		for(j=sa[rank[i]-1];s[i+k]==s[j+k];++k) ;
		height[rank[i]]=k;
	}
}
