#include <cstdio>
#include <cstdlib>
#include <cstring>
#define Load(x) \
	if (strcmp(mod, #x) == 0) fscanf(config,"%s", x)
char name[100];
char conf[100];
char data[100];
char cstd[100];
char cans[100];
char args[100];
char file[10][100];
char cmd[1000];
char mod[100];
FILE *rules,*rule,*config;
int Case;
inline void Compile(const char *s) {
	sprintf(cmd, "g++ %s.cpp %s -Wl,--stack=16777216 -o %s.exe", s, args, s);
	system(cmd);
}
inline void MakeData(int id) {
	sprintf(file[6],"%s%d.in",name,id);
	sprintf(file[7],"%s%d%s",name,id,cans);

	rule=fopen(file[1], "w");
	fgets(cmd,100,rules), fputs(cmd,rule);
	fclose(rule);
	puts(cmd);

	int tim=0,lim=100,res,flg=1;
	while(flg&&tim<lim) {
		++tim,flg=0;
		printf("Try #%d: \n",tim);
		sprintf(cmd, ".\\%s.exe < .\\%s > .\\%s", file[2],file[1],file[4]);
		res=system(cmd);
		if(res){
			flg=1;
			continue;
		}
		sprintf(cmd, ".\\%s.exe < .\\%s > .\\%s", file[3], file[4], file[5]);
		res=system(cmd);
		if(res)flg=2;
	}
	if(tim==lim)puts("[ERROR] TOO MANY TRIES!"),exit(1);
	remove(file[6]),rename(file[4],file[6]);
	remove(file[7]),rename(file[5],file[7]);
	system(cmd);
	remove(file[1]);
}
int main() {
	config=fopen("automake.config", "r");
	while (~fscanf(config,"%s", mod)) {
		Load(name);
		Load(conf);
		Load(data);
		Load(cstd);
		Load(cans);
		Load(args);
	}
	fclose(config);
	if (*name == 0 || *conf == 0 || *data == 0) {
		puts("[ERROR] Wrong Config");
		exit(1);
	}
	if (*cans == 0) memcpy(cans, ".ans", 4);

	sprintf(file[0],"%s%s",name,conf);
	sprintf(file[1],"%s.tmprule",name);
	sprintf(file[2],"%s%s",name,data);
	sprintf(file[3],"%s%s",name,cstd);
	sprintf(file[4],"%s.in",name);
	sprintf(file[5],"%s%s",name,cans);

	rules=fopen(file[0],"r");
	fscanf(rules,"%s", mod);
	if (strcmp(name, mod)) {
		puts("[ERROR] Name Not Equal");
		exit(2);
	}
	fscanf(rules,"%d\n", &Case);
	printf("[MESSAGE] Found %d Cases\n", Case);
	printf("[MESSAGE] Compile Start\n");
	Compile(file[2]);
	Compile(file[3]);
	printf("[MESSAGE] Compile Done!\n");

	for (int i = 1; i <= Case; ++i) {
		printf("[MESSAGE] Make Case #%d Start\n", i);
		MakeData(i);
		printf("[MESSAGE] Make Case #%d Done!\n", i);
	}
	fclose(rules);
}
