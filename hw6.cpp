#include <iostream.h>
#include <conio.h>
#include <dos.h>
#include <ctype.h>
#include <fstream.h>
#include <string.h>
#include <iomanip.h>

struct unit {
   int partnumber;
   char name[100];
   int quantityinstock;
   unit* next;
};

typedef unit* unitptr;    //pointer to structure

void printit(unitptr head);
void part1(unitptr &head, unitptr &curr);
void part2(unitptr head, unitptr curr);
void part3(unitptr head, unitptr curr);

void main()  {
  unitptr head,curr,temp;
  clrscr();
  part1(head,curr);
  part2(head,curr);
  part3(head,curr);
}

void part1(unitptr &head, unitptr &curr) {
 unitptr temp;
 int partno, quant;
 char nameofpart[100];
 ifstream input1;
 input1.open("a:\\hw6add.txt", ios::in);
 //Read in the input to add and set head to the first one
 input1 >> partno >> nameofpart >> quant;
     temp = new unit;
     temp -> partnumber = partno;
     temp -> quantityinstock = quant;
     strcpy(temp->name, nameofpart);
     temp->next = NULL;
     head = temp;

 while (input1 >> partno >> nameofpart >> quant, !input1.eof()) {
     //set the current to the head
     curr = head;
     temp = new unit;
     temp -> partnumber = partno;
     temp -> quantityinstock = quant;
     strcpy(temp->name, nameofpart);
     temp->next = NULL;
     //does the new node go at the head position?
     if (curr -> partnumber > temp -> partnumber) {
	head = temp;
	temp->next = curr->next;
     }
     //Otherwise, it goes somewhere else in the list
     else {
       //As long as the current node in the list has a smaller part number
       //Traverse the list. Also check to see if the next node is null
       while ((curr->next != NULL) && (curr->next->partnumber <= temp->partnumber))
	  curr=curr->next;
       if (curr -> next != NULL) {
       //Put temp in between curr and curr->next.
	 temp->next = curr->next;
	 curr->next = temp;
       }
       else {
       //You have reached the end of the list.  Insert here.
	 curr->next = temp;
       }
     } //end of else
 }  //end while data still in file input1
 printit(head);
 getch();
 input1.close();
} //end of part1 funstion

void part2(unitptr head,unitptr curr) {
 int partno, quant;
 ifstream input2;
 input2.open("a:\\hw6mod.txt", ios::in);

 while (input2 >> partno >> quant, !input2.eof()) {
   curr=head;
   //Loop through till you find the part or reach the end of list
   while ( (curr != NULL) && (curr->partnumber != partno) ) {
       curr = curr -> next;
   }
   if(curr == NULL) cout << "Could not find part " << partno << " to modify." << endl;
    else
    curr->quantityinstock = curr->quantityinstock + quant;
 } //End of while loop for input2
 cout << "\nAfter modifying we have: " << endl;
 printit(head);
 getch();
 input2.close();
}// end of part2

void part3(unitptr head, unitptr curr) {
  int partno, quant;
  ifstream input3;
  input3.open("a:\\hw6del.txt", ios::in);

  while (input3 >> partno, !input3.eof()) {
     curr=head;
     if(curr->partnumber == partno) { //We want to delete the head of the list
       head = curr->next;
       curr->next = NULL;
     }
     else {
	while ((curr != NULL) && (curr->next->partnumber != partno))
	   curr=curr->next;
	if (curr == NULL) cout << "Could not find part " << partno << " to delete." << endl;
	else curr->next = curr->next->next;
     }
  }
  cout << "\nAfter deleting we have: " << endl;
  printit(head);
  getch();
  input3.close();
}//end of part3

void printit(unitptr head) {
  //cout<<"\nPart #"<<setw(20)<<"Part Name"<<setw(5)<<"Quantity in Stock";
  //cout<<"\n------------------------------------------\n";
  while (head != NULL) {
     cout << setw(5) << head->partnumber << setw(30) << head->name << setw(8) << head->quantityinstock;
     cout << endl;
     head = head -> next;
  }
  cout<<"\nPress any key to continue......\n";
}