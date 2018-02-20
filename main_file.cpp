///*
#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;

//char *color;
char poss_moves[15][3];				//list
char mr[5],mc[2],color[6]="white",move1[5];
int m=0,i,j;
int br=0,bb=0,bn=0,bp=0,wr=0,wb=0,wn=0,wp=0;

struct bd{
	char piece[7],block_color[6],piece_color[6];
	char p[7];
	int type_no=1;
	int block_r,block_c;
	/*
	 * piece = rook
	 * block_color = white
	 * piece_color = black
	 * block_r,block_c= 77
	 * type_no = 3
	 */
}board[8][8],temp;

void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}

char* itoaa(int num, char* str, int base)
{
	// Implementation of itoa()
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}

void print_details(int *i,int *j){
	cout<<endl<<"******************************************************************";
	cout<<endl<<"block_no = "<<board[*i][*j].block_r<<" "<<board[*i][*j].block_c;
	cout<<endl<<"piece = "<<board[*i][*j].piece;
	cout<<endl<<"block_color  = "<<board[*i][*j].block_color;
	cout<<endl<<"piece_color = "<<board[*i][*j].piece_color;
	cout<<endl<<"type_no = "<<board[*i][*j].type_no;
	return;
	}

void fill_structure(char move[],int *i,int *j){
	/*
	 * moves are passed from "state.dat" file one by one as wr(i.e. white rook)
	 * and they are filled in the structure[i][j]
	 */
	board[*i][*j].block_r=*i;
	board[*i][*j].block_c=*j;
	if (move[0] == '.'){
		//initialize blank spaces
		strcpy(board[*i][*j].piece_color,".");
		strcpy(board[*i][*j].piece," ");
		strcpy(board[*i][*j].p," ");
	}
	else{
		if(move[0]=='w'){
			strcpy(board[*i][*j].piece_color,"white");
		}
		else{
			strcpy(board[*i][*j].piece_color,"black");
		}
			//deciding piece
			switch(move[1]){
			case 'r':
				strcpy(board[*i][*j].piece,"rook");
				strcpy(board[*i][*j].p,"rook");
				if(strcmp(board[*i][*j].piece_color,"white")){
					board[*i][*j].type_no=++wr;
				}
				else{
					board[*i][*j].type_no=++br;
				}
				break;
			case 'n':
				strcpy(board[*i][*j].piece,"horse");
				strcpy(board[*i][*j].p,"horse");
				if(strcmp(board[*i][*j].piece_color,"white")){
					board[*i][*j].type_no=++wn;
				}
				else{
					board[*i][*j].type_no=++bn;
				}
				break;
			case 'b':
				strcpy(board[*i][*j].piece,"bishop");
				strcpy(board[*i][*j].p,"bishop");
				if(strcmp(board[*i][*j].piece_color,"white")){
					board[*i][*j].type_no=++wb;
				}
				else{
					board[*i][*j].type_no=++bb;
				}
				break;
			case 'q':
				strcpy(board[*i][*j].piece,"queen");
				strcpy(board[*i][*j].p,"queen");
				break;
			case 'k':
				strcpy(board[*i][*j].piece,"king");
				strcpy(board[*i][*j].p,"king");
				break;
			case 'p':
				strcpy(board[*i][*j].piece,"pawn");
				strcpy(board[*i][*j].p,"pawn");
				if(strcmp(board[*i][*j].piece_color,"white")){
					board[*i][*j].type_no=++wp;
				}
				else{
					board[*i][*j].type_no=++bp;
				}
				break;
			}
	}
	if (*i%2 == 0){
		if (*j%2==0){
			strcpy(board[*i][*j].block_color,"white");
		}
		else{
			strcpy(board[*i][*j].block_color,"black");
		}
	}
	else{
		if (*j%2==0){
					strcpy(board[*i][*j].block_color,"black");
		}
		else{
			strcpy(board[*i][*j].block_color,"white");
		}
	}
//	print_details(i,j);
	return;
}

void draw_board(){
	/*
	 * read the board structure.
	 */
	int c=8;
	cout<<endl<<"*************************************************BOARD*****************************************************"<<endl<<endl;

	cout<<"\t _______________________________________________________________________"<<endl<<"\t|\t\t\t\t\t\t\t\t\t|";
	for(int i=0;i<8;i++){
		cout<<endl<<c-i<<"\t|";
		for(int j=0;j<8;j++){
			cout<<"\t"<<board[i][j].piece_color[0]<<board[i][j].piece[0];
		}
		cout<<"\t|"<<endl<<"\t|\t\t\t\t\t\t\t\t\t|";
	}
	cout<<endl<<"\t|_______________________________________________________________________|"<<endl;
	cout<<endl<<"\t\ta\tb\tc\td\te\tf\tg\th"<<endl;
}

void init(int resume=0){
	cout<<endl<<"in init";
	char move[3];
		int i=0,j=0;
		if (resume==0){
			ifstream fin("state.dat",ios::in);
			for(int m=0;m<64;m++){
						fin.read((char*)&move, sizeof(move));
						fill_structure(move,&i,&j);
						if(j<7){
							j++;
						}
						else{
							j=0;
							i++;
						}
					}
					fin.close();
		}
		else {
			ifstream fin1("resume.dat",ios::in);
			for(int m=0;m<64;m++){
						fin1.read((char*)&move, sizeof(move));
						fill_structure(move,&i,&j);
						if(j<7){
							j++;
						}
						else{
							j=0;
							i++;
						}
					}
					fin1.close();
		}
		draw_board();
}

void close1(){
	ofstream fout;
	char move1[8],move[3];
	fout.open("resume.dat",ios::out);
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(strcmp(board[i][j].piece_color,".")==0){
				move[0]='.';
				move[1]='.';
				move[2]='\n';
				fout<<move;
				continue;
			}
			else{
				move[0]=board[i][j].piece_color[0];
				if (board[i][j].piece[0] == 'h')
					move[1]='n';
				else move[1]=board[i][j].piece[0];
				move[2]='\n';
				fout<<move;
			}

		}
	}
	fout.close();
}

void get_board_move(char u_move[],char * b_from,char *b_to){

	int ifb1,ifb2,itb1,itb2;
	char cfb1[1],cfb2[1],ctb1[1],ctb2[1];

	//conversion of moves
	ifb1 = (7 - (u_move[1]-49)) * 10;
	ifb2 = (u_move[0] - 97);
	itb1 = (7 - (u_move[4]-49)) * 10;
	itb2 = (u_move[3] - 97);

	//int to char conv.
	itoaa(ifb1,cfb1,10);
	itoaa(ifb2,cfb2,10);
	itoaa(itb1,ctb1,10);
	itoaa(itb2,ctb2,10);

	//combining that chars to b_from and b_to
	strcpy(b_from,cfb1);
	strcat(b_from,cfb2);
	strcpy(b_to,ctb1);
	strcat(b_to,ctb2);

}

void get_play_moves(char movv[]){
	// convert char numbers to char characters as it was input

	//    a b c d e f g h 		-row given	//even
	//    0 1 2 3 4 5 6 7		-expected

	//    8 7 6 5 4 3 2 1		-column given	//odd
	//    0 1 2 3 4 5 6 7		-expected

//	c7-c5 = 12-32
	char move[5];
	move[0]=movv[1];
	move[1]=movv[0];

			switch(move[0]){
				case '0':
					move1[0]='a';
					break;
				case '1':
					move1[0]='b';
					break;
				case '2':
					move1[0]='c';
					break;
				case '3':
					move1[0]='d';
					break;
				case '4':
					move1[0]='e';
					break;
				case '5':
					move1[0]='f';
					break;
				case '6':
					move1[0]='g';
					break;
				case '7':
					move1[0]='h';
					break;
				default:
					cout<<"error1";
			}
			switch(move[1]){
				case '0':
					move1[1]='8';
					break;
				case '1':
					move1[1]='7';
					break;
				case '2':
					move1[1]='6';
					break;
				case '3':
					move1[1]='5';
					break;
				case '4':
					move1[1]='4';
					break;
				case '5':
					move1[1]='3';
					break;
				case '6':
					move1[1]='2';
					break;
				case '7':
					move1[1]='1';
					break;
				default:
					cout<<"error2";
			}
		}

void insert_move(int *row,int *col,int x=0,int y=0){
	//convert and insert moves in list
//	cout<<endl<<"x,y = "<<x<<","<<y;
//	cout<<endl<<"row,col = "<<*row<<","<<*col;
	   itoaa(*row+x,mr,10);
	   itoaa(*col+y,mc,10);
	   strcat(mr,mc);
	   strcpy(poss_moves[m],mr);		//inserting in 2d array
//	   cout<<endl<<"pos: "<<poss_moves[m];
	   m++;
}

void king_moves(int *row,int *col){
	*row -= 1;
	*col -= 1;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if (((*row+i)<8 && (*row+i)>0) && (((*col+j)>0 && (*col+j)<8))){
				if((strcmp(board[*row+i][*col+j].piece_color,".")==0) or (strcmp(board[*row+i][*col+j].piece_color,color)==abs(21))){ //use piece_color beacuse piece = " "
					//enemy color or blank space
					if ((*row+1==*row+i)&&(*col+1==*col+j)){		//avoiding original position
						continue;
					}
					insert_move(row,col,i,j);
					cout<<endl<<"i,j = "<<i<<j;
				}
			}
	    }
	}
}

void rook_moves(int *row,int *col){
	bool f1=false;
	bool f2=false;
	bool f3=false;
	bool f4=false;
	for(i=1;i<8;i++){
        if (((*row+i < 8) && (((*col) < 8)&&(*col>=0))) && (f1==false)){
	        if (strcmp(board[*row+i][*col].piece_color,".")==0){
		        insert_move(row,col,i,0);
		        cout<<endl<<"1";
	        }
		    else if((strcmp(board[*row+i][*col].piece_color,color)==abs(21))){	//enemy color
		        insert_move(row,col,i,0);
		        f1=true;
		    }
		    else if(strcmp(board[*row+i][*col].piece_color,color)==0){
		    	cout<<endl<<"3";
		    	f1=true;
		    }
        }

        if ((((*row< 8)&&(*row>=0)) && ((*col+i) < 8)) && (f2==false)){
	        if (strcmp(board[*row][*col+i].piece_color,".")==0){
		        insert_move(row,col,0,i);
	        }
		    else if((strcmp(board[*row][*col+i].piece_color,color)==abs(21))){	//enemy color
		        insert_move(row,col,0,i);
		        f2=true;
		    }
		    else if(strcmp(board[*row][*col+i].piece_color,color)==0){
		        f2=true;
		    }
        }

        if ((((*row < 8)&&(*row >= 0)) && ((*col-i) >= 0)) && (f3==false)){
	        if (strcmp(board[*row][*col-i].piece_color,".")==0){
		        insert_move(row,col,0,-i);
	        }
		    else if((strcmp(board[*row][*col-i].piece_color,color)==abs(21))){	//enemy color
		        insert_move(row,col,0,-i);
		        f3=true;
		    }
		    else if(strcmp(board[*row][*col-i].piece_color,color)==0){
		        f3=true;
		    }
        }

        if (((*row-i >= 0) && (((*col) < 8)&&(*col >=0))) && (f4==false)){
	        if (strcmp(board[*row-i][*col].piece_color,".")==0){
		        insert_move(row,col,-i,0);
	        }
		    else if((strcmp(board[*row-i][*col].piece_color,color)==abs(21))){	//enemy color
		        insert_move(row,col,-i,0);
		        f4=true;
		    }
		    else if(strcmp(board[*row-i][*col].piece_color,color)==0){
		        f4=true;
		    }
        }
	}
}

void bishop_moves(int *row,int *col){
	bool f5=false;
	bool f6=false;
	bool f7=false;
	bool f8=false;
	for(i=1;i<8;i++){
        if (((*row+i < 8) && ((*col+i) < 8)) && (f5==false)){
	        if (strcmp(board[*row+i][*col].piece_color,".")==0){
		        insert_move(row,col,i,i);
	        }
		    else if((strcmp(board[*row+i][*col+i].piece_color,color)==abs(21))){	//enemy color
		        insert_move(row,col,i,i);
		        f5=true;
		    }
		    else if(strcmp(board[*row+i][*col+i].piece_color,color)==0){
		        f5=true;
		    }
        }

        if ((*row-i >= 0)&& (*col+i < 8) && (f6==false)){
	        if (strcmp(board[*row-i][*col+i].piece_color,".")==0){
		        insert_move(row,col,-i,i);
	        }
		    else if((strcmp(board[*row-i][*col+i].piece_color,color)==abs(21))){	//enemy color
		        insert_move(row,col,-i,i);
		        f6=true;
		    }
		    else if(strcmp(board[*row-i][*col+i].piece_color,color)==0){
		        f6=true;
		    }
        }

        if (((*row+i < 8) && ((*col-i) >= 0)) && (f7==false)){
	        if (strcmp(board[*row+i][*col-i].piece_color,".")==0){
		        insert_move(row,col,i,-i);
	        }
		    else if((strcmp(board[*row+i][*col-i].piece_color,color)==abs(21))){	//enemy color
		        insert_move(row,col,i,-i);
		        f7=true;
		    }
		    else if(strcmp(board[*row+i][*col-i].piece_color,color)==0){
		        f7=true;
		    }
        }

        if (((*row-i >= 0) && (*col-i >=0)) && (f8==false)){
	        if (strcmp(board[*row-i][*col-i].piece_color,".")==0){
		        insert_move(row,col,-i,-i);
	        }
		    else if((strcmp(board[*row-i][*col-i].piece_color,color)==abs(21))){	//enemy color
		        insert_move(row,col,-i,-i);
		        f8=true;
		    }
		    else if(strcmp(board[*row-i][*col-i].piece_color,color)==0){
		        f8=true;
		    }
        }
	}
}

void knight_moves(int *row,int *col){
	if((*row+2 < 8)&&(*col-1 >= 0)){
		if(strcmp(board[*row+2][*col-1].piece_color,".")==0){
			insert_move(row,col,2,-1);
		}
		else if((strcmp(board[*row+2][*col-1].piece_color,color)==abs(21))){
			insert_move(row,col,2,-1);
		}
	}

	if((*row+2 < 8)&&(*col+1 < 8)){
		if(strcmp(board[*row+2][*col+1].piece_color,".")==0){
			insert_move(row,col,2,1);
		}
		else if (strcmp(board[*row+2][*col+1].piece_color,color)==abs(21)){
			insert_move(row,col,2,1);
		}
	}

	if((*row-2 >= 0)&&(*col-1 >= 0)){
		if(strcmp(board[*row-2][*col-1].piece_color,".")==0){
			insert_move(row,col,-2,-1);
		}
		else if ((strcmp(board[*row-2][*col-1].piece_color,color)==abs(21))){
			insert_move(row,col,-2,-1);
		}
	}
	if((*row-2 >= 0)&&(*col+1 < 8)){
		if(strcmp(board[*row-2][*col+1].piece_color,".")==0){
			insert_move(row,col,-2,1);
		}
		else if((strcmp(board[*row-2][*col+1].piece_color,color)==abs(21))){
			insert_move(row,col,-2,1);
		}
	}

	if((*row+1 < 8)&&(*col+2 < 8)){
		if(strcmp(board[*row+1][*col+2].piece_color,".")==0){
			insert_move(row,col,1,2);
		}
		else if((strcmp(board[*row+1][*col+2].piece_color,color)==abs(21))){
			insert_move(row,col,1,2);
		}
	}

	if((*row-1 >=0)&&(*col+2 < 8)){
		if(strcmp(board[*row-1][*col+2].piece_color,".")==0){
			insert_move(row,col,-1,2);
		}
		else if((strcmp(board[*row-1][*col+2].piece_color,color)==abs(21))){
			insert_move(row,col,-1,2);
		}
	}

	if((*row+1 < 8)&&(*col-2 >= 0)){
		if(strcmp(board[*row+1][*col-2].piece_color,".")==0){
			insert_move(row,col,1,-2);
		}
		else if ((strcmp(board[*row+1][*col-2].piece_color,color)==abs(21))){
			insert_move(row,col,1,-2);
		}
	}

	if((*row-1 >= 0)&&(*col-2 >= 0)){
		if(strcmp(board[*row-1][*col-2].piece_color,".")==0){
			insert_move(row,col,-1,-2);
		}
		else if((strcmp(board[*row+1][*col-2].piece_color,color)==abs(21))){
			insert_move(row,col,-1,-2);
		}
	}
}

void pawn_moves(int *row,int *col){
	int first_move_w=0,first_move_b=0;
	if(strcmp(color,"white")==0){ //down to up
		if(first_move_w==0){
			if(*row-2 >= 0){
				if(strcmp(board[*row-2][*col].piece_color,".")==0) {  		//blank
					insert_move(row,col,-2,0);
				}
			}
			first_move_w=1;
		}

		if(*row-1 >= 0){
			if(strcmp(board[*row-1][*col].piece_color,".")==0) {  		//blank
				insert_move(row,col,-1,0);
			}

			if(*col+1 < 8){
				if(strcmp(board[*row-1][*col+1].piece_color,color)==-21){	//enemy color right
					insert_move(row,col,-1,1);
				}
			}

			if(*col-1 >=0){
				if(strcmp(board[*row-1][*col-1].piece_color,color)==-21){	//enemy color left
					insert_move(row,col,-1,-1);
				}
			}
		}
	}
	else{ //up to down
		if(first_move_b==0){
			if(*row+2 >= 0){
				if(strcmp(board[*row+2][*col].piece_color,".")==0) {  		//blank
					insert_move(row,col,2,0);
				}
			}
			first_move_b=1;
		}
		if(*row+1 < 8){
			if(strcmp(board[*row+1][*col].piece_color,".")==0){  		//blank
				insert_move(row,col,1,0);
			}

			if(*col+1 < 8){
				if(strcmp(board[*row+1][*col+1].piece_color,color)==abs(21)){	//enemy color right
					insert_move(row,col,1,1);
				}
			}

			if(*col-1 >=0){
				if(strcmp(board[*row+1][*col-1].piece_color,color)==abs(21)){	//enemy color left
					insert_move(row,col,1,-1);
				}
			}
		}

	}
}

void possible_moves(char b_from[]){
	/*
	 * input = from position
	 * output = list of possible moves from that position
	 */
	int row=(int)b_from[0]-48;
	int col=(int)b_from[1]-48;
	switch(board[row][col].piece[0]){
	case 'k':
		m=0;
		king_moves(&row,&col);
		break;
	case 'q':
		m=0;
		rook_moves(&row,&col);
		bishop_moves(&row,&col);
		break;
	case 'h':
		m=0;
		knight_moves(&row,&col);
		break;
	case 'r':
		m=0;
		rook_moves(&row,&col);
		break;
	case 'b':
		m=0;
		bishop_moves(&row,&col);
		break;
	case 'p':
		m=0;
		pawn_moves(&row,&col);
		break;
	default:								// error her for black knight move
		cout<<endl<<"!! Error Piece = "<<board[row][col].piece[0]<<"\t details of black requested is \n";
		print_details(&row,&col);
		break;
	}
	int y=0;
	cout<<endl<<"possible mov are :\n";
	char movv[3];
	for(int i=0;i<10;i++){
		if(poss_moves[i][0]=='#')
			break;
		for(int j=0;j<2;j++){
			movv[j]=poss_moves[i][j];
		}
		get_play_moves(movv);
		cout<<move1;

		cout<<endl;
	}
	return;
}

int is_valid(char b_to[]){
	char move[3];
	b_to[2]='\0';
	for(i=0;i<15;i++){
		move[0]=move[1]=move[2]='\0';
		for(j=0;j<2;j++){
			move[j]=poss_moves[i][j];
		}
		if(strcmp(b_to,move)==0){
			return 1;
		}
	}
	return 0;
}

void movement(char *b_from,char *b_to){
	struct bd temp;
	int bfr=int(b_from[0])-48;
	int bfc=int(b_from[1])-48;
	int btr=int(b_to[0])-48;
	int btc=int(b_to[1])-48;

//	cout<<endl<<"bfr,bfc = "<<bfr<<" , "<<bfc;;
//	cout<<endl<<"btr,btc = "<<btr<<" , "<<btc;
//
//	print_details(&bfr,&bfc);
//	print_details(&btr,&btc);
	//moving to empty location

		strcpy(temp.piece,board[bfr][bfc].piece);
		strcpy(temp.piece_color,board[bfr][bfc].piece_color);
		temp.type_no=board[bfr][bfc].type_no;

		strcpy(board[bfr][bfc].piece,board[btr][btc].piece);
		strcpy(board[bfr][bfc].piece_color,board[btr][btc].piece_color);
		board[bfr][bfc].type_no=board[btr][btc].type_no;

		strcpy(board[btr][btc].piece,temp.piece);
		strcpy(board[btr][btc].piece_color,temp.piece_color);
		board[btr][btc].type_no=temp.type_no;

	if((board[btr][btc].piece,".")!=0){
		strcpy(board[bfr][bfc].piece," ");
		strcpy(board[bfr][bfc].piece_color,".");
		board[bfr][bfc].type_no=0;
	}

//	print_details(&bfr,&bfc);
//	print_details(&btr,&btc);

	draw_board();

}

///*
int main(){

	int n=2,c=0;
	char b_from[3],b_to[3];
	char u_move[5];
//	char u_move_l[4][6] = {{"b3-b4"},{"c5-c4"},{"c3-d5"},{"b8-c6"}};
	int f=0,flag=0;
	cout<<endl<<"enter 1 to continue previous played game: ";
	cin>>flag;
	init(flag);
	cout<<endl<<"Board initialized."<<endl;
	while((n%15)){ // logic to run while for 15-3 times
			n++;
			for(int r=0;r<15;r++){
					for(int s=0;s<2;s++){
						poss_moves[r][s]='#';
					}
				}

//		for(int r=0;r<4;r++){
//			for(int s=0;s<6;s++){
//				u_move[s] = u_move_l[r][s];   	//gather u_move from list
//			}
			cout<<endl<<"enter the move for "<<color<<" pieces : ";
			cin>>u_move;
			cout<<endl<<"from "<<u_move[0]<<u_move[1]<<" to "<<u_move[3]<<u_move[4]<<" color = "<<color;

			get_board_move(u_move,b_from,b_to);				//u_move is an array. b_from and b_to are character value of indexes.
			// now all operation are carried on actual array indexes.(moves = row,col)
			possible_moves(b_from);
			f = is_valid(b_to);
			if(f==1){
				movement(b_from,b_to);
				c==0 ? c=1:c=0;
				c==0 ? strcpy(color,"white") : strcpy(color,"black");
			}
			else {
				cout<<"not valid move, try again!!\n";
			}
		}
		cout<<endl<<"going to close";
	close1();
	cout<<endl<<"closed";
	return 0;
//	}
}

//*/
/*
int main(){

	int n=2,c=0,list_of_moves[30];
	char b_from[3],b_to[3];
	char u_move[5];
	bool f=false;
	init();
	cout<<endl<<"Board initialized."<<endl;
	while((n%15)){ // logic to run while for 15-3 times
		n++;
		cout<<endl<<"enter the move for "<<color<<" pieces : ";
		cin>>u_move;
		//color change logic
		c==0 ? c=1:c=0;
		c==0 ? strcpy(color,"white") : strcpy(color,"black");
		get_board_move(u_move,b_from,b_to);				//u_move is an array. b_from and b_to are character value of indexes.

		// now all operation are carried on actual array indexes.(moves = row,col)
		possible_moves(b_from);
		if(is_valid(b_to)){

		}

	}
	return 0;
}

*/
