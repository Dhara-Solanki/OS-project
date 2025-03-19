#include<stdio.h>
FILE *f,*op;
void LRTF(int n,int at[],int brust[])
{
int total=0,bt[n];
double tat=0,wt=0;
for(int i=0;i<n;i++)bt[i]=brust[i],total+=bt[i];
int ans[total+1];
for(int i=n-1;i>=0;i--)if(at[i]==0)ans[0]=i;
fprintf(op,"%s","Gantt chart : ");
for(int i=1;i<=total;i++)
{
int maxt=bt[ans[i-1]],cr=ans[i-1];
for(int j=0;j<n;j++)
{
if(bt[j]>maxt && at[j]<i)maxt=bt[j],cr=j;
}
ans[i]=cr;
bt[cr]--;
if(bt[cr]==0)tat+=i-at[cr],wt+=(i-at[cr])-brust[cr];
fprintf(op,"%d ",ans[i]);
}
fprintf(op,"%s","\n");
fprintf(op,"%s%f%s","Average turn aroud time : ",tat/n,"\n");
fprintf(op,"%s%f%s","Average waiting time : ",wt/n,"\n");
}
void PS(int n,int at[],int bt[]){
int p[n],temp[n],tat[n],wt[n];
for (int i = 0; i < n; i++)
{
temp[i] = bt[i];
}
for(int i=0;i<n;i++){
fscanf(f,"%d",&p[i]);
}
int cnt = 0, t = 0, Total_wt = 0, Total_tat = 0;
fprintf(op,"%s","Gantt Chart : ");
for(t;cnt<n;t++){
int mi_p = n+1;
int ind=-1;
for(int i=0;i<n;i++){
if(p[i]<mi_p && at[i]<=t && bt[i]>0){
mi_p=p[i];
ind = i;
}
}
if(ind==-1) {
fprintf(op,"%s","- ");
continue;
}
bt[ind]-=1;
fprintf(op,"%d ",ind);
if(bt[ind]==0){
cnt++;
tat[ind]=t+1-at[ind];
wt[ind]=tat[ind]-temp[ind];
Total_tat += tat[ind];
Total_wt += wt[ind];
}
}
float avg_tat = (float)Total_tat/n;
float avg_wt = (float)Total_wt/n;
fprintf(op,"%s","\n");
fprintf(op,"%s %f %s", "Average Turn-Around Time : ",avg_tat,"\n");
fprintf(op,"%s %f %s", "Average Waiting Time : ",avg_wt,"\n");
}
int max(int a,int b){
if(a>=b)return a;
return b;
}
void SRTF(int n,int at[],int bt[]){
int temp[n], tat[n], wt[n];
int mx = 0;
for (int i = 0; i < n; i++)
{
mx = max(mx, at[i]);
}
for (int i = 0; i < n; i++)
{
temp[i] = bt[i];
}
int cnt = 0, t = 0, Total_wt = 0, Total_tat = 0;
fprintf(op, "%s", "Gantt Chart : ");
int id = -1;
int mi = 1000000000, ind = -1;
for (t; cnt < n; t++)
{
if (id != -1)
mi = bt[id];
else
mi = 100000000;
for (int j = 0; j < n; j++)
{
if (bt[j] > 0 && at[j] <= t && bt[j] < mi)
{
ind = j;
mi = bt[j];
}
}
if (ind == -1 && id == -1)
{
fprintf(op, "%s", "- ");
continue;
}
if (ind != -1)
id = ind;
bt[id] -= 1;
fprintf(op, "%d ", id); 
if (bt[id] == 0)
{
cnt++;
tat[id] = t + 1 - at[id];
wt[id] = tat[id] - temp[id];
Total_tat += tat[id];
Total_wt += wt[id];
id = -1;
}
}
float avg_tat = (float)Total_tat / n;
float avg_wt = (float)Total_wt / n;
fprintf(op, "%s", "\n");
fprintf(op, "%s %f %s", "Average Turn-Around Time : ", avg_tat, "\n");
fprintf(op, "%s %f %s", "Average Waiting Time : ", avg_wt, "\n");
}
void RR(int n,int at[],int bt[]){
int remaining_time[n], turn_around_time[n], waiting_time[n];
for (int i = 0; i < n; i++)
{
remaining_time[i] = bt[i];
}
/* necessary variables */
int cnt = 0, total_wt = 0, total_at = 0, time_quantum = 1, counter, i, time = 0;
float average_wt = 0, average_tt = 0;
counter = n;
/* Necessary condition for the gantt chart*/
int ind = 0;
int ans[100];
for (cnt = 0, i = 0; counter != 0;)
{
if (remaining_time[i] <= time_quantum && remaining_time[i] > 0)
{
cnt = cnt + remaining_time[i];
remaining_time[i] = 0;
ans[ind] = i;
ind++;
counter--;
total_wt = total_wt + cnt - at[i] - bt[i];
total_at = total_at + cnt - at[i];
}
else if (remaining_time[i] > 0)
{
ans[ind] = i;
ind++;
remaining_time[i] = remaining_time[i] - time_quantum;
cnt = cnt + time_quantum;
}
if (i == n - 1)
{
i = 0;
}
else if (at[i + 1] <= cnt)
{
i++;
}
else
{
i = 0;
}
}
/* Here is the gantt chart */
fprintf(op, "Gantt chart :\n");
for (i = 0; i < ind; i++)
{
fprintf(op, "%d ", ans[i]);
}
average_wt = (float)total_wt / n;
average_tt = (float)total_at / n;
fprintf(op, "%s", "\n");
/* writing Average timings in the output file */
fprintf(op, "%s %f %s", "Average_Turn-around_Time is :", average_tt, "\n");
fprintf(op, "%s %f %s", "Average_Waiting_Time is :", average_wt, "\n");
}
void SJF(int n,int at[],int brust[])
{
int total=0,bt[n];
double wt=0,tat=0;
for(int i=0;i<n;i++)bt[i]=brust[i],total+=bt[i];
int ans[total+1];
for(int i=n-1;i>=0;i--)if(at[i]==0)ans[0]=i;
for(int i=1;i<=total;i++)
{
int cr=ans[i-1],mn=brust[cr];
for(int j=0;j<n;j++)
{
if(at[j]<i && brust[j]<mn)mn=brust[j],cr=j;
}
ans[i]=cr;
fprintf(op,"%d ",ans[i]);
bt[cr]--;
if(bt[cr]==0)
{
tat+=(i-at[cr]);
wt+=(i-at[cr]-brust[cr]);
brust[cr]=1e9;
}
}
fprintf(op,"%s","Average turn around time : ");
fprintf(op,"%lf",tat/n);
fprintf(op,"%s","\nAverage waiting time :");
fprintf(op,"%lf",wt/n);
}
void FCFS(int n,int at[],int bt[])
{
int cnt=0,done[n],totalturn=0,totalwait=0,pnt=0;
int finishtime[n],last[n],h=0,turnaround[n],waitingtime[n];
for(int i=0;i<n;i++)
{
done[i]=0;
} 
fprintf(op,"%s","Gantt Chart : ");
for(int i=0;i<n;i++)
{
int possi=-1;
int temp=at[i];
int turn=-1;
for(int j=0;j<n;j++)
{
if(at[j]<=temp && done[j]==0)
{
temp=at[j];
possi=j;
}
}
turn=possi;
done[possi]=1;
if(possi==-1)
{
int left=-1;
for(int l=0;l<n;l++)
{
if(done[l]==0)
{
left=l;
}
}
for(int m=0;m<bt[left];m++)
{
fprintf(op,"%d ",left);
}
turn=left;
}
else{
for(int k=0;k<bt[possi];k++)
{
fprintf(op,"%d ",possi);
}
}
last[h]=turn;
h++;
//printf("%d",turn);
//printf("\n");
if(h==1)
{
finishtime[turn]=bt[turn];
}
else{
finishtime[turn]=finishtime[last[pnt]]+bt[turn];
pnt+=1;
}
//printf("%d",finishtime[turn]);
//printf("\n");
}
for(int i=0;i<n;i++)
{
turnaround[i]=finishtime[i]-at[i];
totalturn+= turnaround[i];
}
for(int i=0;i<n;i++)
{
waitingtime[i]=turnaround[i]-bt[i];
totalwait+= waitingtime[i];
}
float avg_tat = (float)totalturn/n;
float avg_wt = (float)totalwait/n; 
fprintf(op,"%s","\n");
fprintf(op,"%s %f %s", "Average Turn-Around Time : ",avg_tat,"\n");
fprintf(op,"%s %f %s", "Average Waiting Time : ",avg_wt,"\n");
}
int main()
{
f=fopen("input1.txt","r");
op=fopen("output1.txt","w");
int n,type=-1;
fscanf(f,"%d",&type);
fscanf(f,"%d",&n);
int at[n],bt[n];
for(int i=0;i<n;i++){
fscanf(f,"%d",&at[i]);
}
for(int i=0;i<n;i++){
fscanf(f,"%d",&bt[i]);
}
// call function according to type 
// type shoud be in input file order : type,n,at,bt,priority.
// priority scan should be done in it's personal fuction 
switch(type)
{
case 0:
FCFS(n,at,bt);
break;
case 1:
SJF(n,at,bt);
break;
case 2:
RR(n,at,bt);
break;
case 3:
PS(n,at,bt);
break;
case 4:
SRTF(n,at,bt);
break;
case 5:
LRTF(n,at,bt);
break;
default :
fprintf(op,"%s","Enter valid choice !!\n");
}
fclose(f);
fclose(op);
}