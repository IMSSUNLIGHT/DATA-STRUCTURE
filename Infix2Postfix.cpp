/* Converting Infix to postfix*/

#include<iostream>
#include<string.h>
using namespace std;

class InfixPostfix{
char *st, *ins, *ops, ch;
int size, len, tos;
int i,j, flag;
public:
InfixPostfix();
~InfixPostfix();
int BalSymbol();
void Push(char);
char Pop();
char Peep();
int Prec(char);
bool IsFull();
bool IsEmpty();
void GetString();
void Display();
void Infix2Postfix();
};

InfixPostfix :: InfixPostfix(){
st=NULL;
ops=NULL;
ins=NULL;
size=0;
tos=-1;
j=0;
flag=0;
}

InfixPostfix :: ~InfixPostfix(){
delete []ins;
delete []st;
delete []ops;
}

void InfixPostfix :: Push(char x){
if(!IsFull()) st[++tos]=x;
else cout<<"Can't Insert, Stack is Full\n";
}

char InfixPostfix :: Pop(){
char x= '@';
if(!IsEmpty()) x=st[tos--];
else cout<<"Can't delete, Stack is Already Empty\n";
return x;
}

char InfixPostfix :: Peep(){
char x='@';
if(!IsEmpty()) x=st[tos];
else cout<<"Stack is Empty\n";
return x;
}

bool InfixPostfix :: IsFull(){
return (tos==(len-1));
}

bool InfixPostfix :: IsEmpty(){
return (tos==-1);
}

void InfixPostfix :: GetString(){
cout<<"Enter the size of stack\n";
cin>>size;
ins= new char[size];
cout<<"Enter the Expresion\n";
cin>>ins;
len= strlen(ins);
st=new char[len];
}

void InfixPostfix :: Display(){
cout<<"Equivalent Postfix Expression is:\t";
for(i=0; ops[i]!='\n'; i++){
cout<<ops[i];
}
cout<<endl;
}

int InfixPostfix :: Prec(char c){
if((c=='*') || (c=='/')) return 2;
else if((c=='+') || (c=='-')) return 1;
else return 0;
}

int InfixPostfix :: BalSymbol(){
GetString();
for(i=0;i<len; i++){
switch(ins[i]){
case '(':
case '{':
case '[': Push(ins[i]); break;
case ')':
case '}':
case ']':  if (IsEmpty()) {flag=1; break; }
	   else{
	   	ch=Peep();
	   	if((ch=='(' && ins[i]==')') || (ch=='{' && ins[i]=='}') || (ch=='[' && ins[i]==']')) ch=Pop();
	   	else flag=1;  
	   } //else
default: ;

} //switch
if(flag==1) break;
} // for

return flag;
} // BalSymbol


void InfixPostfix :: Infix2Postfix(){
int res;
res=BalSymbol();
if(res!=0) cout<<"You have entered Invalid Expression\n";
else{
ops=new char[len+1];
for(i=0; i<len; i++){
switch(ins[i]){
case '(': 
case '{':
case '[': Push(ins[i]); break;

case ')':
case '}':
case ']':
	while(1){
	ch=Pop();
	if((ch=='(') || (ch=='{')|| (ch =='['))	break;
	else ops[j++]=ch;
	}//while
	break;
case '+':
case '-':
case '*':
case '/':
	while(!IsEmpty() && (Prec(Peep())>=Prec(ins[i])))
		ops[j++]=Pop();
	Push(ins[i]);
	break;
default: 
	ops[j++]=ins[i];
	break;
}//switch
}//for
while(!IsEmpty()) ops[j++]=Pop();
ops[j]='\n';
Display();
}
}// Infix2Postfix


int main(){
InfixPostfix S1;
S1.Infix2Postfix();
return 0;
}
