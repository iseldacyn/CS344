#include <iostream>
#include <fstream>
#include <string>
#include "node.h"
#include "stack_linkedlist.h"
#include "queue_linkedlist.h"

using namespace std;

struct Student{
string name;
short arrive,length;
};

void announce(Student);
void meet(Student,short);

int main()
{
  //The unfair way
  cout << "The unfair way\n";

  short tS=0;
  Student studentS, currentS;
  Stack<Student> meetS;
  ifstream meetingS;
  meetingS.open("personin.txt");

  while(!meetingS.eof()){
    if(meetS.isEmpty()){
      meetingS >> studentS.name >> studentS.arrive >> studentS.length;
      meetS.push(studentS);
      announce(studentS);
      tS = studentS.arrive;
    }
    else{
      meetingS >> studentS.name >> studentS.arrive >> studentS.length;
      if(meetingS.eof()) break;
      else if(tS <= studentS.arrive){
        while(tS <= studentS.arrive){
        currentS = meetS.pop();
        meet(currentS, tS);
        tS += currentS.length;
        if(meetS.isEmpty()) break;
        }
        meetS.push(studentS);
        announce(studentS);
      }
      else{
        meetS.push(studentS);
        announce(studentS);
      }
    }
  }
  while(!meetS.isEmpty()){
    currentS = meetS.pop();
    meet(currentS, tS);
    tS += currentS.length;
  }
  cout << endl;
  meetingS.close();

  //The fair way
  cout << "The fair way\n";

  short tQ=0;
  Student studentQ, currentQ;
  Queue<Student> meetQ;
  ifstream meetingQ;
  meetingQ.open("personin.txt");
  while(!meetingQ.eof()){
    if(meetQ.isEmpty()){
      meetingQ >> studentQ.name >> studentQ.arrive >> studentQ.length;
      meetQ.enqueue(studentQ);
      announce(studentQ);
      tQ = studentQ.arrive;
    }
    else{
      meetingQ >> studentQ.name >> studentQ.arrive >> studentQ.length;
      if(meetingQ.eof()) break;
      else if(tQ <= studentQ.arrive){
        while(tQ <= studentQ.arrive){
          currentQ = meetQ.dequeue();
          meet(currentQ, tQ);
          tQ += currentQ.length;
          if(meetQ.isEmpty()) break;
        }
        meetQ.enqueue(studentQ);
        announce(studentQ);
      }
      else{
        meetQ.enqueue(studentQ);
        announce(studentQ);
      }
    }
  }
  while(!meetQ.isEmpty()){
    currentQ = meetQ.dequeue();
    meet(currentQ, tQ);
    tQ += currentQ.length;
  }
  meetingQ.close();
  return 0;
}

void announce(Student s){
  cout << " " << s.name << " arrives at " << s.arrive << " and requests a meeting of length " << s.length << endl;
}

void meet(Student s,short time){
  cout << s.name << " meets from " << time << " to " << time + s.length << endl;
}
