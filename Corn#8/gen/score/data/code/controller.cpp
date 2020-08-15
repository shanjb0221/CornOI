#include<cstdlib>
#include<cstdio>
char name[100],cmd[100];
int n;
int main() {
	freopen("score.rules","r",stdin);
	scanf("%s%d\n",name,&n);
	printf("%d Cases\n",n);
	for(int i=1; i<=n; ++i) {
		gets(cmd);
		freopen("score.rule","w",stdout);
		puts(cmd);
		fclose(stdout);
		system("score.data");
		system("score.data2");
		system("score.std");
		sprintf(cmd,"ren score.in %s%d.in",name,i);
		system(cmd);
		sprintf(cmd,"ren score.out %s%d.out",name,i);
		system(cmd);
		fprintf(stderr,"Case %d Done!\n",i);
	}
}

