#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 
#include <conio.h>

//�ɤB �Nsystem("CLS")�אּprintf("\033[0;0H\033[2J") �įണ�� 

// �Y: @ ����:o �I�y��:.  ����: ? 
int i,j,S_idxb,S_idxs,A_idxb,A_idxs,len=2,END=0,RE=0,Hard=0;
int head=1;   //head �k1 ��2 �W4 �U5
char ground[9][9]; //���a 
int jd_list[81][2];  //�P�_���ڤU�@�B�n�����̨��A�]�����ڷ|���W�@�Ө��骺��m���A�ҥH�гy9*9 ��2d�}�C 

void color(short x){     //�C��ĪG 
	if ((x>=0) && (x<=15)){
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	}
	else{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
}

void op(){    //��X�禡 
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

int smaller(){          //O���Y�p 
	if (len<=2){
	    color(7); printf("���פ����A�L�k�Y�p\n");
	    Sleep(300);    //�Ȱ��B��0.3��A���|�����M�� 
		RE=1;
		return 0;
	}
	ground[jd_list[len-1][0]][jd_list[len-1][1]]='.';         //�N���ڥh�� 
	jd_list[len-1][0]=-1; jd_list[len-1][1]=-1;
	len-=1;
}

int ran_plus(int N,int try_time){       //���H����N���j�A������ڪ��[����V(�ӷs��m�����I�y��)�A�B�p�G�դF�W�L100���٥����\�h�[������ 
	if (try_time>100){
	    color(7); printf("�[������\n");
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

int longer(){   //���׶W�L15�ɫh����[�� 
	if (len>=15){
	    color(7); printf("���׹L���A�L�k�[��\n");
	    Sleep(300);
		RE=1;
		return 0;
	}
	ran_plus(rand()%4,1);
	return 0;
}

void swap(){    //�C���ʤ@�B�ɡA�b���ݥ[�W���ʪ��̷s��m�A�A���̫ܳe���A�ϷU�s����m�b�U�e���A�ϷU�ª���m�b�U�᭱ 
	int x,y,m,n;
	for(i=len-1;i>0;i--){
		x=jd_list[i][0]; y=jd_list[i][1]; m=jd_list[i-1][0]; n=jd_list[i-1][1];
		jd_list[i][0]=m; jd_list[i][1]=n;
		jd_list[i-1][0]=x; jd_list[i-1][1]=y;
	}
}

int ran_run(int N,int try_time){    //�P�W�z���H�����j�j���ۦP�A�A�Ω�Y�N�Q�D�Y���ɡA���X���{�װʧ@ 
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

int ran_walk(int N,int try_time){      //�P�W�z���H�����j�j���ۦP�A�A�Ω�S���¯ٮɪ��۵M���� 
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

int escape(){   //�P�_�n�ΰk���٬O�۵M���� 
	if (ground[S_idxb][S_idxs]=='?'){
		ran_run(rand()%4,1);
	}
	else{
		ran_walk(rand()%4,1);
	}
}

int move(char M){     //���ʪ��U���禡 
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
		color(7); printf("��J���~ �Э��s��J\n");
	    Sleep(300);
		RE=1;
		return 0;
	}
	if (abs(z-head)==1){     //�W�P�U ���P�k��n�t1�A�i�N�|��if�P�_���@�Y���@�� 
		color(7); printf("����˨���~ �Э��s��J\n");
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
		if ((len>=10) && (Hard==0)){     //���פj��10�Y�k�] 
		   Hard=1;
		   color(7); printf("\n�}�l�k�]~\n");
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
		   color(7); printf("\n�}�l�k�]~\n");
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
		   color(7); printf("\n�}�l�k�]~\n");
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
		   color(7); printf("\n�}�l�k�]~\n");
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
		printf("\033[H\033[2J");     //�N�e���M�šA�i�ϹC�����y�Z 
 	    color(7); printf("\n�ثe����:%d\n",len);
	    op();
	    color(7); printf("--------------------------");
 	    color(7); printf("\n�o��~\n");
 	    Sleep(400);
 		len+=1;
   		while(1){
			A_idxb=rand()%9;       //?��s�H����m 
			A_idxs=rand()%9;
			if (ground[A_idxb][A_idxs]=='.'){
		  	    break;
   			}
        }
		ground[A_idxb][A_idxs]='?';	
	}
	else{
		if (ground[S_idxb][S_idxs]=='o'){
			color(7); printf("\n�A��F QQ\n");
			END=1;
		}
	}
	ground[S_idxb][S_idxs]='@';
	jd_list[len-1][0]=S_idxb; jd_list[len-1][1]=S_idxs;
	swap();
}


int main(){        //�D�{�� 
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
	srand(time(NULL));  //�]�w�D�Y��l��m 
	S_idxb=rand()%8+1;
	S_idxs=rand()%8+1;
	while(1){;
 		A_idxb=rand()%9;
		A_idxs=rand()%9;
		if ((A_idxb!=S_idxb) && (A_idxs!=S_idxs) && (A_idxs!=S_idxs-1)){
			break;
		}
	}
	jd_list[0][0]=S_idxb; jd_list[0][1]=S_idxs;         //��}�l�ɨ���b���� 
	jd_list[1][0]=S_idxb; jd_list[1][1]=S_idxs-1;
	ground[S_idxb][S_idxs]='@';
	ground[S_idxb][S_idxs-1]='o';
	ground[A_idxb][A_idxs]='?';
	printf("<< �o�O�@��²�檺�g���D�C�� >>\n<< �ޱ��g���D�A�Y��ݸ��A�ùF��30��!!!>>\n\n\n");
	printf("*******************\n\n");
	printf("P.S: �o�O�g���D������M�Y:");
	color(2); printf("o@  ");
	color(7); printf("�o�O�A���ؼ�: ");
	color(4); printf("?\n\n");
	color(7);
	printf("�ާ@�覡 W:�W A:�� S:�U D:�k U:�Y�p(�u���Y�p����׳�2) O:�[��(�u��[������פp�󵥩�15�A�åB�����v�[������)\n\n");
	printf("�g���D�i���������(����̤W��|�^��̤U�A����̥���|�Ǩ�̥k�A�H������)\n\n");
	printf("�Y��");
	color(4); printf("?");
	color(7); printf("�i��o�@��(�[���@��)�A�åB�|���s��s");
	color(4); printf("?  ");
	color(7); printf("����׹F��10���A���ʮ�");
    color(4); printf("?");
    color(7); printf("�]�|�k�]�A�[�o!\n");
    printf("\n*******************\n\n\n");
    printf("�����N��}�l�C��:");
    getch();                           //���Ϋ�enter����J�k 
    printf("\033[H\033[2J");
    color(7); printf("\n�ثe����:%d\n",len);
	op();
	color(7); printf("--------------------------");
	while(1){
		color(7); printf("�п�J�z�����ʤ覡: ");
		ip=_getch();
		move(ip);
		if (len>=30){
			printf("\033[H\033[2J");;
			color(7); printf("\n�ثe����:%d\n",len);
		    ground[A_idxb][A_idxs]='.';
		    op();
			color(7); printf("\n�AĹ�F �n�δ�~\n");
			break;
		}
		if ((END==0) && (RE==0)){
			printf("\033[H\033[2J");
			color(7); printf("\n�ثe����:%d\n",len);
			op();
			color(7); printf("--------------------------");
		}
		else if ((END==0) && (RE==1)){     //��J���~���s��J 
			printf("--------------------------");
			RE=0;
		}
		else if (END==1){           //End Game 
			color(7); printf("\n�`����:%d\n",len);
			break;
		}
	}	
	return 0;
}
		
