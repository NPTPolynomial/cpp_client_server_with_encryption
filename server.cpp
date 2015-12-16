//server implementation.

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> //to write
#include <stdio.h>

#include <sstream> //used to convert int to c_string
#include <cmath> //used to do pow() "to the power of..."

#include <pthread.h> //for multi-threaded connections. Compile with g++ server.cpp -lpthread

#include <vector> // to make matrix
#include <string>
#include <cstring>

using namespace std;

typedef vector<char> Row;
typedef vector<Row> Matrix;


/////////////////////////////////////////////
////////////STRING SUBSTITUTION ENCRYPTION///
/////////////////////////////////////////////

void string_substitution_back(string &str, int x){
    //if(x<0){
     //   x = 0;
    //}

    //cout << "string_substitution_back" << endl;
	//cout << "string received: " << str << endl;
   
    //Substitution Array
    char sa[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' ', ',', '.', '?'};
   
    
    char sa_cap[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '_', ']', '@', '!'};

    //char sb[]={ 'a', 'b', 'c'};

    //cout << sa[26]<<endl;

    //replace(str.begin(), str.end(), '-', sa[26]);
    
    //replace(str.begin(), str.end(), sa[26], sa[1]);
    
    int rep = 0;
    for(int i=0; i<30; i++){

        rep = ((i-x)%30);
        if(rep <0){
            rep = 30 + rep;
        }
        //cout << rep << endl;
        //cout << "replacing: " << sa_cap[i] << " with " << sa[rep] <<endl;
        replace(str.begin(), str.end(), sa_cap[i], sa[rep] );
        
    }
    
    
    //return str;

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
		//cout << "Adding: "<<s[index] <<" on row: "<<row<<" col: "<<col<<endl;
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
        
    swap_lines(m, 0, 1);
    break; 
    
    case 2:
        
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



void *connection_handler(void *);

////////////////////////
///////////////////////
//////Shared secret key (default 5)
int SECRET_KEY = 5;

///////////////////////////////////////////////
////////////////////////////////////////////
///////Diffie-Hellman's Algorithm Variables
double n = 3;
int q = 5;
////////////////User input xa (default: 10)
double xb = 10;

int yb = 10;
int ya = 0;


int main (){

    //create socket for server
    int socket_desc;
    int *new_sock;

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_desc == -1){
        cout << "Failed to create socket";
    }


    //incoming connection setup
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );


    //bind the socket to server
    if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0 ){
        cout << "Binding failed. Socket is being used. Please try again in 15 seconds."<<endl;
		return 0;
    }else{
        cout << "Binding success."<<endl;
    }


    //listen in for connections
    listen(socket_desc, 3);


    //accept incoming connections
    int new_socket;
    int c; //will be size of sockaddr_in for length of socket.
    int pid;
    struct sockaddr_in client;
    const char *message; //will be used to send message back to client
	const char *message2; //will be used to send message back to client

    cout << "Waiting for incoming connections..."<<endl;
    c = sizeof(struct sockaddr_in);
   

    pthread_t sniffer_thread;

    //accet new connections in a loop.
    while((new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c))){
        cout << "Connection accepted"<<endl;

        if(new_socket < 0){
            cout << "Incoming Connection failed to accepted"<<endl;

        }

        char *client_ip = inet_ntoa(client.sin_addr);
        int client_port = ntohs(client.sin_port);

        cout << "CLIENT IP: "<<client_ip<<endl;
        cout << "CLIENT PORT: "<<client_port<<endl;
		
		//calculating random private number for this session: xb
		xb = (rand()%7) + 1;
		yb = int(pow(n, xb)) % q;
		cout << "SERVER PRIVATE NUMBER: " << yb << endl;

		
		
		
		
	    int read_size_priv_num;
	    char client_priv_num[4];

	    if((read_size_priv_num = recv(new_socket, client_priv_num, 4, 0))<0){
		
			cout << "ERROR: Could not receive client's private number..." << endl;
			return 0;
		}else{
			
			cout << "CLIENT PRIVATE NUMBER: " << client_priv_num << endl;
			
			sscanf(client_priv_num, "%d", &ya);
			//cout << ya << endl;
			SECRET_KEY = int(pow(ya, xb))%q;
			cout << "CALCULATED SHARED SECRET KEY: " << SECRET_KEY <<endl;
		}
		
		
		
		
		
		
        

        //send message back to client
        message = "Hello client :) \n";
        send(new_socket, message, strlen(message)+1, 0);
		
        //send message back to client
		//const char* privkey = xb;
        message2 = intToStr(yb).c_str();
		cout << "server sending message: " << message2 << endl;
        send(new_socket, message2, strlen(message2), 0);
/*
        if ((pid=fork())==0){
            close(socket_desc);
             //send message back to client
            message = "Hello client from forked process:) \n";
            send(new_socket, message, strlen(message), 0);
            close(new_socket);
            exit(0);

        }
        close(new_socket);
*/
        ///create thread to allow more connections and to keep connection alive.
        new_sock = (int *)malloc(1);
        *new_sock = new_socket;
        
        //assigns the thread
        if (pthread_create( &sniffer_thread, 0, connection_handler, new_sock ) < 0){
            cout << "Error, could not create thread"<<endl;
            perror("Could not create thread");
            return 1;
        }



    }

    
   

    close(socket_desc);
    return 0;


}

//This handles connection for multiple clients
void *connection_handler(void *socket_desc){
    int sock = *((int *)socket_desc);
    int read_size;
    const char *message;
    char client_message[2000];

    while((read_size = recv(sock, client_message, 2000, 0))>0){

    //send(sock, client_message, strlen(client_message), 0);
		
		//create matrix to hold data coming in.
		Matrix myMatrix(15, Row(15));
		
		cout <<"\n"<< "Client: "<< client_message << endl;
		string mystr = client_message;
		//string mystr(client_message, sizeof(client_message));
		
		//cout << "mystr: "<< mystr << endl;
		initMatrix(myMatrix,15,15);
		initMatrix_with_string(myMatrix, mystr);
		printMatrixSq(myMatrix,15,15);
		re_arrange_back(myMatrix, SECRET_KEY);
		printMatrixSq(myMatrix,15,15);
		string matrix_str = matrixToStr(myMatrix);
		cout << "Matrix to str = "<< matrix_str<<endl;
		cout << "Decode str to original: "<<endl;
		string_substitution_back(matrix_str, SECRET_KEY);
		//cout << matrix_str << endl;
		
		matrix_str.erase(std::remove(matrix_str.begin(), matrix_str.end(), '-'), matrix_str.end());
		cout << matrix_str << endl;		
		cout << endl;
		

    }


    //message = "This is a message from the handler\n";
    //send(sock, message, strlen(message), 0);
    free(socket_desc);
    return 0;
}
