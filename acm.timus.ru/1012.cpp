#include <stdio.h>
#define N 5000
struct bigint
{
 char D[N];
 bigint()
 {
  for(int i = 0; i < N; i++)
  {
   D[i] = 0;
  }
 }
 
 void assign(int a)
 {
  int count = 0;
  if( a == 0)
  {
   D[count++] = 0;
  }
  while(a != 0)
  {
   D[count++] = a%10;
   a/=10;
  }
 }
 void print()
 {
  int len = 0;
  for(int i = N-1; i >= 0; i--)
   if(D[i] != 0)
   {
    len = i;
    break;
   }
  for(int i = len; i >= 0; i--)
  {
   printf("%d",D[i]);
  }
 }
 
 void operator += (bigint A)
 {
  int carry = 0,tmp;
  for(int i = 0 ; i < N; i++)
  {
   tmp = (D[i] + A.D[i] + carry) / 10;
   D[i] = (D[i] + A.D[i] + carry) % 10;
   carry = tmp;
  }
 }
 
 void operator *= (int A)
 {
  int carry = 0,tmp;
  for(int i = 0 ; i < N; i++)
  {
   tmp = (D[i]*A + carry) / 10;
   D[i] = (D[i]*A + carry) % 10;
   carry = tmp;
  }
 }
 bigint operator + (bigint A)
 {
  bigint res = *this;
  res += A;
  return res;
 }

 bigint operator * (int A)
 {
  bigint res = *this;
  res *= A;
  return res;
 }
};
void main()
{
 int n,k;
 scanf("%d %d",&n, &k);
 
 bigint a,b,c;
 a.assign(1);
 b.assign(k-1);
 
 for(int i = 2; i <= n; i++)
 {
  c = (a+b)*(k-1);
  a = b;
  b = c;
 }
 b.print();
}
