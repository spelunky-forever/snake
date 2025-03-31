#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 
#include <conio.h>

//補丁 將system("CLS")改為printf("\033[0;0H\033[2J") 效能提升 

// 頭: @ 身體:o 點座標:.  食物: ? 
int i,j,S_idxb,S_idxs,A_idxb,A_idxs,len=2,END=0,RE=0,Hard=0;
int head=1;   //head 右1 左2 上4 下5
char ground[9][9]; //場地 
int jd_list[81][2];  //判斷尾巴下一步要往哪裡走，因為尾巴會往上一個身體的位置走，所以創造9*9 的2d陣列 

void color(short x){     //顏色效果 
	if ((x>=0) && (x<=15)){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}

void op(){    //輸出函式 
	printf("\n");
	for(i=0;i<=8;i++){
		for(j=0;j<=8;j++){
			if (ground[i][j]=='.'){
				color(7); printf("%c",ground[i][j]);
			}
			else if ((ground[i][j]=='o') || (ground[i][j]=='@')){
				color(2); printf("%c",ground[i][j]);
			}
			else if (ground[i][j]=='?'){
				color(4); printf("%c",ground[i][j]);
			}
		}
		printf("\n");
	}	
}

int smaller(){          //O鍵縮小 
	if (len<=2){
	    color(7); printf("長度不足，無法縮小\n");
	    Sleep(300);    //暫停運做0.3秒，不會直接清除 
		RE=1;
		return 0;
	}
	ground[jd_list[len-1][0]][jd_list[len-1][1]]='.';         //將尾巴去除 
	jd_list[len-1][0]=-1; jd_list[len-1][1]=-1;
	len-=1;
}

int ran_plus(int N,int try_time){       //為隨機的N遞迴，控制尾巴的加長方向(該新位置應為點座標)，且如果試了超過100次還未成功則加長失敗 
	if (try_time>100){
	    color(7); printf("加長失敗\n");
	    Sleep(300);
		RE=1;
		return 0; 
	}
	if (N==0){
		if (jd_list[len-1][0]+1<=8){
  		    if (ground[jd_list[len-1][0]+1][jd_list[len-1][1]]=='.'){
  			    len+=1;
  			    jd_list[len-1][0]=jd_list[len-2][0]+1; jd_list[len-1][1]=jd_list[len-2][1];
  			    ground[jd_list[len-1][0]][jd_list[len-1][1]]='o';
  			    return 0;
	    	}
	    }
	    return ran_plus(rand()%4,try_time+1);
	}
	else if (N==1){
		if (jd_list[len-1][0]-1>=0){
  		    if (ground[jd_list[len-1][0]-1][jd_list[len-1][1]]=='.'){
  			    len+=1;
  			    jd_list[len-1][0]=jd_list[len-2][0]-1; jd_list[len-1][1]=jd_list[len-2][1];
  			    ground[jd_list[len-1][0]][jd_list[len-1][1]]='o';
  			    return 0;
	    	}
	    }
	    return ran_plus(rand()%4,try_time+1);
	}
	else if (N==2){
		if (jd_list[len-1][1]+1<=8){
  		    if (ground[jd_list[len-1][0]][jd_list[len-1][1]+1]=='.'){
  			    len+=1;
  			    jd_list[len-1][0]=jd_list[len-2][0]; jd_list[len-1][1]=jd_list[len-2][1]+1;
  			    ground[jd_list[len-1][0]][jd_list[len-1][1]]='o';
  			    return 0;
	    	}
	    }
	    return ran_plus(rand()%4,try_time+1);
	}
	else if (N==3){
		if (jd_list[len-1][1]-1>=0){
  		    if (ground[jd_list[len-1][0]][jd_list[len-1][1]-1]=='.'){
  			    len+=1;
  			    jd_list[len-1][0]=jd_list[len-2][0]; jd_list[len-1][1]=jd_list[len-2][1]-1;
  			    ground[jd_list[len-1][0]][jd_list[len-1][1]]='o';
  			    return 0;
	    	}
	    }
	    return ran_plus(rand()%4,try_time+1);
	}
}

int longer(){   //長度超過15時則不能加長 
	if (len>=15){
	    color(7); printf("長度過長，無法加長\n");
	    Sleep(300);
		RE=1;
		return 0;
	}
	ran_plus(rand()%4,1);
	return 0;
}

void swap(){    //每移動一步時，在尾端加上移動的最新位置，再移至最前面，使愈新的位置在愈前面，使愈舊的位置在愈後面 
	int x,y,m,n;
	for(i=len-1;i>0;i--){
		x=jd_list[i][0]; y=jd_list[i][1]; m=jd_list[i-1][0]; n=jd_list[i-1][1];
		jd_list[i][0]=m; jd_list[i][1]=n;
		jd_list[i-1][0]=x; jd_list[i-1][1]=y;
	}
}

int ran_run(int N,int try_time){    //與上述的隨機遞迴大略相同，適用於即將被蛇吃掉時，做出的閃避動作 
	if (try_time>100){
		return 0;
	}
	if (N==0){
		if (S_idxb+1<=8){
  		    if (ground[S_idxb+1][S_idxs]=='.'){
  			    ground[S_idxb+1][S_idxs]='?';
  			    ground[A_idxb][A_idxs]='.';
  			    A_idxb=S_idxb+1;
  			    return 0;
	    	}
	    }
	    return ran_run(rand()%4,try_time+1);
	}
	else if (N==1){
		if (S_idxb-1>=0){
  		    if (ground[S_idxb-1][S_idxs]=='.'){
  			    ground[S_idxb-1][S_idxs]='?';
  			    ground[A_idxb][A_idxs]='.';
  			    A_idxb=S_idxb-1;
  			    return 0;
	    	}
	    }
	    return ran_run(rand()%4,try_time+1);
	}
	else if (N==2){
		if (S_idxs+1<=8){
  		    if (ground[S_idxb][S_idxs+1]=='.'){
  			    ground[S_idxb][S_idxs+1]='?';
  			    ground[A_idxb][A_idxs]='.';
  			    A_idxs=S_idxs+1;
  			    return 0;
	    	}
	    }
	    return ran_run(rand()%4,try_time+1);
	}
	else if (N==3){
		if (S_idxs-1>=0){
  		    if (ground[S_idxb][S_idxs-1]=='.'){
  			    ground[S_idxb][S_idxs-1]='?';
  			    ground[A_idxb][A_idxs]='.';
  			    A_idxs=S_idxs-1;
  			    return 0;
	    	}
	    }
	    return ran_run(rand()%4,try_time+1);
	}
}

int ran_walk(int N,int try_time){      //與上述的隨機遞迴大略相同，適用於沒有威脅時的自然移動 
	if (try_time>100){
		return 0;
	}
	if (N==0){
		if (A_idxb+1<=8){
  		    if ((ground[A_idxb+1][A_idxs]=='.') && ((S_idxb!=A_idxb+1) || (S_idxs!=A_idxs))){
  		    	ground[A_idxb][A_idxs]='.';
  		    	A_idxb+=1;
  			    ground[A_idxb][A_idxs]='?';
  			    return 0;
	    	}
	    }
	    return ran_walk(rand()%4,try_time+1);
	}
	else if (N==1){
		if (A_idxb-1>=0){
  		    if ((ground[A_idxb-1][A_idxs]=='.') && ((S_idxb!=A_idxb-1) || (S_idxs!=A_idxs))){
  		    	ground[A_idxb][A_idxs]='.';
  		    	A_idxb-=1;
  			    ground[A_idxb][A_idxs]='?';
  			    return 0;
	    	}
	    }
	    return ran_walk(rand()%4,try_time+1);
	}
	else if (N==2){
		if (A_idxs+1<=8){
  		    if ((ground[A_idxb][A_idxs+1]=='.') && ((S_idxb!=A_idxb) || (S_idxs!=A_idxs+1))){
  		    	ground[A_idxb][A_idxs]='.';
  		    	A_idxs+=1;
  			    ground[A_idxb][A_idxs]='?';
  			    return 0;
	    	}
	    }
	    return ran_walk(rand()%4,try_time+1);
	}
	else if (N==3){
		if (A_idxs-1>=0){
  		    if ((ground[A_idxb][A_idxs-1]=='.') && ((S_idxb!=A_idxb) || (S_idxs!=A_idxs-1))){
  		    	ground[A_idxb][A_idxs]='.';
  		    	A_idxs-=1;
  			    ground[A_idxb][A_idxs]='?';
  			    return 0;
	    	}
	    }
	    return ran_walk(rand()%4,try_time+1);
	}
}

int escape(){   //判斷要用逃的還是自然移動 
	if (ground[S_idxb][S_idxs]=='?'){
		ran_run(rand()%4,1);
	}
	else{
		ran_walk(rand()%4,1);
	}
}

int move(char M){     //移動的各項函式 
	int z;
	if ((M=='W') || (M=='w')){
		z=4;
	}
	else if ((M=='A') || (M=='a')){
		z=2;
	}
	else if ((M=='S') || (M=='s')){
		z=5;
	} 
	else if ((M=='D') || (M=='d')){
		z=1;
	}
	else if ((M=='U') || (M=='u')){
		smaller();
		return 0;
	}
	else if ((M=='O') || (M=='o')){
		longer();
		return 0;
	}
	else{
		color(7); printf("輸入錯誤 請重新輸入\n");
	    Sleep(300);
		RE=1;
		return 0;
	}
	if (abs(z-head)==1){     //上與下 左與右恰好差1，可將四個if判斷式濃縮成一個 
		color(7); printf("不能倒車歐~ 請重新輸入\n");
		Sleep(300);
		RE=1;
		return 0;
	}
	ground[S_idxb][S_idxs]='o';
	ground[jd_list[len-1][0]][jd_list[len-1][1]]='.';
	if ((M=='W') || (M=='w')){
		S_idxb-=1;
		if (S_idxb==-1){
			S_idxb=8;
		}
		if ((len>=10) && (Hard==0)){     //長度大於10即逃跑 
		   Hard=1;
		   color(7); printf("\n開始逃跑~\n");
		   Sleep(300);
		   escape();
	    }
	    else if (Hard==1){
	    	escape();
		}
	}
	else if ((M=='A') || (M=='a')){
		S_idxs-=1;
		if (S_idxs==-1){
			S_idxs=8;
		}
		if ((len>=10) && (Hard==0)){
		   Hard=1;
		   color(7); printf("\n開始逃跑~\n");
		   Sleep(300);
		   escape();
	    }
	    else if (Hard==1){
	    	escape();
		}
	}
	else if ((M=='S') || (M=='s')){
		S_idxb+=1;
		if (S_idxb==9){
			S_idxb=0;
		}
		if ((len>=10) && (Hard==0)){
		   Hard=1;
		   color(7); printf("\n開始逃跑~\n");
		   Sleep(300);
		   escape();
	    }
	    else if (Hard==1){
	    	escape();
		}
	} 
	else if ((M=='D') || (M=='d')){
		S_idxs+=1;
		if (S_idxs==9){
			S_idxs=0;
		}
		if ((len>=10) && (Hard==0)){
		   Hard=1;
		   color(7); printf("\n開始逃跑~\n");
		   Sleep(300);
		   escape();
	    }
	    else if (Hard==1){
	    	escape();
		}
	}
	head=z;
	if (ground[S_idxb][S_idxs]=='?'){
 	    ground[jd_list[len-1][0]][jd_list[len-1][1]]='o';
 	    ground[S_idxb][S_idxs]='@';
		printf("\033[H\033[2J");     //將畫面清空，可使遊戲較流暢 
 	    color(7); printf("\n目前分數:%d\n",len);
	    op();
	    color(7); printf("--------------------------");
 	    color(7); printf("\n得分~\n");
 	    Sleep(400);
 		len+=1;
   		while(1){
			A_idxb=rand()%9;       //?刷新隨機位置 
			A_idxs=rand()%9;
			if (ground[A_idxb][A_idxs]=='.'){
		  	    break;
   			}
        }
		ground[A_idxb][A_idxs]='?';	
	}
	else{
		if (ground[S_idxb][S_idxs]=='o'){
			color(7); printf("\n你輸了 QQ\n");
			END=1;
		}
	}
	ground[S_idxb][S_idxs]='@';
	jd_list[len-1][0]=S_idxb; jd_list[len-1][1]=S_idxs;
	swap();
}


int main(){        //主程式 
	char ip;
	for (i=0;i<=8;i++){
		for(j=0;j<=8;j++){
			ground[i][j]='.';
		}
	}
	for(i=0;i<=80;i++){
		for(j=0;j<2;j++){
			jd_list[i][j]=-1;
		}
	}
	srand(time(NULL));  //設定蛇頭初始位置 
	S_idxb=rand()%8+1;
	S_idxs=rand()%8+1;
	while(1){;
 		A_idxb=rand()%9;
		A_idxs=rand()%9;
		if ((A_idxb!=S_idxb) && (A_idxs!=S_idxs) && (A_idxs!=S_idxs-1)){
			break;
		}
	}
	jd_list[0][0]=S_idxb; jd_list[0][1]=S_idxs;         //剛開始時身體在左側 
	jd_list[1][0]=S_idxb; jd_list[1][1]=S_idxs-1;
	ground[S_idxb][S_idxs]='@';
	ground[S_idxb][S_idxs-1]='o';
	ground[A_idxb][A_idxs]='?';
	printf("<< 這是一個簡單的貪食蛇遊戲 >>\n<< 操控貪食蛇，吃到問號，並達到30分!!!>>\n\n\n");
	printf("*******************\n\n");
	printf("P.S: 這是貪食蛇的身體和頭:");
	color(2); printf("o@  ");
	color(7); printf("這是你的目標: ");
	color(4); printf("?\n\n");
	color(7);
	printf("操作方式 W:上 A:左 S:下 D:右 U:縮小(只能縮小到長度剩2) O:加長(只能加長到長度小於等於15，並且有機率加長失敗)\n\n");
	printf("貪食蛇可穿梭牆壁兩端(走到最上方會回到最下，走到最左方會傳到最右，以此類推)\n\n");
	printf("吃到");
	color(4); printf("?");
	color(7); printf("可獲得一分(加長一格)，並且會重新刷新");
	color(4); printf("?  ");
	color(7); printf("當長度達到10格後，移動時");
    color(4); printf("?");
    color(7); printf("也會逃跑，加油!\n");
    printf("\n*******************\n\n\n");
    printf("按任意鍵開始遊戲:");
    getch();                           //不用按enter的輸入法 
    printf("\033[H\033[2J");
    color(7); printf("\n目前分數:%d\n",len);
	op();
	color(7); printf("--------------------------");
	while(1){
		color(7); printf("請輸入您的移動方式: ");
		ip=_getch();
		move(ip);
		if (len>=30){
			printf("\033[H\033[2J");;
			color(7); printf("\n目前分數:%d\n",len);
		    ground[A_idxb][A_idxs]='.';
		    op();
			color(7); printf("\n你贏了 好棒棒~\n");
			break;
		}
		if ((END==0) && (RE==0)){
			printf("\033[H\033[2J");
			color(7); printf("\n目前分數:%d\n",len);
			op();
			color(7); printf("--------------------------");
		}
		else if ((END==0) && (RE==1)){     //輸入錯誤重新輸入 
			printf("--------------------------");
			RE=0;
		}
		else if (END==1){           //End Game 
			color(7); printf("\n總分為:%d\n",len);
			break;
		}
	}	
	return 0;
}
		
