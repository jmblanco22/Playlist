#include <iostream>
#include "Playlist.h"
using namespace std;


//Default and only constructor -- call private function init
Playlist::Playlist() {
	init();
}

//Destructor -- call private function eraseList with head
Playlist::~Playlist() {
	eraseList(head);
}

int Playlist::getNodeCount() {
	
	return nodeCount;
}

//Add a SongNode to the front of the list
void Playlist::insertFront(SongNode* songNode) {
	if (head == nullptr) {
		head = songNode;
		songNode->setNext(nullptr);
	}
	else {
		songNode->setNext(head);
		head = songNode;
	}
	nodeCount++;
}

//Remove an SongNode from the list; if the value doesn't exist in the list return false;
//   otherwise search for the SongNode, adjust pointers, and return true.
bool Playlist::remove(string id) {
	if (!contains(id)) { return false; }

	SongNode* curr = head;
	SongNode* prev = head;

	// Find the node with the value of data
	while (curr->getUniqueID() != id) {
		prev = curr;
		curr = curr->getNext();
	}

	// curr will contain the node to be deleted
	// Node is at the front of the list
	if (curr == head) {
		head = curr->getNext();
		delete curr;
	}
	// Node is in middle or is last node
	else {
		prev->setNext(curr->getNext());
		delete curr;
	}
	nodeCount--;
	return true;

}

//This function is the most complicated
//   songPosition and newPosition values have been validated in main
//		before this function is called
void Playlist::changeSongPosition(int songPosition, int newPosition) {
	if (songPosition == newPosition) {
		return;
	}

	SongNode* newNode = head;
	SongNode* prevNode = nullptr;
	
	int pos = 1;
	// STEP 1: Find songNode that is at songPosition
	while (newNode != nullptr && pos < songPosition) {
		prevNode = newNode;
		newNode = newNode->getNext();
		pos++;
	}
	if (newNode == nullptr) {
		return;
	}


	// STEP 2: Remove songNode at songPosition from list. Keep reference to that songNode.

	// If songPosition was 1, song being moved was the head of the list
	//		so change what head points to
	// otherwise
	//		find the node before songNode in the list and adjust that node's
	//		next pointer

	// At this point songNode is no longer in the list
	if (prevNode == nullptr) {
		head = newNode->getNext();
	}
	else {
		
		prevNode->setNext(newNode->getNext());
	}


	// STEP 3: Insert song at newPosition
	//	If the newPosition was 1 ... the songNode will become the head of the list
	//		adjust pointers appropriately
	//	otherwise
	//		find the node that is before the newPosition
	//		it will be somewhere after original head position or at
	//		the end of the list
	//		call insertAfter
	if(newPosition == 1){
		newNode->setNext(head);
		head = newNode;
	}
	else {
		SongNode* currNode = head;
		SongNode* prevNewNode = nullptr;
		int newpos = 1;
		while (currNode != nullptr && newpos < newPosition) {
			prevNewNode = currNode;
			currNode = currNode->getNext();
			newpos++;
		}
		if (prevNewNode == nullptr) {
			head = newNode;
		}
		else {
			prevNewNode->setNext(newNode);
		}
		newNode->setNext(currNode);
	}
	

	
}

// insertAfter ... inserts newNode after prevNode
void Playlist::insertAfter(SongNode* prevNode, SongNode* newNode) {
	if (prevNode != nullptr) {
		// Set next of newNode as next of prevNode
	}
		newNode->setNext(prevNode->getNext());

		// Set next of prevNode to newNode
		prevNode->setNext(newNode);
	
	nodeCount++;
}

// calculate total time in seconds in playlist
int Playlist::getTotalTime() {
	
	int totalTime = 0;
	
	SongNode* curr = head;

		while (curr != nullptr) {
			totalTime += curr->getSongLength();
			curr = curr->getNext();
		}
		return totalTime;
		
	
}

// Print out all nodes in the list
void Playlist::printPlaylist() {
	SongNode* songs = head;
	int i = 1;
	if (head == nullptr) {
		cout << "\n\t>>> PLaylist is empty! <<<" << endl;
	}
	else {
		printTableHeadings();
		while (songs != nullptr) {
			printTableRow(songs, i);
			i++;
			songs = songs->getNext();
		}
		
	}
	
}

// Print out all nodes in the list with the artist's name
void Playlist::printByArtist(string artist) {
	SongNode* curr = head;

	printTableHeadings();
	if (curr == nullptr) {
		cout << "\t List is empty! <<" << endl;
	}
	else {
		SongNode* temp = head;
		int i = 1;
		while (temp != nullptr) {
			if (temp->getArtistName() == artist) {
				
				printTableRow(temp, i);
			}
			i++;
			temp = temp->getNext();
			
		}

		cout << endl;
	}
}

// Search to see if list contains the uniqueID
bool Playlist::contains(const string& id) {
	SongNode* curr = head;

	while (curr != nullptr) {
		if (id == curr->getUniqueID())
			return true;
		else
			curr = curr->getNext();
	}
	return false;
}

// Clear the list -- remove all nodes and initialize the playlist again
void Playlist::clearList() {
	eraseList(head);
	init();
	cout << "\n\t>>> PLaylist has been cleared! <<<" << endl;
	return;
}

// Set up linked list starting values
void Playlist::init() {
	head = nullptr;
	nodeCount = 0;
}

// Delete all allocated objects
void Playlist::eraseList(SongNode* head) {
	SongNode* curr = head;
	SongNode* succ;

	while (curr != nullptr) {
		succ = curr->getNext();
		delete curr;
		curr = succ;
	}
	nodeCount = 0;
}
// COMPLETED -- DO NOT CHANGE
// Print headings for playlist table
void Playlist::printTableHeadings() {
	
		cout << "\n\t------------------------- PLAYLIST ------------------------------" << endl;
		cout << "\t" << setw(5) << left << "Pos  ";
		cout << setw(12) << left << "Unique Id";
		cout << setw(20) << left << "Song";
		cout << setw(20) << left << "Artist";
		cout << setw(4) << left << "Time" << endl;
	
}
// COMPLETED -- DO NOT CHANGE
void Playlist::printTableRow(SongNode* song, int position) {
	
		cout << "\t" << setw(5) << left << position;
		cout << setw(12) << left << song->getUniqueID();
		cout << setw(20) << left << song->getSongName();
		cout << setw(20) << left << song->getArtistName();
		cout << setw(4) << right << song->getSongLength() << endl;
	
}







