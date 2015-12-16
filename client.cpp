//#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h> //for inet_addr

#include <sstream> //used to convert int to c_string

#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath> //used to do pow() "to the power of..."

#include <vector> //for matrix

// IPv4 AF_INET sockets:
/*struct sockaddr_in {
    short sin_family;   // e.g. AF_INET, AF_INET6
    unsigned short sin_port;     // e.g. htons(3490)
    struct in_addr sin_addr;     // see struct in_addr, below
    char sin_zero[8];  // zero this if you want to
};
 
struct in_addr {
    unsigned long s_addr;          // load with inet_pton()
};

struct sockaddr {
    unsigned short    sa_family;    // address family, AF_xxx
    char              sa_data[14];  // 14 bytes of protocol address
};

*/

using namespace std;
//////////////////////////////////////////
///////////////////Making Matrix//////////
//////////////////////////////////////////
typedef vector<char> Row;
typedef vector<Row> Matrix;





/////////////////////////////////////////////
////////////STRING SUBSTITUTION ENCRYPTION///
/////////////////////////////////////////////

void string_substitution(string &str, int x){
    if(x<0){
        x = 0;
    }

    //cout << "replace_string called" << endl;
   
    //Substitution Array
    char sa[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' ', ',', '.', '?'};
   
    
    char sa_cap[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_', ']', '@', '!'};

    
    //replace(str.begin(), str.end(), sa[26], sa[1]);
    
    int rep = 0;
    for(int i=0; i<30; i++){

        rep= (i+x)%30;
        cout << rep << endl;
        cout << "replacing: " << sa[i] << " with " << sa_cap[rep] <<endl;
        replace(str.begin(), str.end(), sa[i], sa_cap[rep] );
        
    }

}




/////////////////////////////////////////////
////////////MATRIX FUNCTIONS///
/////////////////////////////////////////////

void printMatrixSq(const Matrix &m, int num_col, int num_row){
    cout << "Print Matrix SQ called" <<endl;
    for(int i=0; i<num_row; i++){
        for(int j=0; j<num_col; j++){
            //cout << "Matrix[" << i << "][" << j << "]: ";
            char compare = ' '; 

            cout << m[i][j]<< " ";

            if(j == num_col-1){
                cout << endl;
            }
        }


    }
}


void initMatrix( Matrix &m, int col, int row){
    for(int i=0; i<col; i++){
        for(int j=0; j<row; j++){
            m[j][i] = '-';
        }
    }

}

void initMatrix_with_string( Matrix &m, string s){
    int length = s.length();    
    cout<< "string length: "<< s.length()<<endl;
    
    int row = 0;
    int col = 0;
    int index = 0;

    while(index < length){

        m[row][col] = s[index];

        if(col>=m.size()-1){
            col = 0;
            row++;
        }else{
            col++;;
        }

        if(row>=m.size()){
            row = 0;
        }

        index++;

    }

}

string matrixToStr(const Matrix &m){
	string ret;
	int size = m.size();
	
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			ret += (m[i][j]);
			
			//cout << "currently ret: " << ret << endl;
		}
		
	}
	
	return ret;
}




void swap(char &a, char &b){
    //cout << "Swapping: " << a << " with: "<< b << endl;
    
    char c = a;
    a = b;
    b = c;

}

void swap_lines(Matrix &m, int a, int b){
    int n = m.size();

    if((a < n) && (b < n) && (a != b)){
        
        for(int i=0; i < n; i++){
            swap(m[a][i], m[b][i]);
        }
        
    }else{
        cout<<"Error: swap_line: parameter error."<<endl;
    }

}

void transpose(Matrix &m){
    int n = m.size();
    for(int i =0; i < n-1; i++){
        for(int j= i + 1; j < n; ++j){
            swap(m[i][j], m[j][i]);
        }

    }

}

void re_arrange(Matrix &m, int x){
   cout<<"Rearrange engaged"<<endl;

    switch(x){
    case 1:
        transpose(m);
    	swap_lines(m, 0, 1);
		swap_lines(m, 2, 3);
		swap_lines(m, 4, 5);
		swap_lines(m, 6, 7);
		swap_lines(m, 8, 9);
		swap_lines(m, 10, 11);
		swap_lines(m, 12, 13);
    break; 
    
    case 2:
        transpose(m);
    	swap_lines(m, 1, 2);
		swap_lines(m, 2, 3);
		swap_lines(m, 4, 5);
		swap_lines(m, 6, 7);
		swap_lines(m, 8, 9);
		swap_lines(m, 10, 11);
		swap_lines(m, 12, 13);
		swap_lines(m, 14, 0);
    break;
	
    case 3:
		swap_lines(m, 0, 1);
		swap_lines(m, 2, 3);
		swap_lines(m, 4, 5);
		swap_lines(m, 6, 7);
		transpose(m);
		swap_lines(m, 8, 9);
		swap_lines(m, 10, 11);
		swap_lines(m, 12, 13);
        transpose(m);
    	
    break;
	
    case 4:
		swap_lines(m, 1, 2);
		swap_lines(m, 2, 3);
		swap_lines(m, 4, 5);
		swap_lines(m, 6, 7);
		transpose(m);
		swap_lines(m, 8, 9);
		swap_lines(m, 10, 11);
		swap_lines(m, 12, 13);
		swap_lines(m, 14, 0);
        transpose(m);
    break;
	
    case 5:
        transpose(m);
    	swap_lines(m, 1, 2);
    break;


    default:
        transpose(m);

    }


}

/////////////////////////////////////////
/////////////Reverse the re-arrangement
//////////////////////////////////////////

void re_arrange_back(Matrix &m, int x){
   cout<<"Rearrange back engaged"<<endl;

    switch(x){
    case 1:
		swap_lines(m, 12, 13);
		swap_lines(m, 10, 11);
		swap_lines(m, 8, 9);
		swap_lines(m, 6, 7);
		swap_lines(m, 4, 5);
		swap_lines(m, 2, 3);
		swap_lines(m, 0, 1);
        transpose(m);
		
    break; 
    
    case 2:
		swap_lines(m, 14, 0);
		swap_lines(m, 12, 13);
		swap_lines(m, 10, 11);
		swap_lines(m, 8, 9);
		swap_lines(m, 6, 7);
		swap_lines(m, 4, 5);
		swap_lines(m, 2, 3);
		swap_lines(m, 1, 2);
        transpose(m);
    	
    break;
	
    case 3:
		transpose(m);
		swap_lines(m, 12, 13);
		swap_lines(m, 10, 11);
		swap_lines(m, 8, 9);
		transpose(m);
		swap_lines(m, 6, 7);
		swap_lines(m, 4, 5);
		swap_lines(m, 2, 3);
		swap_lines(m, 0, 1);
		
    break;
	
    case 4:
		transpose(m);
		swap_lines(m, 14, 0);
		swap_lines(m, 12, 13);
		swap_lines(m, 10, 11);
		swap_lines(m, 8, 9);
		transpose(m);
		swap_lines(m, 6, 7);
		swap_lines(m, 4, 5);
		swap_lines(m, 2, 3);
		swap_lines(m, 1, 2);
		
    break;
	
    case 5:
		swap_lines(m, 1, 2);
        transpose(m);
    	
    break;


    default:
        transpose(m);

    }


}


/////////////////////////////////////
////////////////////////
//////Convert Int to String
////////////////////////////////////
string intToStr(int x){
 
    stringstream convert_to_string;
 
    convert_to_string << x;
    return convert_to_string.str();
}




////////////////////////
///////////////////////
//////secret key (default 5)
int SECRET_KEY = 5;

///////////////////////////////////////////////
////////////////////////////////////////////
///////Diffie-Hellman's Algorithm Variables
double n = 3;
int q = 5;
////////////////User input xa (default: 10)
double xa = 10;
int ya = 10;
int yb = 0;


int main( int argc, char *argv[]){

    //create a client socket
    int socket_desc;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc == -1){
        cout<<"Could not create socket"<<endl;
    }
    

    //prepare all the addresses for the server we are connecting to 
    struct sockaddr_in server;

    //server.sin_addr.s_addr = inet_addr("216.58.209.3");
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);

    //connect to remote server
    if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) <0){
        cout<<"connection error"<<endl;
        return 1;
    }else{
        cout<<"connected"<<endl;
		
		//calculating random private number for this session: xa
		xa = (rand()%11) + 1;
		
		ya = int(pow(n, xa))%q;
		
		cout << "CLIENT PRIVATE NUMBER: " << ya << endl;

    }
	
	
	const char *message;
	//send server client's private number:
    //send message back to server
    message = intToStr(ya).c_str();
    send(socket_desc, message, strlen(message), 0);
	
    
	
	
    //receive data if there is any
    cout << endl;
    char server_reply[100];
    if (recv(socket_desc, server_reply, 100, 0) < 0){
        cout << "Recv failed"<<endl;

    }else{
        cout << "Server reply: ";
        cout << server_reply << endl;
    }

    //clear reply:
        server_reply[0] = '\0';
        memset(&server_reply[0],0,sizeof(server_reply));
    cout << endl;
	
	

    //receive server private key
    cout << endl;
    char server_reply_priv_key[4];
    if (recv(socket_desc, server_reply_priv_key, 4, 0) < 0){
        cout << "server_reply_priv_key Recv failed"<<endl;
		return 0;

    }else{
        cout << "Server reply: SERVER PRIVATE NUMBER is ";
        cout << server_reply_priv_key << endl;
		
		sscanf(server_reply_priv_key, "%d", &yb);
		
		if(yb == 0){
			cout << "Error: Could not get server's private number, please restart client using 'CTRL + C' and try again."<<endl;
			return 0;
			
		}
		
		SECRET_KEY = int(pow(yb, xa))%q;
		cout << "CALCULATED SHARED SECRET KEY: " << SECRET_KEY <<endl;
    }

    //clear reply:
        server_reply_priv_key[0] = '\0';
        memset(&server_reply_priv_key[0],0,sizeof(server_reply_priv_key));
    cout << endl;
	
	////////////////////////////////////
	/////Calculating the secret key
	////////////////////////////////////
	
	
	
	
	/////////////////////////////////////////////////
	////////////////////Make Matrix 15x15
	/////////////////////////////////////////////////
	Matrix myMatrix(15, Row(15));
	
	initMatrix(myMatrix, 15,15);
	
    

    while(1){

        //send test data
        cout<<"Please enter a message (limit: 225 lower-case chars):"<<endl;
        char input_stream[256];
        cin.getline(input_stream, sizeof(input_stream));
        //message = input_stream.c_str();
        //message = "GET / HTTP/1.1\r\n\r\n";
		
		
		
	    string s(input_stream, strlen(input_stream));
	    //cout << s << endl;
	    string_substitution(s, SECRET_KEY);
		
		cout << "This is encoded using substitution: "<< s << endl; 
		
		initMatrix(myMatrix, 15, 15);
		initMatrix_with_string(myMatrix, s);
		printMatrixSq(myMatrix,15,15);
		re_arrange(myMatrix, SECRET_KEY);
		//re_arrange(myMatrix, 2);
		//re_arrange(myMatrix, 1);
		printMatrixSq(myMatrix,15,15);
		string str_matrix = matrixToStr(myMatrix);
		
		cout << "final str matrix: " << str_matrix << endl;
		
		const char *final_message = str_matrix.c_str();
		
		cout << "Encrypted message: " << final_message <<endl;
		
        
        if (send(socket_desc, final_message, strlen(final_message), 0) < 0){
            cout<<"Message failed to send."<<endl<<endl;
        }else{
            cout<<"Message sent."<<endl<<endl;
        };
        


    }

    //close connection

    close(socket_desc);

    return 0;
}

